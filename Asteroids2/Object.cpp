#include "Object.h"

namespace Asteroids
{

    Object::Object(float xCenter, float yCenter, float zCenter,
        float xSize, float ySize, float zSize,
        float* diffColor, float* ambiColor, float* specColor,
        float xSpeed, float ySpeed, float polygones,
        float rotateSpeed, float angle, float rotateVectorX, float rotateVectorY, float rotateVectorZ)
        : polygones(polygones), rotateSpeed(rotateSpeed), angle(angle)
    {
        setCoords(xCenter, yCenter, zCenter);
        setSize(xSize, ySize, zSize);
        setColors(diffColor, ambiColor, specColor);
        setSpeed(xSpeed, ySpeed);
        setRotateVector(rotateVectorX, rotateVectorY, rotateVectorZ);
    }

    void Object::calcCoords()
    {
        this->setCoords(xCenter + getXSpeed(), yCenter, zCenter + getYSpeed());

        setAngle(angle + rotateSpeed);
    }

    bool Object::isCollision(Object* other)
    {
        if (sqrt(pow(abs(xCenter - other->xCenter), 2) +
            pow(abs(yCenter - other->yCenter), 2) +
            pow(abs(zCenter - other->zCenter), 2)) <
            (min(min(xSize, ySize), zSize) / 2 + min(min(other->xSize, other->ySize), other->zSize) / 2))
            return true;
        return false;
    }

    float Object::calcAngleMultiply(bool isForX)
    {
        int tempAngle = angle;

        if (tempAngle < 0) tempAngle = 360 + tempAngle;
        float answer = 1 - (((tempAngle + 90 * int(isForX)) % 180) * 0.0111111);

        if (!isForX)
        {
            if (tempAngle >= 180 && tempAngle < 360)
                return -answer;
            else
                return answer;
        }
        else
        {
            if (tempAngle >= 0 && tempAngle < 90 || tempAngle >= 270 && tempAngle < 360)
                return -answer;
            else
                return answer;
        }
        return 0;
    }

    void Object::setCoords(float xCenter, float yCenter, float zCenter)
    {
        this->xCenter = xCenter;
        this->yCenter = yCenter;
        this->zCenter = zCenter;
    }

    void Object::setSize(float xSize, float ySize, float zSize)
    {
        this->xSize = xSize;
        this->ySize = ySize;
        this->zSize = zSize;
    }

    void Object::setColors(float* diffColor, float* ambiColor, float* specColor)
    {
        this->diffColor = diffColor;
        this->ambiColor = ambiColor;
        this->specColor = specColor;
    }

    void Object::setSpeed(float x, float y)
    {
        this->xSpeed = x;
        this->ySpeed = y;
    }

    void Object::setRotateVector(float rotateVectorX, float rotateVectorY, float rotateVectorZ)
    {
        this->rotateVectorX = rotateVectorX;
        this->rotateVectorY = rotateVectorY;
        this->rotateVectorZ = rotateVectorZ;
    }
}