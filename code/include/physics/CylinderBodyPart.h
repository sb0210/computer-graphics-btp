#ifndef CYLINDER_BODY_PART_H
#define CYLINDER_BODY_PART_H

#include "physics/BodyPart.h"

class CylinderBodyPart: public BodyPart{
public:
	float radius;
	float length;
	CylinderBodyPart(dWorldID world, dSpaceID space, QVector3D pos, dQuaternion q, float radius, float length, float mass, QVector3D color);
	void draw(QOpenGLShaderProgram *program);
};

#endif