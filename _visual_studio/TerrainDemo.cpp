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

void TerrainDemo::_initializeScene()
{
	_renderer->setClearColor(0, 255, 255);
	AbstractMaterial* randomMaterial = new ColorMaterial(glm::vec3(1,0,1));

	Mesh* randomMesh = Mesh::load(config::MGE_MODEL_PATH + "plane20x20_2tris_aligned_uvs.obj");

	Camera* camera = new Camera("camera", glm::vec3(0, 5, 7));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	camera->setPitch(40.0f);
	_world->setMainCamera(camera);
	_world->add(camera);

	GameObject* plane = new GameObject("plane");
	plane->setMesh(randomMesh);
	plane->setMaterial(randomMaterial);
	_world->add(plane);
}

void TerrainDemo::_processEvents()
{
	AbstractGame::_processEvents();
}
