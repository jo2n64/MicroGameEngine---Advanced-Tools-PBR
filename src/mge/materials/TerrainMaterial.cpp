#include "TerrainMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"
#include <stdio.h>

ShaderProgram* TerrainMaterial::_shader = NULL;

GLint TerrainMaterial::_uMVPMatrix = 0;
GLint TerrainMaterial::_uDiffuseTexture = 1;
GLint TerrainMaterial::_uHeightmapTexture = 0;
GLint TerrainMaterial::_uSplatmapTexture = 2;

GLint TerrainMaterial::_aVertex = 0;
GLint TerrainMaterial::_aNormal = 0;
GLint TerrainMaterial::_aUV = 0;

TerrainMaterial::TerrainMaterial(float pHeightModifier, float pTilingMultiplier) :  _heightModifier(pHeightModifier), _tilingMultiplier(pTilingMultiplier)
{
	_lazyInitializeShader();
}

TerrainMaterial::~TerrainMaterial()
{
}

void TerrainMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	if (!_heightmapTexture) return;

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	if (pWorld->getLightCount() > 0) {

		Light* light = pWorld->getLightAt(0);

		glUniform1f(_shader->getUniformLocation("ambientIntensity"), light->getAmbientIntensity());
		glUniform1f(_shader->getUniformLocation("specularIntensity"), light->getSpecularIntensity());

		glUniform3fv(_shader->getUniformLocation("pointLightColor"), 1, glm::value_ptr(light->getLightColor()));
		glUniform3fv(_shader->getUniformLocation("pointLightPosition"), 1, glm::value_ptr(light->getLocalPosition()));
		glUniform3fv(_shader->getUniformLocation("ambientColor"), 1, glm::value_ptr(light->getAmbientColor()));
		glUniform3fv(_shader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(pWorld->getMainCamera()->getLocalPosition()));
		glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));
		std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;

	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _heightmapTexture->getId());
	glUniform1i(_uHeightmapTexture, 0);
	glUniform1f(_shader->getUniformLocation("heightModifier"), _heightModifier);
	glUniform1f(_shader->getUniformLocation("tileMul"), _tilingMultiplier);

	_setupTexture(_diffuseTexture1, 1, "diffuseTexture1");
	_setupTexture(_diffuseTexture2, 2, "diffuseTexture2");
	_setupTexture(_diffuseTexture3, 3, "diffuseTexture3");
	_setupTexture(_diffuseTexture4, 4, "diffuseTexture4");

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, _splatmapTexture->getId());
	glUniform1i(_shader->getUniformLocation("splatmapTexture"), 5);
	

	//pass in a precalculate mvp matrix (see texture material for the opposite)
	//glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	//glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}

void TerrainMaterial::setDiffuseColor(const glm::vec3 pDiffuseColor)
{
	_diffuseColor = pDiffuseColor;
}

void TerrainMaterial::setDiffuseTexture1(Texture* pDiffuseTexture)
{
	_diffuseTexture1 = pDiffuseTexture;
}

void TerrainMaterial::setDiffuseTexture2(Texture* pDiffuseTexture)
{
	_diffuseTexture2 = pDiffuseTexture;
}

void TerrainMaterial::setDiffuseTexture3(Texture* pDiffuseTexture)
{
	_diffuseTexture3 = pDiffuseTexture;
}

void TerrainMaterial::setDiffuseTexture4(Texture* pDiffuseTexture)
{
	_diffuseTexture4 = pDiffuseTexture;
}

void TerrainMaterial::setHeightmapTexture(Texture* pHeightmapTexture)
{
	_heightmapTexture = pHeightmapTexture;
}

void TerrainMaterial::setHeightModifier(const float pHeightModifier)
{
	_heightModifier = pHeightModifier;
}

void TerrainMaterial::setSplatmapTexture(Texture* pSplatmapTexture)
{
	_splatmapTexture = pSplatmapTexture;
}

void TerrainMaterial::_lazyInitializeShader()
{
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "terrain.vert");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "terrain.frag");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		//_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		/*_uModelMatrix = _shader->getUniformLocation("modelMatrix");
		_uViewMatrix = _shader->getUniformLocation("viewMatrix");
		_uProjectionMatrix = _shader->getUniformLocation("projectionMatrix");*/
		//_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}


//actually more like binding instead of setting up, but whatever...
void TerrainMaterial::_setupTexture(Texture* pDiffuseTexture, int index, std::string uniformLocation)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, pDiffuseTexture->getId());
	glUniform1i(_shader->getUniformLocation(uniformLocation), index);

}
