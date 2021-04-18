#ifndef PBRMATERIAL_HPP
#define PBRMATERIAL_HPP


#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"

class ShaderProgram;

class PBRColorMaterial : public AbstractMaterial
{
public:
	PBRColorMaterial(glm::vec3 color = glm::vec3(1,0,0));
	virtual ~PBRColorMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
	void setDiffuseColor(glm::vec3 color);

private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	glm::vec3 _diffuseColor;
};


#endif
