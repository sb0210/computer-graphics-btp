#ifndef OBJENGINE_H
#define OBJENGINE_H

#include "geometry/GeometryEngine.h"

class OBJEngine: public GeometryEngine{
public:
  string path;
  OBJEngine(string path, float lx, float ly, float lz);
  void init();
};

#endif