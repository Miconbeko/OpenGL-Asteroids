#include <GL/glut.h>
#include <stdlib.h>

#include "../inc/Scene.h"

using Asteroids::Scene;

Scene* scene;

void Reshape(int width, int height)
{
    scene->Reshape(width, height);
}

void SpecialKey(int key, int x, int y)
{
    scene->SpecialKeyDown(key);
}

void SpecialUp(int key, int x, int y)
{
    scene->SpecialKeyUp(key);
}

void Keyboard(unsigned char key, int x, int y)
{
    scene->Keyboard(key);
}

void Draw()
{
    scene->Draw();
}

void Timer(int value)
{
    glutPostRedisplay();
    scene->Timer(value);
    glutTimerFunc(scene->getFramesDelay(), Timer, 0);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    scene = new Scene();
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(350, 10);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Asteroids");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glutSpecialFunc(SpecialKey);
    glutSpecialUpFunc(SpecialUp);
    glutKeyboardFunc(Keyboard);
    glutTimerFunc(scene->getFramesDelay(), Timer, 0);

    glutMainLoop();
    delete scene;
    return 0;
}