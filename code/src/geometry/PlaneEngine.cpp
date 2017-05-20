#include "geometry/PlanepEngine.h"

PlaneEngine::PlaneEngine(float a, float b, float c, float d){
  this->a = a;
  this->b = b;
  this->c = c;
  this->d = d;
}
void PlaneEngine::init(){
  float left = -20;
  float right = 20;
  float near = 20;
  float far = -20;

  float x[4] = {left,left, right, right};
  float z[4] = {near, far, far, near};
  float y[4];
  for(int i=0;i<4;i++){
    y[i] = (d - a*x[i] - c*z[i])/b;
  }

  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;

  QVector2D texCoord[4] = {QVector2D(0,0),QVector2D(0,1),QVector2D(1,1),QVector2D(1,0)};
  QVector3D points[4];
  for(int i=0;i<4;i++)
    points[i] = QVector3D(x[i],y[i],z[i]);

  for(int i=0;i<4;i++){
    VertexData v = {points[i],texCoord[i],color};
    vertices.push_back(v);
  }

  indices.push_back(1);
  indices.push_back(0);
  indices.push_back(2);
  indices.push_back(3);
  indices.push_back(3);
  indices.push_back(3);

  numIndices = indices.size();
  numVertices = vertices.size();
  bind(&vertices[0],&indices[0]);

}


