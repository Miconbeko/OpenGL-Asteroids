#pragma once
#include <iostream>
#include <cmath>

using std::max;
using std::min;

namespace Asteroids
{
    class Object
    {
    private:
        float xCenter, yCenter, zCenter;
        float xSize, ySize, zSize;
        float* diffColor, * ambiColor, * specColor;
        float xSpeed, ySpeed, polygones;
        float rotateSpeed, angle, rotateVectorX, rotateVectorY, rotateVectorZ;
        bool isDead = false;
    public:
        Object(float xCenter, float yCenter, float zCenter,
            float xSize, float ySize, float zSize,
            float* diffColor, float* ambiColor, float* specColor,
            float xSpeed = 0, float ySpeed = 0, float polygones = 50,
            float rotateSpeed = 0, float angle = 0, float rotateVectorX = 0, float rotateVectorY = 0, float rotateVectorZ = 0);

        virtual ~Object() { }
        float  getXCenter() const { return xCenter; }
        float  getYCenter() const { return yCenter; }
        float  getZCenter() const { return zCenter; }
        void   setXCenter(float xCenter) { this->xCenter = xCenter; }
        void   setYCenter(float yCenter) { this->yCenter = yCenter; }
        void   setZCenter(float zCenter) { this->zCenter = zCenter; }
        void   setCoords(float xCenter, float yCenter, float zCenter);
        float  getXSize() const { return xSize; }
        float  getYSize() const { return ySize; }
        float  getZSize() const { return zSize; }
        void   setXSize(float xSize) { this->xSize = xSize; }
        void   setYSize(float ySize) { this->ySize = ySize; }
        void   setZSize(float zSize) { this->zSize = zSize; }
        void   setSize(float xSize, float ySize, float zSize);
        float* getDiffColor() const { return diffColor; }
        float* getAmbiColor() const { return ambiColor; }
        float* getSpecColor() const { return specColor; }
        void   setDiffColor(float* diffColor) { this->diffColor = diffColor; }
        void   setAmbiColor(float* ambiColor) { this->ambiColor = ambiColor; }
        void   setSpecColor(float* specColor) { this->specColor = specColor; }
        void   setColors(float* diffColor, float* ambiColor, float* specColor);
        float  getXSpeed() const { return xSpeed; };
        void   setXSpeed(float xSpeed) { this->xSpeed = xSpeed; }
        float  getYSpeed() const { return ySpeed; };
        void   setYSpeed(float ySpeed) { this->ySpeed = ySpeed; }
        void   setSpeed(float x, float y);
        float  getPolygones() const { return polygones; }
        void   setPolygones(float polygones) { this->polygones = polygones; }
        float  getRotateSpeed() const { return rotateSpeed; }
        void   setRotateSpeed(float rotateSpeed) { this->rotateSpeed = rotateSpeed; }
        float  getAngle() const { return angle; }
        void   setAngle(float angle) { angle = angle - int(angle) / 360 * 360; this->angle = angle; }
        float  getRotateVectorX() const { return rotateVectorX; }
        void   setRotateVectorX(float rotateVectorX) { this->rotateVectorX = rotateVectorX; }
        float  getRotateVectorY() const { return rotateVectorY; }
        void   setRotateVectorY(float rotateVectorY) { this->rotateVectorY = rotateVectorY; }
        float  getRotateVectorZ() const { return rotateVectorZ; }
        void   setRotateVectorZ(float rotateVectorZ) { this->rotateVectorZ = rotateVectorZ; }
        void   setRotateVector(float rotateVectorX, float rotateVectorY, float rotateVectorZ);
        bool   getIsDead() const { return isDead; }
        void   setIsDead() { this->isDead = true; }

        float calcAngleMultiply(bool isForX);

        bool isCollision(Object* other);

        void calcCoords();

        virtual void  draw() = 0;
    };
}

