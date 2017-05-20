#ifndef CAPSULEENGINE_H
#define CAPSULEENGINE_H

#include "geometry/GeometryEngine.h"

class CapsuleEngine: public GeometryEngine{
public:
  GeometryEngine* myCylinderEngine;
  GeometryEngine* myHemisphereEngine1;
  GeometryEngine* myHemisphereEngine2;
  CapsuleEngine(float radius, float length);
  void init();
  void update(float radius, float length);
};

#endif
