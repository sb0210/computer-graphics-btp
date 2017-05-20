#include "physics/CylinderBodyPart.h"

CylinderBodyPart::CylinderBodyPart(dWorldID world, dSpaceID space, QVector3D pos, dQuaternion q, float radius, float length, float _mass, QVector3D color):BodyPart(world, space, pos){
	this->radius = radius;
	this->length = length;
	geom = dCreateCylinder(space, radius, length);
	dMassSetCylinderTotal(&mass, _mass, 1, radius, length);
	setParams(q);
	// geometryengine = new CylinderEngine(radius, length);
	// geometryengine->setColor(color);
	// geometryengine->init();
}

void CylinderBodyPart::draw(QOpenGLShaderProgram *program){
	if(geometryengine==NULL)return;
	const float *pos, *R;
	float radius, length;
	pos = dGeomGetPosition(geom);
	R = dGeomGetRotation(geom);
	dGeomCylinderGetParams(geom, &radius, &length);
	// float scale[3] = {radius, radius, length};
	// geometryengine->update(pos, R, scale);
	// geometryengine->draw(program);
}
