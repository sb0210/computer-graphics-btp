#include "geometry/ConeEngine.h"

ConeEngine::ConeEngine(float radius,float height):FrustumEngine(radius,0, height){}
void ConeEngine::update(float radius, float height){
  FrustumEngine::update(radius, 0, height);
}

