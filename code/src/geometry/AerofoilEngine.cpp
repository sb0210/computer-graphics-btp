#include "geometry/AerofoilEngine.h"

AerofoilEngine::AerofoilEngine(string filename){
  ifstream file;
  file.open(filename.c_str());
  file>>num; 
  for(int i=0;i<num;i++){
    float x,y;
    file>>x>>y;
    points[0][i] = QVector2D(x,y);
    points[2][i] = QVector2D(x,y);
  }
  for(int i=0;i<num;i++){
    float x,y;
    file>>x>>y;
    points[1][i] = QVector2D(x,y);
    points[3][i] = QVector2D(x,y);
  }
}

void AerofoilEngine::update(float length1, float length2){
  this->length1 = length1;
  this->length2 = length2;
  for(int i=0;i<num;i++){
    points[0][i] = points[0][i]*length1;
    points[1][i] = points[1][i]*length1;
    points[2][i] = points[2][i]*length2;
    points[3][i] = points[3][i]*length2;
  }  

}


void AerofoilEngine::init(float width, QVector2D texCoordAerofoil[4]){
  std::vector<VertexData> vertices;
  std::vector<GLushort> indices;

  int p = 0;
  for(int i=0;i<num-1;i++){

    QVector2D texCoord[4] = {QVector2D(0,points[0][i].y()/length1),QVector2D(0,points[0][i+1].y()/length1),QVector2D(1,points[1][i+1].y()/length1),QVector2D(1,points[1][i].y()/length1)};
    QVector3D _points[4];

    _points[0] = QVector3D(0,points[0][i].y(),-points[0][i].x());
    _points[1] = QVector3D(0,points[0][i+1].y(),-points[0][i+1].x());
    _points[2] = QVector3D(0,points[1][i+1].y(),-points[1][i+1].x());
    _points[3] = QVector3D(0,points[1][i].y(),-points[1][i].x());

    for(int i=0;i<4;i++){
      VertexData v = {_points[i],texCoord[i],color};
      vertices.push_back(v);
    }
    indices.push_back(p+1);
    indices.push_back(p+0);
    indices.push_back(p+2);
    indices.push_back(p+2);
    indices.push_back(p+0);
    indices.push_back(p+3);
    p = p + 4;
  }
  for(int i=0;i<num-1;i++){
    QVector2D texCoord[4] = {QVector2D(0,points[0][i].y()/length2),QVector2D(0,points[0][i+1].y()/length2),QVector2D(1,points[1][i+1].y()/length2),QVector2D(1,points[1][i].y()/length2)};
    QVector3D _points[4];
    _points[0] = QVector3D(width,points[0][i].y(),-points[0][i].x());
    _points[1] = QVector3D(width,points[0][i+1].y(),-points[0][i+1].x());
    _points[2] = QVector3D(width,points[1][i+1].y(),-points[1][i+1].x());
    _points[3] = QVector3D(width,points[1][i].y(),-points[1][i].x());

    for(int i=0;i<4;i++){
      VertexData v = {_points[i],texCoord[i],color};
      vertices.push_back(v);
    }

    indices.push_back(p+1);
    indices.push_back(p+0);
    indices.push_back(p+2);
    indices.push_back(p+2);
    indices.push_back(p+0);
    indices.push_back(p+3);
    p = p + 4;
  }

  for(int i=0;i<num-1;i++){

    QVector3D _points[4];
    _points[0] = QVector3D(0,points[0][i].y(),-points[0][i].x());
    _points[1] = QVector3D(0,points[0][i+1].y(),-points[0][i+1].x());
    _points[2] = QVector3D(width,points[2][i+1].y(),-points[2][i+1].x());
    _points[3] = QVector3D(width,points[2][i].y(),-points[2][i].x());

    for(int i=0;i<4;i++){
      VertexData v = {_points[i],texCoordAerofoil[i],color};
      vertices.push_back(v);
    }

    indices.push_back(p+1);
    indices.push_back(p+0);
    indices.push_back(p+2);
    indices.push_back(p+2);
    indices.push_back(p+0);
    indices.push_back(p+3);
    p = p + 4;
  }

  for(int i=0;i<num-1;i++){

    QVector3D _points[4];
    _points[0] = QVector3D(0,points[1][i].y(),-points[1][i].x());
    _points[1] = QVector3D(0,points[1][i+1].y(),-points[1][i+1].x());
    _points[2] = QVector3D(width,points[3][i+1].y(),-points[3][i+1].x());
    _points[3] = QVector3D(width,points[3][i].y(),-points[3][i].x());

    for(int i=0;i<4;i++){
      VertexData v = {_points[i],texCoordAerofoil[i],color};
      vertices.push_back(v);
    }

    indices.push_back(p+1);
    indices.push_back(p+0);
    indices.push_back(p+2);
    indices.push_back(p+2);
    indices.push_back(p+0);
    indices.push_back(p+3);
    p = p + 4;
  }

  numIndices = indices.size();
  numVertices = vertices.size();
  bind(&vertices[0],&indices[0]);

  setPrimitive(GL_TRIANGLES);
}