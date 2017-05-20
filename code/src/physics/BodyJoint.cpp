#include "physics/BodyJoint.h"
#include "physics/BallJoint.h"
#include "physics/HingeJoint.h"


BodyJoint::BodyJoint(BodyPart* body1, BodyPart* body2){
  body[0] = body1;
  body[1] = body2;
  T = 2;
}

void BodyJoint::setTimePeriod(float T){
  this->T = T;
  for(unsigned int i=0;i<dof.size();i++){
    dof[i].setTimePeriod(T);
  }
}

BodyJoint* BodyJoint::getJoint(Type type, dWorldID world,BodyPart* body1, BodyPart* body2){
  if(type == HINGE){
    return new HingeJoint(world, body1, body2);
  }
  else if(type == BALL){
    return new BallJoint(world, body1, body2);
  }

  return NULL;
}

void BodyJoint::setAnchor(float , float , float ){}
void BodyJoint::setAxis(float , float , float ){}
void BodyJoint::setAxises(QVector3D , QVector3D ){}
void BodyJoint::setParams(int , float ){}
float BodyJoint::getSpeed(float ){return 0;}

void BodyJoint::setForceCoef(float ball_force_coef, float hinge_force_coef){
  this->ball_force_coef = ball_force_coef*8/T;
  this->hinge_force_coef = hinge_force_coef*4/T;
}

