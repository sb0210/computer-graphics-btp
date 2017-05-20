#include "geometry/FrustumEngine.h"

FrustumEngine::FrustumEngine(float baseRadius, float topRadius, float height):GeometryEngine(){
  init(topRadius/baseRadius);
  update(baseRadius, topRadius, height);
}
void FrustumEngine::update(float baseRadius, float topRadius, float height){
  this->baseRadius = baseRadius;
  this->topRadius = topRadius;
  this->height = height;
  GeometryEngine::update(baseRadius,baseRadius,height);
}
void FrustumEngine::init(float ratio){
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;
  float numSlices = 100 ;
  for(int i=0;i<numSlices;i++){

    float x1 = ratio*qCos(qDegreesToRadians(i*360.0/numSlices));
    float y1 = ratio*qSin(qDegreesToRadians(i*360.0/numSlices));
    float z1 = 0.5;
    QVector3D point1(x1,y1,z1);
    QVector2D texCoord1(i*1.0/numSlices,1);

    float x2 = qCos(qDegreesToRadians(i*360.0/numSlices));
    float y2 = qSin(qDegreesToRadians(i*360.0/numSlices));
    float z2 = -0.5;
    QVector3D point2(x2,y2,z2);
    QVector2D texCoord2(i*1.0/numSlices,0);


    float x3 = qCos(qDegreesToRadians((i+1)*360.0)/numSlices);
    float y3 = qSin(qDegreesToRadians((i+1)*360.0)/numSlices);
    float z3 = -0.5;
    QVector3D point3(x3,y3,z3);
    QVector2D texCoord3((i+1)*1.0/numSlices,0);

    float x4 = ratio*qCos(qDegreesToRadians((i+1)*360.0)/numSlices);
    float y4 = ratio*qSin(qDegreesToRadians((i+1)*360.0)/numSlices);
    float z4 = 0.5;
    QVector3D point4(x4,y4,z4);
    QVector2D texCoord4((i+1)*1.0/numSlices,1);
    VertexData v1 = {point1,texCoord1, color}, v2 = {point2,texCoord2, color}, v3 = {point3,texCoord3, color}, v4 = {point4,texCoord4, color};
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    indices.push_back(4*i+1);
    indices.push_back(4*i);
    indices.push_back(4*i+2);
    indices.push_back(4*i+3);
    indices.push_back(4*i+3);
    indices.push_back(4*i+3);
  }
  numIndices = indices.size();
  numVertices = vertices.size();
  bind(&vertices[0],&indices[0]);
}

