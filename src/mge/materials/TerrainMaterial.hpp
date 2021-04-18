#include "AbstractMaterial.hpp"
#include "GL/glew.h"
#include <vector>

class ShaderProgram;
class Texture;

class TerrainMaterial : public AbstractMaterial{
	public:
		TerrainMaterial(float pHeightModifier, float pTilingMultiplier);
		virtual ~TerrainMaterial();

		virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
		
		void setDiffuseColor(const glm::vec3 pDiffuseColor);

		void setDiffuseTexture1(Texture* pDiffuseTexture);
		void setDiffuseTexture2(Texture* pDiffuseTexture);
		void setDiffuseTexture3(Texture* pDiffuseTexture);
		void setDiffuseTexture4(Texture* pDiffuseTexture);

		void setHeightmapTexture(Texture* pHeightmapTexture);
		void setHeightModifier(const float pHeightModifier);
		void setSplatmapTexture(Texture* pSplatmapTexture);


	private:
		static ShaderProgram* _shader;
		static void _lazyInitializeShader();

		static GLint _uMVPMatrix;
		static GLint _uModelMatrix;
		static GLint _uViewMatrix;
		static GLint _uProjectionMatrix;
		static GLint _uDiffuseTexture;
		static GLint _uHeightmapTexture;
		static GLint _uSplatmapTexture;

		static GLint _aVertex;
		static GLint _aNormal;
		static GLint _aUV;

		glm::vec3 _diffuseColor = glm::vec3(1,1,1);
		Texture* _diffuseTexture1;
		Texture* _diffuseTexture2;
		Texture* _diffuseTexture3;
		Texture* _diffuseTexture4;

		Texture* _heightmapTexture;
		Texture* _splatmapTexture;

		float _heightModifier;
		float _tilingMultiplier;

		void _setupTexture(Texture* pDiffuseTexture, int index, std::string uniformLocation);

		TerrainMaterial(const TerrainMaterial&);
		TerrainMaterial& operator=(const TerrainMaterial&);
};