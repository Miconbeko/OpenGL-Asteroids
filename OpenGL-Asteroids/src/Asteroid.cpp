#include "../inc/Asteroid.h"

namespace Asteroids
{
	void Asteroid::draw()
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
		glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
		glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

		glPushMatrix();
		glRotatef(90, -1, 0, 0);
		glTranslatef(getXCenter(), getYCenter(), getZCenter());
		glRotatef(getAngle(), getRotateVectorX(), getRotateVectorY(), getRotateVectorZ());
		glutSolidSphere(getXSize() / 2, getPolygones(), getPolygones());
		glPopMatrix();
	}
}