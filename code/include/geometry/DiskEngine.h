#ifndef DISKENGINE_H
#define DISKENGINE_H

#include "geometry/ArcEngine.h"

class DiskEngine: public ArcEngine{
public:
  DiskEngine(float radius);
  void update(float radius);
};

#endif