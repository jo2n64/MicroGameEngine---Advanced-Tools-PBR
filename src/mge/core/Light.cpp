#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/LightMaterial.hpp"

Light::Light(const std::string& pName, const glm::vec3& pPosition):GameObject(pName, pPosition)
{
}

Light::~Light() {
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively (World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}

void Light::setLightColor(const glm::vec3 pLightColor)
{
    _lightColor = pLightColor;
}

void Light::setAmbientColor(const glm::vec3 pAmbientColor)
{
    _ambientColor = pAmbientColor;
}

void Light::setSpecularIntensity(const float pSpecIntensity)
{
    _specularIntensity = pSpecIntensity;
}

void Light::setAmbientIntensity(const float pAmbientIntensity)
{
    _ambientIntensity = pAmbientIntensity;
}

glm::vec3 Light::getLightColor() const
{
    return _lightColor;
}

glm::vec3 Light::getAmbientColor() const
{
    return _ambientColor;
}


float Light::getAmbientIntensity() const
{
    return _ambientIntensity;
}

float Light::getSpecularIntensity() const
{
    return _specularIntensity;
}


