/* Created for ELEC 490
 * Megan Gardner
 * Kevin Cook
 * Cameron Kramer
 */

#ifndef KNEEVEC_H
#define KNEEVEC_H

#include <cmath>
#include <iostream>

using namespace std;

class KneeVec {
    public:
       KneeVec(); //constructor
       float getX();
       float getY();
       float getZ();
       void setX(float newX);
       void setY(float newY);
       void setZ(float newZ);

       float KneeAngle(KneeVec other);

    private:
        float x;
        float y;
        float z;
};

#endif // KNEEVEC_H
