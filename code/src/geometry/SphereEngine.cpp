#include "geometry/SphereEngine.h"

SphereEngine::SphereEngine(float radius): EllipsoidEngine(radius, radius, radius){}

void SphereEngine::update(float radius){
  EllipsoidEngine::update(radius, radius, radius);
}
