#include "ADSDemo.hpp"
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

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/CameraBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"

ADSDemo::ADSDemo() :AbstractGame()
{
}


void ADSDemo::initalize()
{
	AbstractGame::initialize();
}

void ADSDemo::_initializeScene()
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));

	Camera* cam = new Camera("camera", glm::vec3(0,6,10));
	_world->setMainCamera(cam);

	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(50, 5, 50));
	plane->setMesh(planeMesh);
	plane->setMaterial(lightMaterial);
	_world->add(plane);

}

void ADSDemo::_render()
{
	AbstractGame::_render();
}

void ADSDemo::_processEvents()
{
	AbstractGame::_processEvents();
}

ADSDemo::~ADSDemo()
{
}

