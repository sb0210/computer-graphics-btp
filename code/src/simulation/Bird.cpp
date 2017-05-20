#include "simulation/Bird.h"
#include "helpers/Colors.h"
#include "helpers/Basics.h"

#include "physics/CapsuleBodyPart.h"
#include "physics/BoxBodyPart.h"

#include "geometry/HemisphereEngine.h"
#include "geometry/OBJEngine.h"
#include "geometry/AerofoilEngine.h"

float thickness = 0.5;
bool inbetween_joints = false;


void Bird::

void Bird::initTorso(float radius, float length, Position position, float mass, dQuaternion orientation, QVector3D color, string texture){

	bodyParts[0] = new CapsuleBodyPart(world, space, radius, length, mass);
	bodyParts[0]->setQuaternian(orientation);
	bodyParts[0]->setPosition(position);
	bodyParts[0]-init();

	GeometryEngine* engine = new EllipsoidEngine(radius, radius, length/2 + radius);
	engine->setColor(color);
	engine->setTexture(texture);
	engine->init();

	bodyParts[0]->setEngine(engine);
}



void Bird::initShoulders();
void Bird::initElbows();
void Bird::initWrists();

void Bird::initBodyParts(){

	Position pos(0,0,0);
	dQuaternion alongY, alongX ;
	float delta = 0.00;
	dQFromAxisAndAngle(alongY, 1,0,0, M_PI/2);
	dQFromAxisAndAngle(alongX, 0,1,0, M_PI/2);


	float radius = trunk_width/2;

	PartParameter partParams[9]={
		PartParameter(BodyPart::OBJ,radius, length-trunk_width, alongY, QVector4D(0,0,0,0), Position(0,bird_center,0), Position(0,0,0), 1000.0),
		PartParameter(BodyPart::ELLIPSE,wing_width/2,wing_length[0]-wing_width,alongX,QVector4D(0,0,0,0),Position(-wing_offset_x-wing_length[0]/2-delta,wing_offset_y,0), Position(0,0,0),15.0 ),
		PartParameter(BodyPart::ELLIPSE,wing_width/2,wing_length[0]-wing_width,alongX,QVector4D(0,0,0,0),Position(+wing_offset_x+wing_length[0]/2+delta,wing_offset_y,0), Position(0,0,0),15.0 ),
		PartParameter(BodyPart::HEMISPHERE,wing_width/2,wing_length[1]/2-wing_width,alongX,QVector4D(0,180,0,180),Position(-wing_offset_x-wing_length[0]-wing_length[1]/4-delta,wing_offset_y,0), Position(0,0,-3*wing_length[1]/4),5.0 ),
		PartParameter(BodyPart::HEMISPHERE,wing_width/2,wing_length[1]/2-wing_width,alongX,QVector4D(180,360,0,180),Position(+wing_offset_x+wing_length[0]+wing_length[1]/4+delta,wing_offset_y,0), Position(0,0,+3*wing_length[1]/4),5.0 ),
		PartParameter(BodyPart::HEMISPHERE,wing_width/2,wing_length[1]/2-wing_width,alongX,QVector4D(180,360,0,180),Position(-wing_offset_x-wing_length[0]-3*wing_length[1]/4-delta,wing_offset_y,0), Position(0,0,3*wing_length[1]/4),5.0 ),
		PartParameter(BodyPart::HEMISPHERE,wing_width/2,wing_length[1]/2-wing_width,alongX,QVector4D(0,180,0,180),Position(+wing_offset_x+wing_length[0]+3*wing_length[1]/4+delta,wing_offset_y,0), Position(0,0,-3*wing_length[1]/4),5.0 ),
		PartParameter(BodyPart::ELLIPSE,wing_width/2,wing_length[2]-wing_width,alongX,QVector4D(0,0,0,0),Position(-wing_offset_x-wing_length[0]-wing_length[1]-wing_length[2]/2-delta,wing_offset_y,0), Position(0,0,0),6 ),
		PartParameter(BodyPart::ELLIPSE,wing_width/2,wing_length[2]-wing_width,alongX,QVector4D(0,0,0,0),Position(+wing_offset_x+wing_length[0]+wing_length[1]+wing_length[2]/2+delta,wing_offset_y,0), Position(0,0,0),6.0),
	};

	for(int i=0;i<9;i++){
		bodyParts[i] = new CapsuleBodyPart(world, space, pos, partParams[i].radius, partParams[i].length,partParams[i].mass,partParams[i].color);

		if(i==0){
				bodyParts[i]->getEngine()->setTexture("textures/parrot.png");
		}
		else if(i==9){
			bodyParts[i]->getEngine()->setTexture("textures/brown.jpg");
		}
		else bodyParts[i]->getEngine()->setTexture("textures/feather.jpg");

		bodyParts[i]->setPosition(partParams[i].newpos);
		bodyParts[i]->setQuaternian(partParams[i].quart);
		if(partParams[i].geometry == BodyPart::HEMISPHERE){
			GeometryEngine* engine = new HemiSphereEngine(1,partParams[i].angles[0],partParams[i].angles[1],partParams[i].angles[2],partParams[i].angles[3]);
			engine->setColor(partParams[i].color);
			engine->setTexture("textures/feather.jpg");
			engine->init(partParams[i].angles[0],partParams[i].angles[1],partParams[i].angles[2],partParams[i].angles[3]);
			bodyParts[i]->setEngine(engine);
			float cal_pos[3] = {partParams[i].calliberatePos.x,partParams[i].calliberatePos.y,partParams[i].calliberatePos.z};
			float cal_scale[3] = {1,1,2};
			bodyParts[i]->setCalliberation(cal_pos, cal_scale);
		}
		if(partParams[i].geometry == BodyPart::OBJ){
			bodyParts[i]->setEngine(new OBJEngine("assets/torso.txt",1,1,1));
			float cal_pos[3] = {partParams[i].calliberatePos.x,partParams[i].calliberatePos.y,partParams[i].calliberatePos.z};
			float cal_scale[3] = {1.0/factor,1.0/factor,1.0/factor};
			bodyParts[i]->setCalliberation(cal_pos, cal_scale);
			bodyParts[i]->getEngine()->setTexture("textures/parrot.png");
		}
	}
	PartParameter horizontalSupportParam(BodyPart::ELLIPSE,0.1,0.1,alongX,QVector4D(0,0,0,0),Position(0,0,-10), Position(0,0,0),10000000.0);
	horizontalSupport = new CapsuleBodyPart(world, space, pos, horizontalSupportParam.radius, horizontalSupportParam.length, horizontalSupportParam.mass, horizontalSupportParam.color);
	horizontalSupport->setPosition(horizontalSupportParam.newpos);

}

void Bird::initBodyJoints(dWorldID world){

	float radius = trunk_width/2;

	JointParam jointParams[8] = {
		{BodyJoint::BALL,  bodyParts[0], bodyParts[1], -wing_offset_x, wing_offset_y,0, 1, 0, 0, 0,0,1},
		{BodyJoint::BALL,  bodyParts[0], bodyParts[2], +wing_offset_x, wing_offset_y,0, 1, 0, 0, 0,0,-1},
		{BodyJoint::HINGE, bodyParts[1], bodyParts[3], -wing_offset_x-wing_length[0], wing_offset_y, 0, 0, 0, 1, 0,0,1},
		{BodyJoint::HINGE, bodyParts[2], bodyParts[4], +wing_offset_x+wing_length[0], wing_offset_y, 0, 0, 0, 1, 0,0,1},
		{BodyJoint::HINGE, bodyParts[3], bodyParts[5], -wing_offset_x-wing_length[0]-wing_length[1]/2, wing_offset_y,0, 1, 0, 0, 0,0,1},
		{BodyJoint::HINGE, bodyParts[4], bodyParts[6], +wing_offset_x+wing_length[0]+wing_length[1]/2, wing_offset_y,0, -1, 0, 0, 0,0,1},
		{BodyJoint::HINGE, bodyParts[5], bodyParts[7], -wing_offset_x-wing_length[0]-wing_length[1],wing_offset_y,0, 0, 0, 1, 0,0,1},
		{BodyJoint::HINGE, bodyParts[6], bodyParts[8], +wing_offset_x+wing_length[0]+wing_length[1],wing_offset_y,0, 0, 0, 1, 0,0,1},
	};
	for (int i=0;i<8;i++){
		bodyJoints[i] = BodyJoint::getJoint(jointParams[i].type, world, jointParams[i].body1, jointParams[i].body2);
		bodyJoints[i]->setAnchor(jointParams[i].anchor_x,jointParams[i].anchor_y,jointParams[i].anchor_z);
		if(jointParams[i].type == BodyJoint::HINGE){
			bodyJoints[i]->setAxis(jointParams[i].axis_x,jointParams[i].axis_y,jointParams[i].axis_z);
		}else{
			bodyJoints[i]->setAxises(QVector3D(jointParams[i].axis_x,jointParams[i].axis_y,jointParams[i].axis_z),QVector3D(jointParams[i].axis_x_2,jointParams[i].axis_y_2,jointParams[i].axis_z_2));
		}
		bodyJoints[i]->setForceCoef(20,10);
	}
	float shoulder_angle = M_PI/7;
	float elbow_angle = M_PI/7;
	float twist_angle = M_PI/5;
	float wrist_angle = M_PI/5;
	float body_angles[] = {shoulder_angle,elbow_angle,twist_angle,wrist_angle};
	for(int i=0;i<8;i++){
		bodyJoints[i]->setParams(dParamLoStop,-body_angles[i/2]);
		bodyJoints[i]->setParams(dParamHiStop,body_angles[i/2]);
	}
	DOF dof[] = {
		DOF(-shoulder_angle, shoulder_angle, 0, 1, DOF::TWO),//ONE),
		DOF(-shoulder_angle, shoulder_angle, 0, 1, DOF::ONE),//ONE),
		DOF(-shoulder_angle, shoulder_angle, 0, 1, DOF::TWO),//ONE),
		DOF(-shoulder_angle, shoulder_angle, 0, 1, DOF::TWO),//ONE),
		DOF(-shoulder_angle, shoulder_angle, 0, 1, DOF::ONE),//ONE),
		DOF(-shoulder_angle, shoulder_angle, 0, 1, DOF::TWO),//ONE),
		DOF(-elbow_angle, elbow_angle, 0, 1, DOF::TWO),
		DOF(elbow_angle, -elbow_angle, 0, 1, DOF::TWO),
		DOF(-twist_angle, twist_angle, 0, 1, DOF::TWO),
		DOF(twist_angle, -twist_angle, 0, 1, DOF::TWO),
		DOF(-wrist_angle, wrist_angle, 0, 1, DOF::TWO),
		DOF(wrist_angle, -wrist_angle, 0, 1, DOF::TWO),
	};

	int mapping[]={
		0,0,0,300,10,
		0,1,1,300,10,
		0,2,2,300,10,
		1,0,3,300,10,
		1,1,4,300,10,
		1,2,5,300,10,
		2,0,6,20,10,
		3,0,7,20,10,
		4,0,8,20,10,
		5,0,9,20,10,
		6,0,10,20,10,
		7,0,11,20,10
	};
	for(int i=0;i<60;i=i+5){
		bodyJoints[mapping[i]]->dof[mapping[i+1]] = dof[mapping[i+2]];
		bodyJoints[mapping[i]]->setForceCoef(mapping[i+3],mapping[i+4]);
	}
	for(int i=0;i<numBodyJoints;i++){
		bodyJoints[i]->setTimePeriod(timePeriod);
	}
	JointParam horizontalSupportJointParam = {BodyJoint::HINGE, horizontalSupport, bodyParts[0], 0,length/2,0, -1, 0, 0, 0,0,1};
	horizontalSupportJoint = BodyJoint::getJoint(horizontalSupportJointParam.type, world, horizontalSupportJointParam.body1, horizontalSupportJointParam.body2);
	horizontalSupportJoint->setAnchor(horizontalSupportJointParam.anchor_x,horizontalSupportJointParam.anchor_y,horizontalSupportJointParam.anchor_z);
	horizontalSupportJoint->setAxis(horizontalSupportJointParam.axis_x,horizontalSupportJointParam.axis_y,horizontalSupportJointParam.axis_z);
	horizontalSupportJoint->setForceCoef(2000,1000);
	horizontalSupportJoint->setParams(dParamLoStop,-M_PI/3);
	horizontalSupportJoint->setParams(dParamHiStop,-M_PI/4);

}

void getFeatherLength(float feather_length_txt[], float factor, int numFeathers){
	ifstream file;
	file.open("assets/rightwing.out");
	int num;
	file>>num;
	for(int i=0;i<numFeathers;i++){
		int x;
		float length;
		file>>x>>length;
		feather_length_txt[x] = length/factor;
	}
}

void getFeatherTexture(float ** feather_texture[], int numFeathers){
	ifstream file;
	file.open("assets/rightwingTex.out");
	int num;
	file>>num;
	int x;
	float x1,y1,x2,y2;
	file>>x>>x1>>y1>>x2>>y2;
	for(int i=0;i<numFeathers-1;i++){
		int next_x;
		float next_x1,next_y1,next_x2,next_y2;
		file>>next_x>>next_x1>>next_y1>>next_x2>>next_y2;
		feather_texture[i][0][0] = (x1+next_x1)/2;
		feather_texture[i][0][1] = (y1+next_y1)/2;
		feather_texture[i][1][0] = (next_x1+next_x2)/2;
		feather_texture[i][1][1] = (next_y1+next_y2)/2;
		feather_texture[i][2][0] = (x1+x2)/2;
		feather_texture[i][2][1] = (y1+y2)/2;
		feather_texture[i][3][0] = (next_x2+x2)/2;
		feather_texture[i][3][1] = (next_y2+y2)/2;
		x1=next_x1;
		y1=next_y1;
		x2=next_x2;
		y2=next_y2;
	}	
	feather_texture[numFeathers-1] = feather_texture[numFeathers-2];
	for(int i=0;i<numFeathers-50;i++){
		feather_texture[i][1][0] = feather_texture[i+50][1][0];
		feather_texture[i][1][1] = feather_texture[i+50][1][1];
		feather_texture[i][3][0] = feather_texture[i+50][3][0];
		feather_texture[i][3][1] = feather_texture[i+50][3][1];
	}
	for(int i=numFeathers-50;i<numFeathers;i++){
		feather_texture[i][1][0] = feather_texture[numFeathers-1][1][0];
		feather_texture[i][1][1] = feather_texture[numFeathers-1][1][1];
		feather_texture[i][3][0] = feather_texture[numFeathers-1][3][0];
		feather_texture[i][3][1] = feather_texture[numFeathers-1][3][1];
	}

}
void Bird::initFeathers(dWorldID world, dSpaceID space){
	numFeathers = 20;
	float thickness_feather = 0.001;
	float width_feather = wing_length[0]/numFeathers;
	featherWidth = width_feather;
	float length_feather = length/2;
	featherArea = 0.5*1.5*length_feather*3*wing_length[0];
	featherLength = new float[numFeathers*6];
	float mass_feather = 0.005;
	feathers = new BodyPart*[6*numFeathers];
	BodyJoint** between_feather = new BodyJoint*[2*(3*numFeathers-1)];

	int numRenderingFeathers = 10;

	/* Have to modify later */
	segmentAreaS = 0.5*0.5*2*(wing_length[0]+wing_length[1]+wing_length[2])*length_feather;
	segmentAreaP = 0.5*0.5*2*(wing_length[0]+wing_length[1]+wing_length[2])*length_feather;

	int p=0;
	float feather_length_txt[180];
	float** feather_texture[180];
	for(int i=0;i<3*numFeathers;i++){
		feather_texture[i] = new float*[4];
		for(int j=0;j<4;j++){
			feather_texture[i][j] = new float[2];
		}

	}
	getFeatherLength(feather_length_txt, factor,3*numFeathers);
	getFeatherTexture(feather_texture, 3*numFeathers);
	for(int sign = 0;sign<=2;sign=sign+2){
		int counter = 0;
		for(int k=0;k<3;k++){
			for(int i=0;i<numFeathers;i++){
				float temp_length = feather_length_txt[counter];
				featherLength[(sign/2*3+k)*numFeathers + i] = temp_length;
				float ratio = (k*numFeathers + i)*1.0/(3*numFeathers);
				QVector3D feather_color = ratio*WHITE + (1-ratio)*GRAY;


				feathers[(sign/2*3+k)*numFeathers + i] = new BoxBodyPart(world,space,Position((sign-1)*(wing_offset_x+(k*numFeathers+i)*width_feather+width_feather/2),wing_offset_y-wing_width/2-temp_length/2,i*thickness_feather),
																			numRenderingFeathers*width_feather,temp_length, thickness_feather, mass_feather, feather_color, feather_texture[counter]);
				if(counter%numRenderingFeathers!=0){
					feathers[(sign/2*3+k)*numFeathers + i]->freeEngine();				
				}
				else{	
					cout<<counter<<endl;
					cout<<(sign-1)*(wing_offset_x+(counter+numRenderingFeathers/2)*width_feather+width_feather/2)<<endl;;
						feathers[(sign/2*3+k)*numFeathers + i]->freeEngine();	
					GeometryEngine* engine = new AerofoilEngine("assets/Curve/bezier.txt");
					engine->update(feather_length_txt[counter],feather_length_txt[counter+numRenderingFeathers-1]);
					QVector2D textureCoord[4];
					for(int i=0;i<4;i++){
						textureCoord[i] = QVector2D(feather_texture[counter][i][0],feather_texture[counter][i][1]);
					}
					engine->init(numRenderingFeathers*width_feather,textureCoord);
					engine->setTexture("textures/parrot.png");
					float cal_pos[3] = {(sign-1)*counter,0,0};
					engine->setPosition(cal_pos);

					feathers[(sign/2*3+k)*numFeathers + i]->setEngine(engine);
				}
				counter++;
			}
		}
	}
	featherJoints = new BodyJoint*[6*numFeathers];

	int feather_mapping[] = {1,1,3,5,7,7,2,2,4,6,8,8};
	for(int k=0;k<12;k++){
		int sign = -2*(feather_mapping[k]%2)+1;
		for(int i=0;i<numFeathers/2;i++){
			featherJoints[k*numFeathers/2+i] = BodyJoint::getJoint(BodyJoint::BALL, world, bodyParts[feather_mapping[k]], feathers[k*numFeathers/2+i]);
			featherJoints[k*numFeathers/2+i]->setAnchor(sign*(wing_offset_x+((k%6)*numFeathers/2+i)*width_feather+3*width_feather/4),wing_offset_y-wing_width/2,i*thickness_feather);
			featherJoints[k*numFeathers/2+i]->setAxises(QVector3D(1,0,0),QVector3D(0,-1,0));
			featherJoints[k*numFeathers/2+i]->setParams(dParamLoStop,-M_PI/20);
			featherJoints[k*numFeathers/2+i]->setParams(dParamHiStop,M_PI/20);
			featherJoints[k*numFeathers/2+i]->setParams(dParamLoStop1,-M_PI/20);
			featherJoints[k*numFeathers/2+i]->setParams(dParamHiStop1,M_PI/20);
			featherJoints[k*numFeathers/2+i]->setParams(dParamLoStop2,-M_PI/20);
			featherJoints[k*numFeathers/2+i]->setParams(dParamHiStop2,M_PI/20);
		}
	}
	float feather_angle = M_PI/15;
	for(int i=0;i<3*numFeathers;i++){
		featherJoints[i]->dof[0] = DOF(-feather_angle, feather_angle, 0, 1, DOF::TWO);
		featherJoints[i]->dof[1] = DOF(-feather_angle, feather_angle, 0, 1, DOF::TWO);
		featherJoints[i]->dof[2] = DOF(-feather_angle, feather_angle, 0, 1, DOF::TWO);
		featherJoints[i]->setForceCoef(1,1);
	}
	for(int i=3*numFeathers;i<6*numFeathers;i++){
		featherJoints[i]->dof[0] = DOF(feather_angle, -feather_angle, 0, 1, DOF::TWO);
		featherJoints[i]->dof[1] = DOF(feather_angle, -feather_angle, 0, 1, DOF::TWO);
		featherJoints[i]->dof[2] = DOF(feather_angle, -feather_angle, 0, 1, DOF::TWO);
		featherJoints[i]->setForceCoef(1,1);
	}	
}

void Bird::initTail(dWorldID world, dSpaceID space){
	int numFeathers = 3;
	float thickness_feather = 0.001;
	float width_feather = length/8;
	float length_feather = length/4;
	
	cout<<length_feather<<endl;
	float mass_feather = 0.005;
	QVector3D feather_color = BROWN;
	float spread_angle = M_PI/3;
	tailFeathers = new BodyPart*[2*numFeathers+1];
	for(int i=-numFeathers;i<=numFeathers;i++){
		int k = i+numFeathers;
		tailFeathers[k] = new BoxBodyPart(world,space,Position(0,bird_center-length/2-length_feather/2,0),
						width_feather,length_feather,thickness_feather,mass_feather,feather_color
						);
	  	tailFeathers[k]->getEngine()->setTexture("textures/feather.jpg");

		QMatrix4x4 mat;
		mat.setToIdentity();
		mat.scale(1/sqrt(2),1/sqrt(2),1);
		mat.rotate(45,QVector3D(0,0,-1));
		tailFeathers[k]->setCalliberation(mat);

	}

	tailFeatherJoints = new BodyJoint*[2*numFeathers+1];

	for(int i=-numFeathers;i<=numFeathers;i++){
		int k = i+numFeathers;
		tailFeatherJoints[k] = BodyJoint::getJoint(BodyJoint::BALL,world,
			bodyParts[0],tailFeathers[k]);
		tailFeatherJoints[k]->setAnchor(0,bird_center-length/2,0);
		tailFeatherJoints[k]->setAxises(QVector3D(1,0,0),QVector3D(0,-1,0));

		tailFeatherJoints[k]->setParams(dParamLoStop,-M_PI/20);
		tailFeatherJoints[k]->setParams(dParamHiStop,M_PI/20);
		tailFeatherJoints[k]->setParams(dParamLoStop1,-M_PI/20);
		tailFeatherJoints[k]->setParams(dParamHiStop1,M_PI/20);
		tailFeatherJoints[k]->setParams(dParamLoStop2,i*spread_angle/6);
		tailFeatherJoints[k]->setParams(dParamHiStop2,i*spread_angle/6);
	}
	float feather_angle = M_PI/20;
	for(int i=-numFeathers;i<=numFeathers;i++){
		int k = i+numFeathers;
		tailFeatherJoints[k]->dof[0] = DOF(-feather_angle, feather_angle, 0, 1, DOF::TWO);
		tailFeatherJoints[k]->dof[1] = DOF(-feather_angle, feather_angle, 0, 1, DOF::TWO);
		tailFeatherJoints[k]->dof[2] = DOF(i*spread_angle/6, (i+1)*spread_angle, 0, 1, DOF::TWO);
		tailFeatherJoints[k]->setForceCoef(1,1);
	}
}

void Bird::readSpecifications(float ** arr, int numElements){
  FILE * file = fopen(birdSpecifications.c_str(), "r");
  if( file == NULL ){
    printf("Impossible to open the file !\n");
    return ;
  }
  char lineHeader[256];
  for(int i=0;i<numElements;i++){
     fscanf(file, "m %f # %s\n", arr[i], lineHeader);
  }

}

void Bird::init(dWorldID world, dSpaceID space){
	initBodyParts(world, space);
	initBodyJoints(world);
	initFeathers(world, space);
	initTail(world, space);
}

void Bird::resize(){
	wing_offset_y = length - wing_offset_y;
	length = length/factor;
	wingspan = wingspan/factor;
	trunk_width = trunk_width/factor;
	wing_width = wing_width/factor;
	bird_center = bird_center/factor;
	wing_offset_y = wing_offset_y/factor;
	wing_offset_x = wing_offset_x/factor;
}

Bird::Bird(dWorldID world,dSpaceID space){
	t = 0;
	numBodyParts = 9;
	numBodyJoints = 8;
	numFeathers = 60;
	numTailFeathers = 7;

	bodyParts = new BodyPart*[numBodyParts];
	feathers = new BodyPart*[numFeathers];
	tailFeathers = new BodyPart*[numTailFeathers];

	bodyJoints = new BodyJoint*[numBodyJoints];
	featherJoints = new BodyJoint*[numFeathers];
	tailFeatherJoints = new BodyJoint*[numTailFeathers];

	birdSpecifications = "assets/birdSpecifications/bird_dimensions.txt";

	float * arr[10] = {
		&length,
		&wingspan,
		&trunk_width,
		&wing_width,
		&bird_center,
		&wing_offset_x,
		&wing_offset_y,
		&factor,
		&weight,
		&timePeriod
	};

	readSpecifications(arr, 10);
	resize();

	float wing_length_total = (wingspan-trunk_width)/2;
	wing_length[0] = wing_length_total/3;
	wing_length[1] = wing_length_total/3;
	wing_length[2] = wing_length_total/3;


	init(world, space);
}

void Bird::drawBody(QOpenGLShaderProgram *program){
	for(int i=0;i<numBodyParts;i++){
		bodyParts[i]->draw(program);		
	}
}

void Bird::drawFeathers(QOpenGLShaderProgram *program){
	for(int i=0*numFeathers;i<numFeathers*6;i++){
		feathers[0]->draw(program);
	}
}

void Bird::drawTail(QOpenGLShaderProgram *program){
	for(int i=0;i<numTailFeathers;i++){
		tailFeathers[i]->draw(program);
	}	
}

void Bird::draw(QOpenGLShaderProgram *program){

	// drawBody(program);
	drawFeathers(program);
	// drawTail(program);
	// horizontalSupport->draw(program);

	int k = t/timePeriod;
	phaseAngle = t - k*timePeriod;
	applyForces(phaseAngle);
	t = t+0.012;
	getLift();
}

void Bird::applyBodyForces(float t){
	for(int i=0;i<numBodyJoints;i++){
		bodyJoints[5]->applyForce(t);
	}
}

void Bird::applyFeatherForces(float t){
	for(int i=0;i<6*numFeathers;i++){
		featherJoints[i]->applyForce(t);	
	}
}

void Bird::applyTailForces(float t){
	for(int i=0;i<numTailFeathers;i++){
		tailFeatherJoints[i]->applyForce(t);	
	}	
}

void Bird::applyForces(float t){
	applyBodyForces(t);
	applyFeatherForces(t);
	applyTailForces(t);
}

float Bird::getLift(){



	float total_force = 0;
	float speed;
	const float* bodyAxis = dBodyGetQuaternion(bodyParts[0]->body);
	const float* wingAxis = dBodyGetQuaternion(bodyParts[1]->body);
	dQuaternion alongY, alongX ;
	dQFromAxisAndAngle(alongY ,0, 1, 0, 0);
	dQFromAxisAndAngle(alongX, 1, 0, 0, 0);
	// cout<<bodyAxis[0]<<" "<<bodyAxis[1]<<" "<<bodyAxis[2]<<" "<<bodyAxis[3]<<endl;
	// cout<<wingAxis[0]<<" "<<wingAxis[1]<<" "<<wingAxis[2]<<" "<<wingAxis[3]<<endl;
	// cout<<alongY[0]<<" "<<alongY[1]<<" "<<alongY[2]<<" "<<alongY[3]<<endl;
	// cout<<alongX[0]<<" "<<alongX[1]<<" "<<alongX[2]<<" "<<alongX[3]<<endl;
	
	float body_axis_angle = getAngle(alongY, bodyAxis);
	float wing_axis_angle = getAngle(alongX, wingAxis);

	// cout<<body_axis_angle*180/M_PI<<" "<<wing_axis_angle*180/M_PI<<endl;
	
	// float sin_theta ;
	// if(cos_theta<=1 && cos_theta>=-1)
	// 	 sin_theta = sqrt(1 - cos_theta*cos_theta);
	// else
	// 	sin_theta = 0;
	// {
	//   speed = bodyJoints[0]->getSpeed(t);
	// 	float force = getForce(t,width_each_feather,featherLength[30],speed);
	// 	// cout<<force<<" "<<t<<endl;
	// 	dBodyAddForce(bodyParts[1]->body,0,force*numFeathers*cos_theta,0);
	// 	dBodyAddForce(bodyParts[2]->body,0,force*numFeathers*cos_theta,0);
	// 	total_force+=force*120;
	// }
	// {
	//   speed = bodyJoints[2]->getSpeed(t);
	// 	float force = getForce(t,width_each_feather,featherLength[90],speed);
	// 	// cout<<force<<" "<<t<<endl;
	// 	dBodyAddForce(bodyParts[3]->body,0,cos_theta*force*numFeathers/2,0);
	// 	dBodyAddForce(bodyParts[4]->body,0,cos_theta*force*numFeathers/2,0);
	// 	dBodyAddForce(bodyParts[5]->body,0,cos_theta*force*numFeathers/2,0);
	// 	dBodyAddForce(bodyParts[6]->body,0,cos_theta*force*numFeathers/2,0);
	// 	total_force+=force*120;
	// }
	// {
	//   speed = bodyJoints[6]->getSpeed(t);
	// 	float force = getForce(t,width_each_feather,featherLength[150],speed);
	// 	// cout<<force<<" "<<t<<endl;
	// 	dBodyAddForce(bodyParts[7]->body,0,cos_theta*force*numFeathers,0);
	// 	dBodyAddForce(bodyParts[8]->body,0,cos_theta*force*numFeathers,0);
	// 	total_force+=cos_theta*force*120;
	// }
	// // cout<<force<<" "<<speed<<" "<<width_each_feather<<" "<<featherLength[i]<<endl;
	// // float force = getForce(t,width_each_feather,featherLength[i],speed);
	// cout<<total_force<<endl;
	// if(total_force<=11018)
	// 	dBodyAddForce(bodyParts[0]->body,0,-total_force,0);
	// 	// dBodyAddForce(bodyParts[0]->body,0,11018,0);

	// for
	// for(int i=0;i<numFeathers;i++){
	// 	dBodyAddForce(feathers[i]->body,0,0.05,0);
	// }
	// for(int i=0;i<10;i++){
	// 	dBodyAddForce(feathers[i]->body,0,0.05,0);
	// }
	//
	// dBodyAddForce(bodyParts[0]->body,0,2018,0);
	//

}


void Bird::applyExternalForce(float fx, float fy, float fz){
	bodyParts[0]->applyExternalForce(fx, fy, fz);
}

void Bird::applyExternalTorque(float tx, float ty, float tz){
	bodyParts[0]->applyExternalTorque(tx, ty, tz);
}

const float* Bird::getOrientation(){
	return bodyParts[0]->getOrientation();
}

