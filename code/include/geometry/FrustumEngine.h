#ifndef FRUSTUMENGINE_H
#define FRUSTUMENGINE_H

#include "geometry/GeometryEngine.h"

class FrustumEngine: public GeometryEngine{
public:
  float baseRadius, topRadius, height;
  FrustumEngine(float baseRadius, float topRadius, float height);
  void init(float ratio);
  virtual void update(float baseRadius, float topRadius, float height);
};

#endif