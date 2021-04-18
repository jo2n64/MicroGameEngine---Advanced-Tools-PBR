#include "glm.hpp"
#include "PBRTexMaterial.hpp"

#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* PBRTexMaterial::_shader = NULL;

GLint PBRTexMaterial::_uModelMatrix = 0;
GLint PBRTexMaterial::_uViewMatrix = 0;
GLint PBRTexMaterial::_uProjectionMatrix = 0;

GLint PBRTexMaterial::_uDiffuseTexture = 0;
GLint PBRTexMaterial::_uMetallicTexture = 1;
GLint PBRTexMaterial::_uRoughnessTexture = 2;
GLint PBRTexMaterial::_uNormalTexture = 3;

GLint PBRTexMaterial::_aVertex = 0;
GLint PBRTexMaterial::_aNormal = 0;
GLint PBRTexMaterial::_aUV = 0;

PBRTexMaterial::PBRTexMaterial(Texture* pDiffuseTexture, Texture* pMetallicTexture, Texture* pRoughnessTexture, Texture* pNormalTexture):
	_diffuseTexture(pDiffuseTexture), _metallicTexture(pMetallicTexture), _roughnessTexture(pRoughnessTexture), _normalTexture(pNormalTexture){
	_lazyInitializeShader();
}

PBRTexMaterial::PBRTexMaterial()
{
	_lazyInitializeShader();
}

PBRTexMaterial::~PBRTexMaterial()
{
}

void PBRTexMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	if (!_diffuseTexture) return;
	_shader->use();

	if (pWorld->getLightCount() > 0) {
		Light* light = pWorld->getLightAt(0);

		glUniform3fv(_shader->getUniformLocation("pointLightColors[" + std::to_string(0) + ']'), 1, glm::value_ptr(light->getLightColor()));
		glUniform3fv(_shader->getUniformLocation("pointLightPositions[" + std::to_string(0) + ']'), 1, glm::value_ptr(light->getWorldPosition()));
		glUniform3fv(_shader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(pWorld->getMainCamera()->getWorldPosition()));
	}

	streamTextureToShader(0, _diffuseTexture, _uDiffuseTexture);
	streamTextureToShader(1, _metallicTexture, _uMetallicTexture);
	streamTextureToShader(2, _roughnessTexture, _uRoughnessTexture);
	streamTextureToShader(3, _normalTexture, _uNormalTexture);

	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));

	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);

}

void PBRTexMaterial::streamTextureToShader(int textureIndex, Texture* textureToStream, GLint uniformLocation)
{
	glActiveTexture(GL_TEXTURE0+textureIndex);
	glBindTexture(GL_TEXTURE_2D, textureToStream->getId());
	glUniform1i(uniformLocation, textureIndex);
}

void PBRTexMaterial::setDiffuseTexture(Texture* pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;
}

void PBRTexMaterial::setMetallicTexture(Texture* pMetallicTexture)
{
	_metallicTexture = pMetallicTexture;
}

void PBRTexMaterial::setRoughnessTexture(Texture* pRoughnessTexture)
{
	_roughnessTexture = pRoughnessTexture;
}

void PBRTexMaterial::setNormalTexture(Texture* pNormalTexture)
{
	_normalTexture = pNormalTexture;
}

void PBRTexMaterial::_lazyInitializeShader()
{
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "pbr_tex.vert");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "pbr_tex.frag");
		_shader->finalize();

		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");
		_uMetallicTexture = _shader->getUniformLocation("metallicTexture");
		_uRoughnessTexture = _shader->getUniformLocation("roughnessTexture");
		_uNormalTexture = _shader->getUniformLocation("normalTexture");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");

	}
}
