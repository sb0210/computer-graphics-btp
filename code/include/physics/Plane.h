#ifndef PLANE_BODY_PART_H
#define PLANE_BODY_PART_H

#include "physics/BodyPart.h"

class Plane: public BodyPart{
public:
	float a,b,c,d;
	Plane(dWorldID world, dSpaceID space, float a, float b, float c, float d, QVector3D color);
	void draw(QOpenGLShaderProgram *program);
};

#endif