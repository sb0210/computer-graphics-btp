#ifndef ELLIPSOIDCONEENGINE_H
#define ELLIPSOIDCONEENGINE_H

#include "geometry/GeometryEngine.h"

class EllipsoidEngine: public GeometryEngine{
public:
  float rx, ry, rz;
  EllipsoidEngine(float rx, float ry, float rz);
  void init();
  virtual void update(float rx, float ry, float rz);
};

#endif