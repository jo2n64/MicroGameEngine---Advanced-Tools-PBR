#include "LightMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"

ShaderProgram* LightMaterial::_shader = NULL;

LightMaterial::LightMaterial(glm::vec3 pLightColor) : _lightColor(pLightColor)
{
	_lazyInitializeShader();
}

LightMaterial::~LightMaterial()
{
}

void LightMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	_shader->use();

	//glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));
	//glUniform3fv(_shader->getUniformLocation("pointLightColor"), 1, glm::value_ptr(_lightColor));
	//glUniform3fv(_shader->getUniformLocation("ambientColor"), 1, glm::value_ptr(_ambientColor));
	//glUniform3fv(_shader->getUniformLocation("pointLightPosition"), 1, glm::value_ptr(_lightPosition));
	//glUniform1fv(_shader->getUniformLocation("specularIntensity"), 1, &_specularStrength);

	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);
}

//void LightMaterial::setDiffuseColor(const glm::vec3 pDiffuseColor)
//{
//	_diffuseColor = pDiffuseColor;
//}
//
//void LightMaterial::setAmbientColor(const glm::vec3 pAmbientColor)
//{
//	_ambientColor = pAmbientColor;
//}
//
//void LightMaterial::setLightColor(const glm::vec3 pLightColor)
//{
//	_lightColor = pLightColor;
//}
//
//void LightMaterial::setLightPosition(const glm::vec3 pLightPosition)
//{
//	_lightPosition = pLightPosition;
//}
//
//void LightMaterial::setSpecularIntensity(const float pSpecIntensity)
//{
//	_specularStrength = pSpecIntensity;
//}

void LightMaterial::_lazyInitializeShader()
{
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "light.vert");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "light.frag");
		_shader->finalize();
	}
}
