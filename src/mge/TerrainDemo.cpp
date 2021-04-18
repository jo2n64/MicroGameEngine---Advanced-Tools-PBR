#include "TerrainDemo.hpp"
#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LightMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/CameraBehaviour.hpp"
#include "mge/behaviours/LightBehaviour.hpp"

#include "mge/config.hpp"

TerrainDemo::TerrainDemo()
{
}

TerrainDemo::~TerrainDemo()
{
}

void TerrainDemo::initialize()
{
	AbstractGame::initialize();
}

void TerrainDemo::_initializeScene()
{
	
	TerrainMaterial* randomMaterial = new TerrainMaterial(4.0f, 10.0f);
	
	randomMaterial->setHeightmapTexture(Texture::load(config::MGE_TEXTURE_PATH + "terrain/heightmap.png"));

	//just setting a single diffuse texture (for now)
	randomMaterial->setDiffuseTexture1(Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse1.jpg"));
	randomMaterial->setDiffuseTexture2(Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse2.jpg"));
	randomMaterial->setDiffuseTexture3(Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse3.jpg"));
	randomMaterial->setDiffuseTexture4(Texture::load(config::MGE_TEXTURE_PATH + "terrain/diffuse4.jpg"));

	randomMaterial->setSplatmapTexture(Texture::load(config::MGE_TEXTURE_PATH + "terrain/splatmap.png"));

	//adding diffuse textures in a vector, then looping through them in the render function of the material

	Mesh* randomMesh = Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj");

	Camera* camera = new Camera("camera", glm::vec3(0, 5, 12.0f));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	camera->setBehaviour(new CameraBehaviour(30.0f, 10.0f, 50.0f, camera));
	camera->setPitch(40.0f);
	_world->setMainCamera(camera);
	_world->add(camera);

	GameObject* plane = new GameObject("plane");
	plane->setMesh(randomMesh);
	plane->scale(glm::vec3(7,1,7));
	plane->setBehaviour(new RotatingBehaviour());
	plane->setMaterial(randomMaterial);
	_world->add(plane);

	Light* light = new Light("light", glm::vec3(0, 6, 4));
	light->scale(glm::vec3(2, 2, 2));
	light->setLightColor(glm::vec3(1, 1, 1));
	light->setAmbientColor(glm::vec3(0, 0, 0));
	light->setAmbientIntensity(1.0f);
	light->setSpecularIntensity(1024.0f);
	light->setBehaviour(new LightBehaviour());
	_world->add(light);
}

void TerrainDemo::_processEvents()
{
	AbstractGame::_processEvents();
}
