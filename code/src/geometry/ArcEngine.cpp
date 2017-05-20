#include "geometry/ArcEngine.h"

ArcEngine::ArcEngine(float radius, float angle){
  init();
  update(radius, angle);
}
void ArcEngine::update(float radius, float angle){
  this->radius = radius;
  this->angle = angle;
  GeometryEngine::update(radius,radius,1);
}
void ArcEngine::init(){
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;
  float numSlices = 89 ;

  float x0 = 0, y0 = 0, z0 = 0;
  QVector3D point0(x0,y0,z0);
  QVector2D texCoord0((x0+1)/2,(z0+1)/2);
  VertexData v0 = {point0,texCoord0,color};

  vertices.push_back(v0);
  indices.push_back(0);

  for(int i=1;i<=numSlices+2;i++){

    float x1 = qCos(qDegreesToRadians(i*angle/numSlices));
    float y1 = qSin(qDegreesToRadians(i*angle/numSlices));;
    float z1 = qSin(qDegreesToRadians(i*angle/numSlices));
    QVector3D point1(x1,y1,z1);
    QVector2D texCoord1((x1+1)/2,(z1+1)/2);

    VertexData v1 = {point1,texCoord1, color};
    vertices.push_back(v1);

    indices.push_back(i+1);
  }

  numIndices = indices.size();
  numVertices = vertices.size();
  bind(&vertices[0],&indices[0]);
  setPrimitive(GL_TRIANGLE_FAN);
}

