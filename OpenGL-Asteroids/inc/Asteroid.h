#pragma once
#include "Object.h"

#include <gl/glut.h>

#include "utils.h"

namespace Asteroids
{
	class Asteroid : public Object
	{
	private:
		int level;
	public:
		Asteroid(
			float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize,
			float* diffColor, float* ambiColor, float* specColor,
			float xSpeed = 0, float ySpeed = 0, float polygones = 50,
			float rotateSpeed = 0, float angle = 0, float rotateVectorX = 0, float rotateVectorY = 0, float rotateVectorZ = 0,
			int level = 2)
			: Object(xCenter, yCenter, zCenter,
				xSize, ySize, zSize,
				diffColor, ambiColor, specColor,
				xSpeed, ySpeed, polygones,
				rotateSpeed, angle)
		{
			this->level = level;
		}

		int		getLevel() const { return level; }
		void	setLevel(int level) { this->level = level; }

		virtual void draw();
	};
}


