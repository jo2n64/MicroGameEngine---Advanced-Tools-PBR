#pragma once
#include "mge/behaviours/AbstractBehaviour.hpp"
class LightBehaviour :  public AbstractBehaviour
{
	public:
		LightBehaviour();
		virtual ~LightBehaviour();
		virtual void update(float pStep);

};

