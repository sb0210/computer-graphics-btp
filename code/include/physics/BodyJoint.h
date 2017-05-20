#ifndef BODYJOINT_H
#define BODYJOINT_H

#include "helpers/Includes.h"
#include "physics/BodyPart.h"
#include "physics/DOF.h"

class BodyJoint{
  public:
    dJointID joint;
    dJointID joint1, joint2, joint3;
    dJointID motor;
    BodyPart* body[2];
    enum Type{
      HINGE,
      THREEHINGEJOINT,
      BALL
    };
    Type type;
    vector<DOF> dof;
    float ball_force_coef, hinge_force_coef;
    QVector3D q_star;
    float T;
    BodyJoint(BodyPart* body1, BodyPart* body2);
    static BodyJoint* getJoint(Type type, dWorldID world,BodyPart* body1, BodyPart* body2);
    virtual void setAnchor(float x, float y, float z);
    virtual void setAxis(float x, float y, float z);
    virtual void setAxises(QVector3D a1, QVector3D a2);
    virtual void applyForce(float t)=0;
    virtual void setParams(int param, float value);
    virtual float getSpeed(float t);
    void setForceCoef(float ball_force_coef, float hinge_force_coef);
    void setTimePeriod(float T);

};
#endif
