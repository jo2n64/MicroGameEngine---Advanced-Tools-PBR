#include "glm.hpp"

#include "PBRColorMaterial.hpp"

#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* PBRColorMaterial::_shader = NULL;



PBRColorMaterial::PBRColorMaterial(glm::vec3 pColor) : _diffuseColor(pColor)
{
	_lazyInitializeShader();
	std::cout << "Color: " << _diffuseColor << std::endl;
}

PBRColorMaterial::~PBRColorMaterial()
{
}

void PBRColorMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	if (_shader) {
		_shader->use();
		if (pWorld->getLightCount() > 0) {
			for (int i = 0; i < pWorld->getLightCount(); i++) {
				Light* light = pWorld->getLightAt(i);
				glUniform3fv(_shader->getUniformLocation("pointLightColors["+std::to_string(i)+']'), 1, glm::value_ptr(light->getLightColor()));
				glUniform3fv(_shader->getUniformLocation("pointLightPositions["+std::to_string(i)+']'), 1, glm::value_ptr(light->getLocalPosition()));
				glUniform3fv(_shader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(pWorld->getMainCamera()->getWorldPosition()));
			}
		}

		//set the material color
		glUniform3fv(_shader->getUniformLocation("albedoColor"), 1, glm::value_ptr(_diffuseColor));
		glUniform1f(_shader->getUniformLocation("metallic"), 0.5f);
		glUniform1f(_shader->getUniformLocation("roughness"), 0.5f);
		glUniform1f(_shader->getUniformLocation("ao"), 1.0f);

		//pass in all MVP matrices separately
		glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
		glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
		glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	}

	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		-1
	);
}

void PBRColorMaterial::setDiffuseColor(glm::vec3 color)
{
	_diffuseColor = color;
}

void PBRColorMaterial::_lazyInitializeShader()
{
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "pbr_color.vert");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "pbr_color.frag");
		_shader->finalize();
	}
}
