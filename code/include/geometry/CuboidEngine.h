#ifndef CUBOIDENGINE_H
#define CUBOIDENGINE_H

#include "geometry/GeometryEngine.h"

class CuboidEngine: public GeometryEngine{
public:
  float lx,ly,lz;
  CuboidEngine(float lx, float ly, float lz);
  void init();
  void init(float **);
  virtual void update(float lx, float ly, float lz);
};

#endif