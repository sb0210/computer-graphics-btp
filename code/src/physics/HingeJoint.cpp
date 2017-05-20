#include "physics/HingeJoint.h"

HingeJoint::HingeJoint(dWorldID world, BodyPart* body1, BodyPart* body2):BodyJoint(body1, body2){
  type = HINGE;
  joint = dJointCreateHinge(world, 0);
  dJointAttach(joint, body[0]->body, body[1]->body);
  dof.resize(1);
}
void HingeJoint::setAnchor(float x, float y, float z){
  dJointSetHingeAnchor(joint, x, y, z);
}

void HingeJoint::setAxis(float x, float y, float z){
  dJointSetHingeAxis(joint, x, y, z);
}

float HingeJoint::getSpeed(float t){
  float qT(dof[0].speedqt(t));
  return qT;
}

void HingeJoint::applyForce(float t){
  float qT(dof[0].speedqt(t));
  // float angle = dJointGetHingeAngle(joint);
  // float torque = hinge_force_coef*(qT-angle);
  // dJointAddHingeTorque(joint,torque);
  dJointSetHingeParam(joint,dParamVel,qT);
  dJointSetHingeParam(joint,dParamFMax,hinge_force_coef);
}

void HingeJoint::setParams(int param, float value){
  dJointSetHingeParam(joint, param, value);
}


