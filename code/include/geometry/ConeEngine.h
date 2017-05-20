#ifndef CONEENGINE_H
#define CONEENGINE_H

#include "geometry/FrustumEngine.h"

class ConeEngine: public FrustumEngine{
public:
  ConeEngine(float radius, float height);
  void update(float radius, float topRadius);
};

#endif