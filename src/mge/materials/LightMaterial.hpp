#include "mge/materials/AbstractMaterial.hpp"
#include "glm.hpp"
#include "mge/core/ShaderProgram.hpp"

#pragma once
class LightMaterial : public AbstractMaterial
{
	public:
		LightMaterial(glm::vec3 pLightColor);
		virtual ~LightMaterial();
		virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
		//void setDiffuseColor(const glm::vec3 pDiffuseColor);
		//void setAmbientColor(const glm::vec3 pAmbientColor);
		//void setLightColor(const glm::vec3 pLightColor);
		//void setLightPosition(const glm::vec3 pLightPosition);
		//void setSpecularIntensity(const float pSpecIntensity);
	private:
		//glm::vec3 _diffuseColor;
		//glm::vec3 _ambientColor;
		glm::vec3 _lightColor;
		//glm::vec3 _lightPosition;
	 //   float _specularStrength;

		static ShaderProgram* _shader;
		static void _lazyInitializeShader();
};

