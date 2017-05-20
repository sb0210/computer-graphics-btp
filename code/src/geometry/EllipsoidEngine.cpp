#include "geometry/EllipsoidEngine.h"

EllipsoidEngine::EllipsoidEngine(float rx, float ry, float rz):GeometryEngine(){
  update(rx,ry,rz);
}
void EllipsoidEngine::update(float rx, float ry, float rz){
  this->rx = rx;
  this->ry = ry;
  this->rz = rz;
  GeometryEngine::update(rx,ry,rz);
}
void EllipsoidEngine::init(){
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;
  float numSlicesX=89, numSlicesY=89;
  for(int i=0;i<numSlicesX;i++){
    for(int j=0;j<numSlicesY;j++){
      float angleX1 = (i*360.0)/numSlicesX;
      float angleY1 = (j*180.0)/numSlicesY;
      float angleX2 = ((i+1)*360.0)/numSlicesX;
      float angleY2 = ((j+1)*180.0)/numSlicesY;


      float x1 = qSin(qDegreesToRadians(angleY1))*qCos(qDegreesToRadians(angleX1));
      float y1 = qCos(qDegreesToRadians(angleY1));
      float z1 = qSin(qDegreesToRadians(angleY1))*qSin(qDegreesToRadians(angleX1));

      QVector3D point1(x1,y1,z1);
      QVector2D texCoord1(angleX1/360,angleY1/180);
      VertexData v1 = {point1,texCoord1,color};

      float x2 = qSin(qDegreesToRadians(angleY2))*qCos(qDegreesToRadians(angleX1));
      float y2 = qCos(qDegreesToRadians(angleY2));
      float z2 = qSin(qDegreesToRadians(angleY2))*qSin(qDegreesToRadians(angleX1));
      QVector3D point2(x2,y2,z2);
      QVector2D texCoord2(angleX1/360,angleY2/180);
      VertexData v2 = {point2,texCoord2, color};

      float x3 = qSin(qDegreesToRadians(angleY2))*qCos(qDegreesToRadians(angleX2));
      float y3 = qCos(qDegreesToRadians(angleY2));
      float z3 = qSin(qDegreesToRadians(angleY2))*qSin(qDegreesToRadians(angleX2));
      QVector3D point3(x3,y3,z3);
      QVector2D texCoord3(angleX2/360,angleY2/180);
      VertexData v3 = {point3,texCoord3, color};

      float x4 = qSin(qDegreesToRadians(angleY1))*qCos(qDegreesToRadians(angleX2));
      float y4 = qCos(qDegreesToRadians(angleY1));
      float z4 = qSin(qDegreesToRadians(angleY1))*qSin(qDegreesToRadians(angleX2));
      QVector3D point4(x4,y4,z4);
      QVector2D texCoord4(angleX2/360,angleY1/180);
      VertexData v4 = {point4,texCoord4, color};

      vertices.push_back(v1);
      vertices.push_back(v2);
      vertices.push_back(v3);
      vertices.push_back(v4);

      indices.push_back(4*(i*numSlicesY+j)+1);
      indices.push_back(4*(i*numSlicesY+j));
      indices.push_back(4*(i*numSlicesY+j)+2);
      indices.push_back(4*(i*numSlicesY+j)+3);
      indices.push_back(4*(i*numSlicesY+j)+3);
      indices.push_back(4*(i*numSlicesY+j)+3);
    }
  }
  numVertices = vertices.size();
  numIndices = indices.size();
  bind(&vertices[0],&indices[0]);
}

