#ifndef SPHEREENGINE_H
#define SPHEREENGINE_H

#include "geometry/EllipsoidEngine.h"

class SphereEngine: public EllipsoidEngine{
public:
  SphereEngine(float radius);
  void update(float radius);
};

#endif