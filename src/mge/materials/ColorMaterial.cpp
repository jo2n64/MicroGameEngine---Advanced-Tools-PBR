#include "glm.hpp"

#include "ColorMaterial.hpp"
#include "mge/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Light.hpp"

ShaderProgram* ColorMaterial::_shader = NULL;

ColorMaterial::ColorMaterial(glm::vec3 pDiffuseColor) : _diffuseColor(pDiffuseColor)
{
    _lazyInitializeShader();
    std::cout << "Diffuse color of material: " << _diffuseColor << std::endl;
}

void ColorMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"color.vert");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"color.frag");
        _shader->finalize();
    }
}

ColorMaterial::~ColorMaterial()
{
    //dtor
}

void ColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void ColorMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    _shader->use();
    
	if (pWorld->getLightCount() > 0) {
		Light* light = pWorld->getLightAt(0);

        glUniform3fv(_shader->getUniformLocation("ambientColor"), 1, glm::value_ptr(light->getAmbientColor()));
        glUniform3fv(_shader->getUniformLocation("pointLightColor"), 1, glm::value_ptr(light->getLightColor()));
        glUniform3fv(_shader->getUniformLocation("pointLightPosition"), 1, glm::value_ptr(light->getLocalPosition()));
        glUniform3fv(_shader->getUniformLocation("cameraPosition"), 1, glm::value_ptr(pWorld->getMainCamera()->getWorldPosition()));

		glUniform1f(_shader->getUniformLocation("ambientIntensity"), light->getAmbientIntensity());
		glUniform1f(_shader->getUniformLocation("specularIntensity"), light->getSpecularIntensity());

		//std::cout << "ColorMaterial found a light at position: " << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	}

    //set the material color
    glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));

    //pass in all MVP matrices separately
    glUniformMatrix4fv ( _shader->getUniformLocation("projectionMatrix"),   1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv ( _shader->getUniformLocation("viewMatrix"),         1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv ( _shader->getUniformLocation("modelMatrix"),        1, GL_FALSE, glm::value_ptr(pModelMatrix));

	

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(
        _shader->getAttribLocation("vertex"),
        _shader->getAttribLocation("normal"),
        -1
    );
    //pMesh->drawDebugInfo(pModelMatrix, pViewMatrix, pProjectionMatrix);

}
