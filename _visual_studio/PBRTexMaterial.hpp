#ifndef PBRTEXMATERIAL_HPP
#define PBRTEXMATERIAL_HPP
#include "mge/materials/AbstractMaterial.hpp"
#include "GL/glew.h"


class ShaderProgram;
class Texture;

class PBRTexMaterial : public AbstractMaterial
{
public:
	PBRTexMaterial(Texture* pDiffuseTexture, Texture* pMetallicTexture, Texture* pRoughnessTexture, Texture* pNormalTexture);
	PBRTexMaterial();
	virtual ~PBRTexMaterial();

	virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

	void streamTextureToShader(int textureIndex, Texture* textureToStream, GLint uniformLocation);

	void setDiffuseTexture(Texture* pDiffuseTexture);
	void setMetallicTexture(Texture* pMetallicTexture);
	void setRoughnessTexture(Texture* pRoughnessTexture);
	void setNormalTexture(Texture* pNormalTexture);

private:
	static ShaderProgram* _shader;
	static void _lazyInitializeShader();

	static GLint _uModelMatrix;
	static GLint _uProjectionMatrix;
	static GLint _uViewMatrix;

	static GLint _uDiffuseTexture;
	static GLint _uMetallicTexture;
	static GLint _uRoughnessTexture;
	static GLint _uNormalTexture;

	static GLint _aVertex;
	static GLint _aNormal;
	static GLint _aUV;

	Texture* _diffuseTexture;
	Texture* _metallicTexture;
	Texture* _roughnessTexture;
	Texture* _normalTexture;

	PBRTexMaterial(const PBRTexMaterial&);
	PBRTexMaterial& operator=(const PBRTexMaterial&);
};

#endif

