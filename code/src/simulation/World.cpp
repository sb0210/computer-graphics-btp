#include "simulation/World.h"
#include "physics/Plane.h"

World::World(){

}

void World::nearCallback (void *, dGeomID o1, dGeomID o2){
    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    dContact contact;
    contact.surface.mode = dContactBounce | dContactSoftCFM;
    contact.surface.mu = dInfinity;
    contact.surface.bounce = 0.9;
    contact.surface.bounce_vel = 0.1;
    contact.surface.soft_cfm = 0.001;
    int numc = dCollide (o1,o2,1,&contact.geom,sizeof(dContact));
    if (numc) {
        dJointID c = dJointCreateContact (world,contactgroup,&contact);
        dJointAttach (c,b1,b2);
    }
}


void World::simLoop (){
      dSpaceCollide (space,0,&nearCallback);
      // dWorldQuickStep (world,0.01);
      dJointGroupEmpty (contactgroup);
}

void World::init(){

	dInitODE ();

	world = dWorldCreate ();
	space = dHashSpaceCreate (0);
	dWorldSetGravity (world,0,0,0);
	dWorldSetCFM (world,1e-5);
	// dCreatePlane (space,0,1,0,-4);
	contactgroup = dJointGroupCreate (0);

	// bird = new MyBird(world, space);
  bird = new Bird(world,space);
  // box = new CuboidEngine(19,19,19);
  // box->setColor(QVector3D(1,1,1));
  // box->setTexture("textures/skymap.jpg");
  // box->init();
  plane = new Plane(world,space, 0,1,0,-10, QVector3D(0.80,0.80,0.80));
  plane->getEngine()->setTexture("textures/checkerboard.png");

}

World::~World(){
    dJointGroupDestroy (contactgroup);
    dSpaceDestroy (space);
    dWorldDestroy (world);
    dCloseODE();
}
void World::draw(QOpenGLShaderProgram *program){
  // box->draw(program);
  plane->draw(program);
  bird->draw(program);
}

void World::applyExternalForce(float fx, float fy, float fz){
  bird->applyExternalForce(fx, fy, fz);
}

void World::applyExternalTorque(float tx, float ty, float tz){
  bird->applyExternalTorque(tx, ty, tz);
}