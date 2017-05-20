#ifndef HINGEJOINT_H
#define HINGEJOINT_H

#include "physics/BodyJoint.h"

class HingeJoint: public BodyJoint{
  public:
    HingeJoint(dWorldID world,BodyPart* body1, BodyPart* body2);
    void setAnchor(float x, float y, float z);
    void setAxis(float x, float y, float z);
    void setParams(int param, float value);
    void applyForce(float t);
    float getSpeed(float t);
};

#endif