#pragma once
#include "Object.h"

#include <gl/glut.h>

#include "utils.h"

namespace Asteroids
{
	class Rocket : public Object
	{
	public:
		Rocket(
			float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize,
			float* diffColor, float* ambiColor, float* specColor,
			float xSpeed = 0, float ySpeed = 0, float polygones = 50,
			float rotateSpeed = 0, float angle = 0, float rotateVectorX = 0, float rotateVectorY = 0, float rotateVectorZ = 0)
			: Object(xCenter, yCenter, zCenter,
				xSize, ySize, zSize,
				diffColor, ambiColor, specColor,
				xSpeed, ySpeed, polygones,
				rotateSpeed, angle, rotateVectorX, rotateVectorY, rotateVectorZ) {}

		virtual void draw();
	};
}


