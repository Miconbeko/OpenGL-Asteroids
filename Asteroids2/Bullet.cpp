#include "Bullet.h"

namespace Asteroids
{
	void Bullet::draw()
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, getAmbiColor());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, getDiffColor());
		glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecColor());
		glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);

		glPushMatrix();
		glRotatef(90, -1, 0, 0);
		glTranslatef(getXCenter(), getYCenter(), getZCenter());
		glutSolidSphere(getXSize() / 2, getPolygones(), getPolygones());
		glPopMatrix();
	}
}