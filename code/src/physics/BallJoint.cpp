#include "physics/BallJoint.h"

BallJoint::BallJoint(dWorldID world,BodyPart* body1, BodyPart* body2):BodyJoint(body1, body2){
  type = BALL;

  joint = dJointCreateBall(world, 0);
  dJointAttach(joint, body[0]->body, body[1]->body);
  dof.resize(3);
  motor = dJointCreateAMotor(world,0);
  dJointAttach(motor, body[0]->body, body[1]->body);
  dJointSetAMotorMode(motor, dAMotorEuler);
}
void BallJoint::setAnchor(float x, float y, float z){
  dJointSetBallAnchor(joint, x, y, z);
}
void BallJoint::setAxises(QVector3D a1, QVector3D a2){
  dJointSetAMotorAxis(motor, 0, 1, a1.x(), a1.y(), a1.z());
  dJointSetAMotorAxis(motor, 2, 2, a2.x(), a2.y(), a2.z());
}
float BallJoint::getSpeed(float t){
  QVector3D speedqT(dof[0].speedqt(t),dof[1].speedqt(t),dof[2].speedqt(t));
  float speed = sqrt(speedqT[0]*speedqT[0]+speedqT[1]*speedqT[1]+speedqT[2]*speedqT[2]);
  return speed;
}
void BallJoint::applyForce(float t){
  QVector3D qT(dof[0].qt(t),dof[1].qt(t),dof[2].qt(t));
  float angle1 = dJointGetAMotorAngle (motor, 0);
  float angle2 = dJointGetAMotorAngle (motor, 1);
  float angle3 = dJointGetAMotorAngle (motor, 2);
  QVector3D currentVector(angle1, angle2, angle3);
  //QVector3D torque = 0.5*ball_force_coef*(qT-currentVector);
  // dJointAddAMotorTorques(motor,torque.x(), torque.y(), torque.z());
  QVector3D speedqT(dof[0].speedqt(t),dof[1].speedqt(t),dof[2].speedqt(t));
  dJointSetAMotorParam(motor,dParamVel,speedqT[0]);
  dJointSetAMotorParam(motor,dParamVel2,speedqT[1]);
  dJointSetAMotorParam(motor,dParamVel3,speedqT[2]);
  dJointSetAMotorParam(motor,dParamFMax,ball_force_coef);
  dJointSetAMotorParam(motor,dParamFMax2,ball_force_coef);
  dJointSetAMotorParam(motor,dParamFMax3,ball_force_coef);
}
void BallJoint::setParams(int param, float value){
  dJointSetAMotorParam(motor, param, value);
}
