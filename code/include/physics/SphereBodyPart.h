#ifndef SPHERE_BODY_PART_H
#define SPHERE_BODY_PART_H

#include "physics/BodyPart.h"

class SphereBodyPart: public BodyPart{
public:
	float radius;
	SphereBodyPart(dWorldID world, dSpaceID space, QVector3D pos, float radius, float mass, QVector3D color);
	void draw(QOpenGLShaderProgram *program);
};

#endif