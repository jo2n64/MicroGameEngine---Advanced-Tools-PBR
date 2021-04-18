#include "glm.hpp"

#include "TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/config.hpp"

ShaderProgram* TextureMaterial::_shader = NULL;

GLint TextureMaterial::_uMVPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;

TextureMaterial::TextureMaterial(Texture* pDiffuseTexture) :_diffuseTexture(pDiffuseTexture) {
	_lazyInitializeShader();
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
	if (!_shader) {
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH + "texture.vert");
		_shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH + "texture.frag");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		//_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		/*_uModelMatrix = _shader->getUniformLocation("modelMatrix");
		_uViewMatrix = _shader->getUniformLocation("viewMatrix");
		_uProjectionMatrix = _shader->getUniformLocation("projectionMatrix");*/
		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void TextureMaterial::setDiffuseTexture(Texture* pDiffuseTexture) {
	_diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
	if (!_diffuseTexture) return;

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

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	//pass in a precalculate mvp matrix (see texture material for the opposite)
	//glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
	//glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
