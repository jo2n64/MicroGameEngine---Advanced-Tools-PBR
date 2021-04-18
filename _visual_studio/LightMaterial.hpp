#include "mge/materials/AbstractMaterial.hpp"
#include "glm.hpp"
#include "mge/core/ShaderProgram.hpp"

#pragma once
class LightMaterial : public AbstractMaterial
{
	public:
		LightMaterial(glm::vec3 pDiffuseColor, glm::vec3 pAmbientColor);
		virtual ~LightMaterial();
		virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
		void setDiffuseColor(glm::vec3 pDiffuseColor);
		void setAmbientColor(glm::vec3 pAmbientColor);
	private:
		glm::vec3 _diffuseColor;
		glm::vec3 _ambientColor;
		float _specularStrength;

		static ShaderProgram* _shader;
		static void _lazyInitializeShader();
};

