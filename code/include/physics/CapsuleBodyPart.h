#ifndef CAPSULEBODYPART_H
#define CAPSULEBODYPART_H

#include "physics/BodyPart.h"

class CapsuleBodyPart: public BodyPart{
public:
	float radius;
	float length;
	CapsuleBodyPart(dWorldID world, dSpaceID space, float radius, float length, float mass);
	void draw(QOpenGLShaderProgram *program);
};

#endif