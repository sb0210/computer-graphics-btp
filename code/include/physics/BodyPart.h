#ifndef BODY_PART_H
#define BODY_PART_H

#include "helpers/Includes.h"
#include "geometry/GeometryEngine.h"

class BodyPart{
public:
	dBodyID body;
	dGeomID geom;
	dMass mass;
	QVector3D pos;
	GeometryEngine* geometryengine;
	GeometryEngine* originalGeometryEngine;
	enum Geometry{
		ELLIPSE,
		HEMISPHERE,
		OBJ
	};
	BodyPart(dWorldID world, dSpaceID space);
	void init();
	void setQuaternian(dQuaternion q);
	void setPosition(QVector3D p);
	void setEngine(GeometryEngine* engine);

	void setParams();
	void setParams(dQuaternion q);
	void setPosition(float x, float y, float z);
	void setScale(float lx, float ly, float lz);
	void setOriginalEngine(GeometryEngine* engine);
	void setCalliberation(float pos[], float R[], float scaling[]);
	void setCalliberation(float pos[], float scaling[]);
	void setCalliberation(QMatrix4x4 mat);

	GeometryEngine* getEngine();
	void freeEngine();

	void applyExternalForce(float fx, float fy, float fz);
	void applyExternalForce(float fx, float fy, float fz, float px, float py, float pz);
	void applyExternalTorque(float tx, float ty, float tz);

	const float* getOrientation();

	virtual void draw(QOpenGLShaderProgram *program)=0;
};

#endif
