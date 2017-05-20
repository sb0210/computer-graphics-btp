#ifndef __WORLD_H_INCLUDED__
#define __WORLD_H_INCLUDED__

#include "simulation/Bird.h"
#include "geometry/GeometryEngine.h"
#include "physics/BodyPart.h"

class World{
public:

	static dWorldID world;
	static dSpaceID space;
	static Bird* bird;
	static dJointGroupID contactgroup;
	static GeometryEngine* box;
	static BodyPart* plane;
	World();
	~World();
	static void nearCallback (void *data, dGeomID o1, dGeomID o2);
	static void simLoop ();
	static void init();
	static void draw(QOpenGLShaderProgram *program);
	static void applyExternalForce(float, float, float);
	static void applyExternalTorque(float, float, float);
};

#endif
