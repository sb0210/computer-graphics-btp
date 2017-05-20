#include "physics/BodyPart.h"
#include "geometry/GeometryEngine.h"
#include "helpers/Basics.h"

BodyPart::BodyPart(dWorldID world, dSpaceID , QVector3D pos){
	this->body = dBodyCreate(world);
	this->pos = pos;
}

BodyPart::BodyPart(dWorldID world, dSpaceID ){
	this->body = dBodyCreate(world);
}

void BodyPart::setPosition(QVector3D pos){
	dBodySetPosition(body, pos.x, pos.y, pos.z);
}

void BodyPart::setQuaternian(dQuaternion q){
	dBodySetQuaternion(body,q);
}

void BodyPart::setParams(){
	dBodySetMass(body, &mass);
	dGeomSetBody(geom, body);
}

void BodyPart::init(){
	dBodySetMass(body, &mass);
	dGeomSetBody(geom, body);
}

void BodyPart::setPosition(float x, float y, float z){
	QVector3D pos(x,y,z);
	setPosition(pos);
}

void BodyPart::setCalliberation(float pos[], float scaling[]){
	float R[12] = {1,0,0,0,
								0,1,0,0,
								0,0,1,0};
	setCalliberation(pos,R,scaling);
}

void BodyPart::setParams(dQuaternion q){
	dBodySetMass(body, &mass);
	dGeomSetBody(geom, body);
	dBodySetQuaternion (this->body,q);
	dBodySetPosition (body,pos.x, pos.y,pos.z);
}

void BodyPart::applyExternalForce(float fx, float fy, float fz){
	dBodyAddForce(body, fx, fy, fz);
}

void BodyPart::applyExternalForce(float fx, float fy, float fz, float px, float py, float pz){
	dBodyAddForceAtRelPos(body, fx, fy, fz, px, py, pz);
}

void BodyPart::applyExternalTorque(float tx, float ty, float tz){
	dBodyAddTorque(body, tx, ty, tz);
}

const float* BodyPart::getOrientation(){
	return dBodyGetQuaternion(body);
}

GeometryEngine* BodyPart::getEngine(){
	return geometryengine;
}

void BodyPart::freeEngine(){
	free(geometryengine);
	geometryengine=NULL;
}

void BodyPart::setEngine(GeometryEngine* engine){
	geometryengine = engine;
}
