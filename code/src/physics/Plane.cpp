#include "physics/Plane.h"

Plane::Plane(dWorldID world, dSpaceID space, float a, float b, float c, float d, QVector3D color):BodyPart(world, space, QVector3D(0,0,0)){
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	geom = dCreatePlane(space, a,b,c,d);
	// geometryengine = new PlaneEngine(a,b,c,d);
	// geometryengine->setColor(color);
	// geometryengine->init();
}

void Plane::draw(QOpenGLShaderProgram* program){
	if(geometryengine==NULL)return;
	geometryengine->draw(program);
}
