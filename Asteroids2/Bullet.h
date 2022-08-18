#pragma once
#include "Object.h"

#include <gl/glut.h>

#include "utils.h"

namespace Asteroids
{
	class Bullet : public Object
	{
	private:
		int lifetime;
	public:
		Bullet(
			float xCenter, float yCenter, float zCenter,
			float xSize, float ySize, float zSize,
			float* diffColor, float* ambiColor, float* specColor,
			float xSpeed = 0, float ySpeed = 0, float polygones = 50,
			float rotateSpeed = 0, float angle = 0, float rotateVectorX = 0, float rotateVectorY = 0, float rotateVectorZ = 0,
			int lifetime = 100)
			: Object(xCenter, yCenter, zCenter,
				xSize, ySize, zSize,
				diffColor, ambiColor, specColor,
				xSpeed, ySpeed, polygones,
				rotateSpeed, angle, rotateVectorX, rotateVectorY, rotateVectorZ), lifetime(lifetime) {}

		int getLifeTime() const { return lifetime; }
		void setLifeTime(int lifetime) { this->lifetime = lifetime; }

		virtual void draw();
	};
}
