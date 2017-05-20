#ifndef __SIMULATIONBIRD_H_INCLUDED__
#define __SIMULATIONBIRD_H_INCLUDED__

#include "physics/BodyPart.h"
#include "physics/BodyJoint.h"

struct BodyPartParameter{
	float radius;
	float length;
	dQuaternion orientation;
	QVector3D position;
	float mass;
	BodyPartParameter(float radius, float length,dQuaternion orientation,QVector3D position,float mass){
		this->radius = radius;
		this->length = length;
		for(int i=0;i<4;i++){
			this->orientation[i] = orientation[i];
		}
		this->position = position;
		this->mass = mass;
	}
};

struct JointParam{
	BodyJoint::Type type;
	BodyPart* body1;
	BodyPart* body2;
	float anchor_x, anchor_y, anchor_z;
	float axis_x, axis_y, axis_z;
	float axis_x_2, axis_y_2, axis_z_2;
};


class SimulationBird{

	public:

	BodyPart** bodyParts;
	BodyPart** feathers;
	BodyPart** tailFeathers;

	BodyJoint** bodyJoints;
	BodyJoint** featherJoints;
	BodyJoint** tailFeatherJoints;

	BodyPart* horizontalSupport;
	BodyJoint* horizontalSupportJoint;
	
	/* Body Parts and joints */
	int numBodyParts;
	int numFeathers;
	int numTailFeathers;
	int numBodyJoints;

	float featherWidth;
	float featherArea;
	float* featherLength;

	float wingspan;
	float length;

	float trunk_width;
	
	float bird_center;
	float wing_offset_x;
	float wing_offset_y;
	float wing_width;
	float wing_length[3];
	
	float segmentAreaS;
	float segmentAreaP;

	float factor;

	float weight;
	float timePeriod;
	float phaseAngle;

	string birdSpecifications;

	dWorldID world;
	dSpaceID space;


	SimulationBird(dWorldID world,dSpaceID space);


	void initTorso();
	void initShoulders();
	void initElbows();
	void initWrists();
	void initBodyParts();
	
	void initBodyJoints();
	void initFeathers();
	void initTail();
	void init();

	void applyBodyForces(float t);
	void applyFeatherForces(float t);
	void applyTailForces(float t);
	void applyForces(float t);

	float getLift();
	void applyExternalForce(float, float, float);
	void applyExternalTorque(float, float, float);

	void resize();

	BodyPart* getBodyPart(float radius, float length, dQuaternion orientation, QVector3D position, float mass);
};

#endif
