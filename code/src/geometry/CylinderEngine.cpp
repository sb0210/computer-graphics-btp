#include "geometry/CylinderEngine.h"

CylinderEngine::CylinderEngine(float radius, float height):FrustumEngine(radius, radius, height){
}
void CylinderEngine::update(float radius, float height){
  FrustumEngine::update(radius, radius, height);
}

