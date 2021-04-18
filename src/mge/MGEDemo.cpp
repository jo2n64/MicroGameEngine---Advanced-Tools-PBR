#include <iostream>
#include <string>

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
#include "mge/behaviours/LightBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/MGEDemo.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MGEDemo::MGEDemo():AbstractGame (),_hud(0)
{
}

void MGEDemo::initialize() {
    //setup the core part
    AbstractGame::initialize();
    //setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void MGEDemo::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load (config::MGE_MODEL_PATH+"plane.obj");
    Mesh* cubeMeshF = Mesh::load (config::MGE_MODEL_PATH+"cube_flat.obj");

    Mesh* suzannaMeshS = Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth.obj");
    Mesh* teapotF = Mesh::load(config::MGE_MODEL_PATH + "teapot_flat.obj");

    Mesh* pistolMesh = Mesh::load(config::MGE_MODEL_PATH + "pistol.obj");

    //MATERIALS

    //create some materials to display the cube, the plane and the light
    AbstractMaterial* lightMaterial = new ColorMaterial (glm::vec3(1,1,0));
    AbstractMaterial* sampleMaterial = new ColorMaterial(glm::vec3(1, 0, 0));

	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
    AbstractMaterial* brickMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));

    //SCENE SETUP

   //add camera first (it will be updated last)
    Camera* camera = new Camera ("camera", glm::vec3(0,10,15));
    camera->rotate(glm::radians(-40.0f), glm::vec3(1,0,0));
    camera->setBehaviour(new CameraBehaviour(40.0f, 5.0f, 100.0f, camera));
    camera->setPitch(40.0f);
    //_world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject ("plane", glm::vec3(0,0,0));
    plane->scale(glm::vec3(50,5,50));
    plane->setMesh(planeMeshDefault);
    plane->setMaterial(runicStoneMaterial);
    _world->add(plane);

    GameObject* suzanna = new GameObject("suzanna", glm::vec3(0, 0, 0));
    suzanna->setMesh(suzannaMeshS);
    suzanna->setMaterial(sampleMaterial);
    suzanna->setLocalPosition(glm::vec3(0, 2, 0));
    //_world->add(suzanna);

    GameObject* pistol = new GameObject("pistol", glm::vec3(0, 4, 0));
    pistol->scale(glm::vec3(10, 10, 10));
    pistol->setMesh(pistolMesh);
    pistol->setMaterial(sampleMaterial);

    GameObject* cube = new GameObject("cube", glm::vec3(0, 0, 0));
    cube->setMesh(cubeMeshF);
    cube->setMaterial(brickMaterial);
    cube->setBehaviour(new KeysBehaviour(5));
	cube->add(camera);
	cube->add(suzanna);
    cube->add(pistol);
    _world->add(cube);

}

void MGEDemo::_render() {
    AbstractGame::_render();
    _updateHud();
}

void MGEDemo::_processEvents()
{
    AbstractGame::_processEvents();
}

void MGEDemo::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

MGEDemo::~MGEDemo()
{
	//dtor
}
