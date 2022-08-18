#include "Rocket.h"

namespace Asteroids
{
	void Rocket::draw()
	{
		float angleMultiplyX = calcAngleMultiply(true);
		float angleMultiplyY = calcAngleMultiply(false);
		float heightDivisor = 2;

		glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
		glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
		glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

		glPushMatrix();
		glRotatef(90, -1, 0, 0);
		setZCenter(getZCenter() - (getYSize() / heightDivisor) * angleMultiplyY);
		setXCenter(getXCenter() - (getYSize() / heightDivisor) * angleMultiplyX);
		glTranslatef(getXCenter(), getYCenter(), getZCenter());
		setZCenter(getZCenter() + (getYSize() / heightDivisor) * angleMultiplyY);
		setXCenter(getXCenter() + (getYSize() / heightDivisor) * angleMultiplyX);
		glRotatef(getAngle(), getRotateVectorX(), getRotateVectorY(), getRotateVectorZ());
		glutSolidCone(getXSize() / 2, getYSize(), getPolygones(), getPolygones());
		glPopMatrix();
	}
}