#include "LightBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Light.hpp"

LightBehaviour::LightBehaviour()
{
}

LightBehaviour::~LightBehaviour()
{
}

void LightBehaviour::update(float pStep)
{
	_owner->setTransform(glm::rotate(glm::radians(60 * pStep), glm::vec3(0,1,0)) * _owner->getTransform());
	//_owner->setTransform(glm::translate(glm::vec3(0, abs(sin(clock() / 1000.0f) * 4.5f), 0)));
	//std::cout << "light pos: " << _owner->getLocalPosition() << std::endl;
}
