#ifndef CYLINDERNGINE_H
#define CYLINDERNGINE_H

#include "geometry/FrustumEngine.h"

class CylinderEngine: public FrustumEngine{
public:
  CylinderEngine(float radius, float height);
  void update(float radius, float height);
};

#endif