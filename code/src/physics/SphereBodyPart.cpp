#include "physics/SphereBodyPart.h"

SphereBodyPart::SphereBodyPart(dWorldID world, dSpaceID space, QVector3D pos, float radius, float _mass, QVector3D color):BodyPart(world, space, pos){
	this->radius = radius;
	geom = dCreateSphere(space, radius);
	dMassSetSphereTotal(&mass, _mass, radius);
	setParams();
	// geometryengine = new SphereEngine(radius);
	// geometryengine->setColor(color);
	// geometryengine->init();
}

void SphereBodyPart::draw(QOpenGLShaderProgram *program){
	if(geometryengine==NULL)return;
	const float *pos;
	const float *R;
	pos = dGeomGetPosition (geom);
	R = dGeomGetRotation (geom);
	// float radius = dGeomSphereGetRadius(geom);
	// float scale[3] = {radius, radius, radius};
	// geometryengine->update(pos, R,scale);
	// geometryengine->draw(program);
}
