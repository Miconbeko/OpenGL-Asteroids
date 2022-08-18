#pragma once
#include <gl/glut.h>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <ctime>
#include <string>

#include "Object.h"
#include "Rocket.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "utils.h"

using std::vector;
using std::string;


namespace Asteroids
{
	class Scene
	{
	private:
		int framesDelay = 5;
		unsigned long long int ticks = 0;

		const float perspectiveAngle = 60;
		const float cameraZDistance = -3;
		const int newLevelInitDelay = 500;
		int newLevelInitTime = newLevelInitDelay;
		int gameLevel = 0;
		unsigned long long int score = 0;
		int stage = 0;
		bool isStageScreen = false;
		bool isStartScreen = true;
		bool isOver = false;

		const float rocketRadius = 0.04;
		const float rocketHeight = 0.1;
		const double rocketDeltaSpeed = 0.00003;
		const float rocketRotateSpeed = 1.3;
		const double rocketStopSpeed = rocketDeltaSpeed / 1.5;
		const int startRocketLifes = 3;
		int rocketLifes = startRocketLifes;

		const float asteroidRadius[3] = { 0.04, 0.07, 0.1 };
		const float asteroidMaxSpeed[3] = { 0.006, 0.005, 0.004 };
		const float asteroidMinSpeed[3] = { 0.002, 0.002, 0.002 };
		const float asteroidMaxRotateSpeed[3] = { 3,2,1 };
		const float asteroidMinRotateSpeed[3] = { 0.3, 0.3, 0.3 };
		const int asteroidMinPolygones = 3;
		const int asteroidMaxPolygones = 5;
		const float asteroidDistFromBorder = 20;
		const float asteroidDeltaAngleSplit = 50;
		const int asteroidSplitValue = 2;
		const int asteroidSpawnValueDelta = 1;
		const int asteroidStartSpawnValue = 6;
		int asteroidSpawnValue = asteroidStartSpawnValue;

		const float bulletRadius = 0.025;
		const float bulletSpeed = 0.03;
		const int bulletMaxValue = 5;

		const float particleDeathRadius = 0.01;
		const float particleMaxSpeed = 0.003;
		const float particleMinSpeed = 0.001;
		const float particlePolygones = 3;
		const float particleDeathDensity = 0.006;
		const float particleDespawnTimeDelta = 50;
		const float particleAngleDelta = 20;
		const float particleThrustRadius = 0.005;
		const float particleThrustValue = 2;

		float lightAmbient[4] = { 0, 0, 0, 1 };
		float lightDiffuse[4] = { 1, 1, 1, 1 }; 
		float lightSpecular[4] = { 1, 1, 1, 1 };
		float lightPosition[4] = { 2, 1, 1, 0 };

		bool isAcceleration = false;
		bool isLeftRotate = false;
		bool isRightRotate = false;

		float gameWidth, gameHeight;
		float width, height;
		vector<Object*> objects;
		vector<Bullet*> particles;
		vector<Asteroid*> asteroids;
		vector<Bullet*> bullets;
		Rocket* rocket;
	public:
		Scene();

		int getFramesDelay() const { return framesDelay; }

		void Draw();
		void drawLifes();
		void Reshape(int width, int height);
		void SpecialKeyDown(int key);
		void SpecialKeyUp(int key);
		void Keyboard(unsigned char key);
		void Timer(int value);
		
		void calcAll();

		void DeleteDeadBullets();
		void DeleteDeadAsteroids();
		void DeleteDeadObjects();
		void DeleteDeadParticles();
		void DeleteAllObjects();

		void initializeLevel();
		void complicateLevel();
		void setRocketStartPosition();

		void calcBulletAsteroidCollision();
		void calcBulletBorderCollision();
		void calcAsteroidRocketCollision();
		void calcParticleLifeTime();
		void outBorderCheck();

		void splitAsteroid(Asteroid* asteroid);
		void createAsteroid(float x, float y, float z, float angle, int level);
		void createDeathParticles(Object* obj);
		void createThrustParticles(Object* obj);
		void createRocket();
		void shoot();

		float getRandomFloat(float min, float max);
		int getRandomInt(int min, int max);
		float calcDeltaMultiply(int angle, bool isForX);

	};
}

