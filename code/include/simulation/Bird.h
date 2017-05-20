#ifndef __BIRD_H_INCLUDED__
#define __BIRD_H_INCLUDED__

#include "physics/BodyPart.h"
#include "physics/BodyJoint.h"


struct JointParam{
	BodyJoint::Type type;
	BodyPart* body1;
	BodyPart* body2;
	float anchor_x, anchor_y, anchor_z;
	float axis_x, axis_y, axis_z;
	float axis_x_2, axis_y_2, axis_z_2;
};

class PartParameter{

	public:
	BodyPart::Geometry geometry;
	float radius,length;
	dQuaternion quart;
	QVector4D angles;
	Position newpos;
	Position calliberatePos;
	float mass;
	string path;
	QVector3D color;
	PartParameter(){}
	PartParameter(BodyPart::Geometry geometry, float radius, float length, dQuaternion quart, QVector4D angles, Position pos, Position calliberatePos, float mass, string path="", QVector3D color=GRAY){
		this->geometry = geometry;
		this->radius = radius;
		this->length = length;
		this->quart[0] = quart[0];
		this->quart[1] = quart[1];
		this->quart[2] = quart[2];
		this->quart[3] = quart[3];
		this->angles = angles;
		this->newpos = pos;
		this->calliberatePos = calliberatePos;
		this->mass = mass;
		this->path = path;
		this->color = color;
	}
};

class Bird{

	public:

	BodyPart** bodyParts;
	BodyPart** feathers;
	BodyPart** tailFeathers;

	BodyJoint** bodyJoints;
	BodyJoint** featherJoints;
	BodyJoint** tailFeatherJoints;

	BodyPart* horizontalSupport;
	BodyJoint* horizontalSupportJoint;
	
	/* simulation time */
	float t;

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

	QOpenGLShaderProgram *program;

	Bird(dWorldID world,dSpaceID space);


	void initTorso();
	void initShoulders();
	void initElbows();
	void initWrists();
	void initBodyParts();
	
	void initBodyJoints();
	void initFeathers();
	void initTail();
	void init();

	void drawBody();
	void drawFeathers();
	void drawTail();
	void draw();

	void applyBodyForces(float t);
	void applyFeatherForces(float t);
	void applyTailForces(float t);
	void applyForces(float t);

	float getLift();
	void applyExternalForce(float, float, float);
	void applyExternalTorque(float, float, float);

	void resize();
	void readSpecifications(float ** arr, int numElements);

	const float* getOrientation();
};

#endif
