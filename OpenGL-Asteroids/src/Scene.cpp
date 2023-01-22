#define _CRT_SECURE_NO_WARNINGS

#include "../inc/Scene.h"

namespace Asteroids
{
    using namespace GraphUtils;

    Scene::Scene()
    {
        srand(time(0));
        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

        asteroidSpawnValue -= asteroidSpawnValueDelta;

        createRocket();
    }

    void Scene::calcAll()
    {
        if (isAcceleration)
        {
            rocket->setSpeed(
                rocket->getXSpeed() + rocketDeltaSpeed * rocket->calcAngleMultiply(true),
                rocket->getYSpeed() + rocketDeltaSpeed * rocket->calcAngleMultiply(false));
            createThrustParticles(rocket);
        }
        else
        {
            float xS = rocket->getXSpeed();
            float yS = rocket->getYSpeed();

            if (xS > rocketStopSpeed)
                rocket->setXSpeed(xS - rocketStopSpeed);
            else if (xS < -rocketStopSpeed)
                rocket->setXSpeed(xS + rocketStopSpeed);
            else rocket->setXSpeed(0);

            if (yS > rocketStopSpeed)
                rocket->setYSpeed(yS - rocketStopSpeed);
            else if (yS < -rocketStopSpeed)
                rocket->setYSpeed(yS + rocketStopSpeed);
            else rocket->setYSpeed(0);
        }

        if (isLeftRotate)
            rocket->setRotateSpeed(-rocketRotateSpeed);
        else if (isRightRotate)
            rocket->setRotateSpeed(rocketRotateSpeed);
        else rocket->setRotateSpeed(0);

        calcBulletAsteroidCollision();
        calcBulletBorderCollision();
        calcAsteroidRocketCollision();
        calcParticleLifeTime();

        DeleteDeadBullets();
        DeleteDeadAsteroids();
        DeleteDeadParticles();
        DeleteDeadObjects();

        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->calcCoords();
        }
        outBorderCheck();
    }

    void Scene::drawLifes()
    {
        Rocket lifeRocket(
            -gameWidth + gameWidth / 100 * 5,
            0,
            gameHeight - gameHeight / 100 * 10,
            rocketRadius * 1.5, rocketHeight / 1.5, rocketRadius * 1.5, diffYellow, ambiYellow, specYellow);

        for (int i = 0; i < rocketLifes; i++)
        {
            lifeRocket.draw();
            lifeRocket.setXCenter(lifeRocket.getXCenter() + rocketRadius * 2);
        }
    }

    void Scene::calcBulletAsteroidCollision()
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            for (int x = 0; x < asteroids.size(); x++)
            {
                if (bullets[i]->isCollision(asteroids[x]))
                {
                    bullets[i]->setIsDead();
                    asteroids[x]->setIsDead();
                    createDeathParticles(bullets[i]);
                    createDeathParticles(asteroids[x]);
                    if (asteroids[x]->getLevel() > 0)
                        splitAsteroid(asteroids[x]);
                }
            }
        }
    }

    void Scene::calcAsteroidRocketCollision()
    {
        for (int i = 0; i < asteroids.size(); i++)
        {
            if (rocket->isCollision(asteroids[i]))
            {
                rocket->setIsDead();
                createDeathParticles(rocket);
            }
        }
    }

    void Scene::calcParticleLifeTime()
    {
        for (int i = 0; i < particles.size(); i++)
        {
            if (particles[i]->getLifeTime() < ticks)
            {
                particles[i]->setIsDead();
            }
        }
    }

    void Scene::splitAsteroid(Asteroid* asteroid)
    {
        for (int i = 0; i < asteroidSplitValue; i++)
        {
            createAsteroid(
                asteroid->getXCenter(), asteroid->getYCenter(), asteroid->getZCenter(),
                asteroid->getAngle() + asteroidDeltaAngleSplit * getRandomFloat(-1, 1),
                asteroid->getLevel() - 1);
        }
    }

    void Scene::calcBulletBorderCollision()
    {
        float deltaBorder = 0.05;

        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->getXCenter() >= gameWidth - deltaBorder ||
                bullets[i]->getXCenter() <= -gameWidth + deltaBorder ||
                bullets[i]->getZCenter() >= gameHeight - deltaBorder ||
                bullets[i]->getZCenter() <= -gameHeight + deltaBorder)
            {
                bullets[i]->setIsDead();
            }
        }
    }

    void Scene::Draw()
    {
        char scoreString[64];
        char gamenameString[64];
        char rulesString[64];
        char toStartString[64];
        char stageString[64];
        char overString[64];

        sprintf(scoreString, "Score: %d", score);
        sprintf(gamenameString, "ASTEROIDS");
        sprintf(rulesString, "Controls: | ARROWS for move | SPACE for shoot | ESC to exit");
        sprintf(toStartString, "Shoot to start");
        sprintf(stageString, "Stage %d, get ready pilot!", stage);
        sprintf(overString, "Game Over! Your score: %d", score);

        calcAll();

        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);

        glLoadIdentity();
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(perspectiveAngle, width / height, 1, 5);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, cameraZDistance);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->draw();
        }

        if (!isStartScreen && !isStageScreen && !isOver)
            drawLifes();

        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        if (!isStartScreen && !isStageScreen && !isOver)
        {
            glPushMatrix();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 1, 0, 1, 0, 1);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3fv(specYellow);
            drawString(GLUT_BITMAP_HELVETICA_18, scoreString, 0.01, 0.97);

            glPopMatrix();
        }

        if (isStartScreen)
        {
            glPushMatrix();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 1, 0, 1, 0, 1);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3fv(diffLightBlue);
            drawString(GLUT_BITMAP_HELVETICA_18, gamenameString, 0.44, 0.6);
            glColor3fv(diffViolet);
            drawString(GLUT_BITMAP_HELVETICA_12, rulesString, 0.30, 0.4);
            glColor3fv(diffViolet);
            drawString(GLUT_BITMAP_HELVETICA_12, toStartString, 0.46, 0.37);

            glPopMatrix();
        }

        if (isStageScreen)
        {
            glPushMatrix();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 1, 0, 1, 0, 1);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3fv(diffGreen);
            drawString(GLUT_BITMAP_HELVETICA_18, stageString, 0.39, 0.6);

            glPopMatrix();
        }
        if (isOver)
        {
            glPushMatrix();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 1, 0, 1, 0, 1);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glColor3fv(diffRed);
            drawString(GLUT_BITMAP_HELVETICA_18, overString, 0.39, 0.6);

            glPopMatrix();
        }

        glFlush();

        glutSwapBuffers();
    }

    void Scene::Reshape(int width, int height)
    {
        if (width == 0)
            width = 1;
        if (height == 0)
            height = 1;
        this->width = width;
        this->height = height;
        gameWidth = -cameraZDistance * tan(perspectiveAngle / 2 * 3.14 / 180.0);
        gameHeight = -cameraZDistance * tan(perspectiveAngle / 2 * 3.14 / 180.0);
        glViewport(0, 0, width, height);
    }

    void Scene::SpecialKeyDown(int key)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            isAcceleration = true;
            break;
        case GLUT_KEY_LEFT:
            isLeftRotate = true;
            break;
        case GLUT_KEY_RIGHT:
            isRightRotate = true;
            break;
        }
    }

    void Scene::SpecialKeyUp(int key)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            isAcceleration = false;
            break;
        case GLUT_KEY_LEFT:
            isLeftRotate = false;
            break;
        case GLUT_KEY_RIGHT:
            isRightRotate = false;
            break;
        }
    }

    void Scene::Keyboard(unsigned char key)
    {
        switch (key)
        {
        case 32:
            shoot();
            break;
        case 27:
            exit(0);
            break;
        }
    }

    void Scene::Timer(int value)
    {
        ticks++;
        if (rocketLifes == 0 && bool(rocket->getIsDead()))
            isOver = true;
        if (asteroids.empty() && isStartScreen == false)
            isStageScreen = true;
        if ((asteroids.empty() || bool(rocket->getIsDead())) && isStartScreen == false)
        {
            if (newLevelInitTime < ticks)
            {
                newLevelInitTime = ticks + newLevelInitDelay;
            }
            if (newLevelInitTime == ticks)
            {
                if (rocketLifes == 0 && bool(rocket->getIsDead()))
                {
                    DeleteAllObjects();

                    stage = 0;
                    score = 0;
                    ticks = 0;
                    newLevelInitTime = 0;
                    rocketLifes = startRocketLifes;
                    asteroidSpawnValue = asteroidStartSpawnValue;

                    isOver = false;
                    isStartScreen = true;
                    isStageScreen = false;

                    createRocket();
                }
                else
                {
                    isStageScreen = false;
                    initializeLevel();
                }
            }
        }
    }

    void Scene::DeleteDeadBullets()
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->getIsDead())
                bullets.erase(bullets.begin() + i);
        }
    }

    void Scene::DeleteDeadAsteroids()
    {
        for (int i = 0; i < asteroids.size(); i++)
        {
            if (asteroids[i]->getIsDead())
            {
                score += (asteroids[i]->getLevel() + 1) * 100;
                asteroids.erase(asteroids.begin() + i);
            }
        }
    }

    void Scene::DeleteDeadParticles()
    {
        for (int i = 0; i < particles.size(); i++)
        {
            if (particles[i]->getIsDead())
                particles.erase(particles.begin() + i);
        }
    }

    void Scene::DeleteDeadObjects()
    {
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->getIsDead())
            {
                delete objects[i];
                objects.erase(objects.begin() + i);
            }
        }
    }

    void Scene::shoot()
    {
        isStartScreen = false;
        if (bulletMaxValue > bullets.size())
        {
            Bullet* bullet = new Bullet(rocket->getXCenter(), rocket->getYCenter(), rocket->getZCenter(), bulletRadius * 2, bulletRadius * 2, bulletRadius * 2, diffRed, ambiRed, specRed);

            bullet->setAngle(rocket->getAngle());
            bullet->setSpeed(
                rocket->getXSpeed() + bulletSpeed * bullet->calcAngleMultiply(true),
                rocket->getYSpeed() + bulletSpeed * bullet->calcAngleMultiply(false));
            bullet->setLifeTime(bullet->getLifeTime() + ticks);

            bullets.push_back(bullet);
            objects.push_back(bullet);
        }
    }

    void Scene::outBorderCheck()
    {
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->getXCenter() > gameWidth)
                objects[i]->setXCenter(-gameWidth);
            else if (objects[i]->getXCenter() < -gameWidth)
                objects[i]->setXCenter(gameWidth);
            if (objects[i]->getZCenter() > gameHeight)
                objects[i]->setZCenter(-gameHeight);
            else if (objects[i]->getZCenter() < -gameHeight)
                objects[i]->setZCenter(gameHeight);
        }
    }

    void Scene::createRocket()
    {
        rocket = new Rocket(0, 0, 0, rocketRadius * 2, rocketHeight, rocketRadius * 2, diffWhite, ambiWhite, specWhite);
        rocket->setRotateVector(0, 1, 0);

        objects.push_back(rocket);
    }

    void Scene::complicateLevel()
    {
        stage++;
        asteroidSpawnValue += asteroidSpawnValueDelta;
    }

    void Scene::DeleteAllObjects()
    {
        int objectsSize = objects.size();

        bullets.clear();
        asteroids.clear();
        particles.clear();
        for (int i = 0; i < objectsSize; i++)
        {
            delete objects[0];
            objects.erase(objects.begin());
        }
    }

    void Scene::initializeLevel()
    {
        float x, z;

        if (asteroids.empty())
            complicateLevel();

        if (bool(rocket->getIsDead()))
        {
            DeleteAllObjects();

            rocketLifes--;
            createRocket();
        }

        for (int i = 0; i < asteroidSpawnValue; i++)
        {
            if (getRandomInt(0, 1))
            {
                x = (-gameWidth * 2 * getRandomInt(0, 1)) + getRandomFloat(gameWidth / 100 * (100 - asteroidDistFromBorder), gameWidth);
                z = getRandomFloat(-gameHeight, gameHeight);
            }
            else
            {
                x = getRandomFloat(-gameWidth, gameWidth);
                z = (-gameHeight * 2 * getRandomInt(0, 1)) + getRandomFloat(gameHeight / 100 * (100 - asteroidDistFromBorder), gameHeight);
            }
            createAsteroid(x, 0, z, getRandomInt(0, 360), 2);
        }
    }

    void Scene::setRocketStartPosition()
    {
        rocket->setCoords(0, 0, 0);
        rocket->setAngle(0);
        rocket->setSpeed(0, 0);
    }

    void Scene::createAsteroid(float x, float y, float z, float angle, int level)
    {
        Asteroid* asteroid = new Asteroid(x, y, z, asteroidRadius[level] * 2, asteroidRadius[level] * 2, asteroidRadius[level] * 2, diffGray, ambiGray, specGray);
        float asteroidSpeed = getRandomFloat(asteroidMinSpeed[level], asteroidMaxSpeed[level]);

        asteroid->setLevel(level);
        asteroid->setAngle(angle);
        asteroid->setRotateSpeed(getRandomFloat(asteroidMinRotateSpeed[level], asteroidMaxRotateSpeed[level]));
        asteroid->setRotateVector(getRandomFloat(-1, 1), getRandomFloat(-1, 1), getRandomFloat(-1, 1));
        asteroid->setSpeed(
            asteroidSpeed * asteroid->calcAngleMultiply(true),
            asteroidSpeed * asteroid->calcAngleMultiply(false));
        asteroid->setPolygones(getRandomInt(asteroidMinPolygones, asteroidMaxPolygones));

        asteroids.push_back(asteroid);
        objects.push_back(asteroid);
    }

    void Scene::createDeathParticles(Object* obj)
    {
        Bullet* particle;
        float particleSpeed;

        for (int i = 0; i < max(max(obj->getXSize(), obj->getYSize()), obj->getZSize()) / particleDeathDensity; i++)
        {
            particleSpeed = getRandomFloat(particleMinSpeed, particleMaxSpeed);
            particle = new Bullet(
                obj->getXCenter(), obj->getYCenter(), obj->getZCenter(),
                particleDeathRadius * 2, particleDeathRadius * 2, particleDeathRadius * 2,
                obj->getDiffColor(), obj->getAmbiColor(), obj->getSpecColor());

            particle->setLifeTime(ticks + particle->getLifeTime() + particleDespawnTimeDelta * getRandomFloat(-1, 1));
            particle->setAngle(getRandomInt(0, 360));
            particle->setSpeed(
                particleSpeed * particle->calcAngleMultiply(true),
                particleSpeed * particle->calcAngleMultiply(false));
            particle->setPolygones(particlePolygones);

            particles.push_back(particle);
            objects.push_back(particle);
        }
    }

    void Scene::createThrustParticles(Object* obj)
    {
        Bullet* particle;
        float particleSpeed, lifeTime;
        float angleMultiplyX = obj->calcAngleMultiply(true);
        float angleMultiplyY = obj->calcAngleMultiply(false);
        float heightDivisor = 2;

        for (int i = 0; i < particleThrustValue; i++)
        {
            particle = new Bullet(
                obj->getXCenter() - (obj->getYSize() / heightDivisor) * angleMultiplyX + rocketRadius / 100 * 90 * getRandomFloat(-1, 1),
                obj->getYCenter() + rocketRadius / 100 * 90 * getRandomFloat(-1, 1),
                obj->getZCenter() - (obj->getYSize() / heightDivisor) * angleMultiplyY + rocketRadius / 100 * 90 * getRandomFloat(-1, 1),
                particleThrustRadius * 2, particleThrustRadius * 2, particleThrustRadius * 2,
                diffLightBlue, ambiLightBlue, specLightBlue);
            particleSpeed = getRandomFloat(particleMinSpeed, particleMaxSpeed);
            lifeTime = particle->getLifeTime() + particleDespawnTimeDelta * getRandomFloat(-1, 1) + particleSpeed * 10000;

            particle->setLifeTime(ticks + lifeTime);
            particle->setAngle(obj->getAngle() + 180);
            particle->setSpeed(
                particleSpeed * particle->calcAngleMultiply(true) + obj->getXSpeed(),
                particleSpeed * particle->calcAngleMultiply(false) + obj->getYSpeed());
            particle->setPolygones(particlePolygones);

            particles.push_back(particle);
            objects.push_back(particle);
        }
    }

    float Scene::getRandomFloat(float min, float max)
    {
        return min + float(float(rand()) / float((RAND_MAX)) * (max - min));
    }

    int Scene::getRandomInt(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }
}