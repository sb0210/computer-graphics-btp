#include "physics/BoxBodyPart.h"

BoxBodyPart::BoxBodyPart(dWorldID world, dSpaceID space, QVector3D position, QVector3D sides, float _mass):BodyPart(world, space, position){
	this->lx = lx;
	this->ly = ly;
	this->lz = lz;
	geom = dCreateBox(space, lx, ly, lz);
	dMassSetBoxTotal(&mass, _mass, lx, ly, lz);
	setParams();

	// geometryengine = new CuboidEngine(lx,ly,lz);
	// geometryengine->setColor(color);
	// if(textureArr==NULL)
	// 	geometryengine->init();
	// else
	// 	geometryengine->init(textureArr);
}

void BoxBodyPart::draw(QOpenGLShaderProgram *program){
	if(geometryengine==NULL)return;
	const float *pos, *R;
	float sides[3];
	pos = dGeomGetPosition(geom);
	R = dGeomGetRotation(geom);
	dGeomBoxGetLengths(geom, sides);
	
	// geometryengine->update(pos, R);
	// geometryengine->draw(program);
}
