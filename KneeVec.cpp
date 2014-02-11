/* Created for ELEC 490
 * Megan Gardner
 * Kevin Cook
 * Cameron Kramer
 */

#include "KneeVec.h"

KneeVec::KneeVec(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

float KneeVec::getX()
{
    return x;
}

float KneeVec::getY()
{
    return y;
}

float KneeVec::getZ()
{
    return z;
}

void KneeVec::setX(float newX)
{
    x = newX;
}

void KneeVec::setY(float newY)
{
    y = newY;
}

void KneeVec::setZ(float newZ)
{
    z = newZ;
}

float KneeVec::KneeAngle(KneeVec other)
{
    //perform knee angle algorithm - other should be sensor 2
    float offset = 0.0;

    if(other.x < 0.0 && other.z > 0.0)
    {
        offset = 180 + 2*abs(atan(other.x/other.z));
    }
    else if(other.x < 0.0 && other.z < 0.0)
    {
        offset = 180 - (180 - 2*atan(other.x/other.y));
    }

    float output = offset - abs(atan(x/z)) - abs(atan(other.x/other.z));

    if(x < 0.0 && z > 0.0 && other.x < 0.0 && other.z > 0.0)
    {
        return output;
    }
    else if(x < 0.0 && z < 0.0 && other.x < 0.0 && other.z > 0.0)
    {
        return 180-output;
    }
    else if(x < 0.0 && z > 0.0 && other.x < 0.0 && other.z > 0.0)
    {
        return output;
    }
    else if(x < 0.0 && z > 0.0 && other.x > 0.0 && other.z < 0.0)
    {
        return 180-output;
    }
    else
        return 180-output;
}

