#include "mge/core/AbstractGame.hpp"

class DebugHud;

#pragma once
class ADSDemo : public AbstractGame
{
	public:
		ADSDemo();
		virtual ~ADSDemo();

		virtual void initalize();
	protected:
		virtual void _initializeScene();
		virtual void _render();
		virtual void _processEvents();

	private:
		ADSDemo(const ADSDemo&);
		ADSDemo& operator=(const ADSDemo&);
};

