#ifndef BALLJOINT_H
#define BALLJOINT_H

#include "physics/BodyJoint.h"

class BallJoint: public BodyJoint{
  public:
    BallJoint(dWorldID world,BodyPart* body1, BodyPart* body2);
    void setAnchor(float x, float y, float z);
    void setAxises(QVector3D a1, QVector3D a2);
    void setParams(int param, float value);
    void applyForce(float t);
    float getSpeed(float t);
};

#endif