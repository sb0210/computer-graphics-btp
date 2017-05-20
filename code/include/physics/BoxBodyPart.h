#ifndef BOXBODYPART_H
#define BOXBODYPART_H

#include "physics/BodyPart.h"

class BoxBodyPart: public BodyPart{
public:
	float lx;
	float ly;
	float lz;
	BoxBodyPart(dWorldID world, dSpaceID space, QVector3D sides, float mass);
	void draw(QOpenGLShaderProgram *program);
};

#endif