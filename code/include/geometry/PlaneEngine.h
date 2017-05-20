#ifndef PLANEENGINE_H
#define PLANEENGINE_H

#include "geometry/GeometryEngine.h"

class PlaneEngine: public GeometryEngine{
public:
  float a,b,c,d;
  PlaneEngine(float a, float b, float c, float d);
  void init();
};

#endif