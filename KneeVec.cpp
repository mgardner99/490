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
    cout << y << endl;
    cout << z << endl;
    cout << other.y << endl;
    cout << other.z << endl;

    if(other.y < 0.0 && other.z > 0.0)
    {
        offset = 180 + 2*abs(atan(other.y/other.z)*180/M_PI);
    }
    else if(other.y < 0.0 && other.z < 0.0)
    {
        offset = 180 - (180 - 2*atan(other.y/other.z)*180/M_PI);
    }
    cout << offset << endl;
    float output = offset - abs(atan(y/z)*180/M_PI) - abs(atan(other.y/other.z)*180/M_PI);
    cout << output << endl;
    if(y < 0.0 && z > 0.0 && other.y < 0.0 && other.z > 0.0)
    {
        return output;
    }
    else if(y < 0.0 && z < 0.0 && other.y < 0.0 && other.z > 0.0)
    {
        //return 180-output;
        return offset-output;
    }
    else if(y < 0.0 && z > 0.0 && other.y < 0.0 && other.z > 0.0)
    {
        return output;
    }
    else if(y < 0.0 && z > 0.0 && other.y > 0.0 && other.z < 0.0)
    {
        return 180-output;
    }
    else
        return 180-output;
}

