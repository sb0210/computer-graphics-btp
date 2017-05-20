#include "geometry/DiskEngine.h"

DiskEngine::DiskEngine(float radius):ArcEngine(radius, 360){}
void DiskEngine::update(float radius){
  ArcEngine::update(radius, 360);
}

