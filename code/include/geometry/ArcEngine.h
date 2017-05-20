#ifndef ARCENGINE_H
#define ARCENGINE_H

#include "geometry/GeometryEngine.h"

class ArcEngine: public GeometryEngine{
public:
  float radius, angle;
  ArcEngine(float radius, float angle);
  void init();
  virtual void update(float radius, float angle);
};

#endif