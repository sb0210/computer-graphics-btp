#include "physics/CapsuleBodyPart.h"

CapsuleBodyPart::CapsuleBodyPart(dWorldID world, dSpaceID space, float radius, float length, float _mass):BodyPart(world, space){
	this->length = length;
	this->length = length;
	this->radius = radius;
	geom = dCreateCapsule(space, radius, length);
	dMassSetCapsuleTotal(&mass, _mass, 1, radius, length);
	setParams();
}

void CapsuleBodyPart::draw(QOpenGLShaderProgram *program){
	if(geometryengine==NULL)return;
	const float *pos;
	const float *R;
	float radius;
	float length;
	pos = dGeomGetPosition (geom);
	R = dGeomGetRotation (geom);
	// dGeomCapsuleGetParams(geom, &radius, &length);
	// float scale[3] = {radius, radius ,length/2+radius};
	// geometryengine->update(pos, R, scale);
	// geometryengine->draw(program);
}
