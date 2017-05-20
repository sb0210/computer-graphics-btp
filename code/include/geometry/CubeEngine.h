#ifndef CUBEENGINE_H
#define CUBEENGINE_H

#include "geometry/CuboidEngine.h"

class CubeEngine: public CuboidEngine{
public:
  CubeEngine(float length);
  void update(float length);
};

#endif