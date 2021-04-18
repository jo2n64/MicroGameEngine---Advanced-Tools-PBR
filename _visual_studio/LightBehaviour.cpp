#include "LightBehaviour.hpp"
#include "mge/core/GameObject.hpp"

LightBehaviour::LightBehaviour()
{
}

LightBehaviour::~LightBehaviour()
{
}

void LightBehaviour::update(float pStep)
{
	_owner->translate(glm::vec3(0,2,5));
	_owner->rotate(clock() / 3000.0f * pStep, glm::vec3(0, 1, 0));
}
