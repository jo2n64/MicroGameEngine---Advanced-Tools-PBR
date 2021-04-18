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
#include "mge/materials/PBRColorMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/CameraBehaviour.hpp"
#include "mge/behaviours/LightBehaviour.hpp"

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

	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane20x20_2tris_aligned_uvs.obj");
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	int cols = 7;
	int rows = 7;
	float spacing = 0.8f;

	//AbstractMaterial* grayMaterial = new ColorMaterial(glm::vec3(0.3, 0.2, 0.4));
	AbstractMaterial* randomMaterial = new ColorMaterial(glm::vec3(1, 0, 0));
	//AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));*/
	AbstractMaterial* pbrTestMaterial = new PBRColorMaterial(glm::vec3(1,0,1));
	//AbstractMaterial* lightMaterial = new LightMaterial(glm::vec3(1, 1, 0));

	Camera* cam = new Camera("camera", glm::vec3(0, 1, 7));
	//cam->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	cam->setPitch(40.0f);
	cam->setBehaviour(new CameraBehaviour(3.0f,10.0f,30.0f, cam));
	_world->add(cam);
	_world->setMainCamera(cam);

	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	//plane->scale(glm::vec3(5, 1, 5));
	plane->scale(glm::vec3(0.5f, 0.5f, 0.5f));
	plane->setMesh(planeMesh);
	plane->setMaterial(pbrTestMaterial);
	_world->add(plane);

	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			std::string numCube = std::to_string(row) + std::to_string(col);
			GameObject* cube = new GameObject("cube"+numCube, glm::vec3(-4.0f + col * spacing , 0.4f + row * spacing, -4.0f));
			cube->setMesh(cubeMesh);
			cube->scale(glm::vec3(0.2f, 0.2f, 0.2f));
			cube->setMaterial(pbrTestMaterial);
			_world->add(cube);
		}
	}
	

	Light* light = new Light("light", glm::vec3(0.0f, 1.0f, -3.0f));
	light->scale(glm::vec3(2, 2, 2));
	light->setLightColor(glm::vec3(1, 1, 1));
	light->setBehaviour(new LightBehaviour());
	_world->add(light);

	Light* light2 = new Light("light", glm::vec3(0, 1.0f, 4));
	light2->scale(glm::vec3(2, 2, 2));
	light2->setLightColor(glm::vec3(1, 1, 1));
	light2->setBehaviour(new LightBehaviour());
	_world->add(light2);

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
