#ifndef AEROFOILENGINE_H
#define AEROFOILENGINE_H

#include "geometry/GeometryEngine.h"

class AerofoilEngine: public GeometryEngine{
public:
  string filename;
  int num;
  float length1, length2;
  QVector2D points[4][100];

  AerofoilEngine(string filename);
  void update(float length1, float length2);
  void init(float width, QVector2D texCoordAerofoil[4]);
};

#endif