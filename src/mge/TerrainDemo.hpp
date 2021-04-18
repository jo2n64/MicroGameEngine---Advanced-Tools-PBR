#include "mge/core/AbstractGame.hpp"
#pragma once

class TerrainDemo : public AbstractGame
{
	public:
		TerrainDemo();
		virtual ~TerrainDemo();
		virtual void initialize();
	protected:
		virtual void _initializeScene();
		virtual void _processEvents();
	private:
		TerrainDemo(const TerrainDemo&);
		TerrainDemo& operator=(const TerrainDemo&);
};

