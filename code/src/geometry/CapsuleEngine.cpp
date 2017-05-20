#include "geometry/CapsuleEngine.h"

CapsuleEngine::CapsuleEngine(float radius, float length): GeometryEngine(){
  myCylinderEngine = new CylinderEngine(radius, length);
  myHemisphereEngine1 = new HemiSphereEngine(radius, 180, 360);
  myHemisphereEngine2 = new HemiSphereEngine(radius, 0, 180);
  init();
  update(radius, length);
}

void CapsuleEngine::init(){
  myCylinderEngine->init();
  myHemisphereEngine1->init();
  myHemisphereEngine2->init();
}
void CapsuleEngine::update(float radius, float length){
  myCylinderEngine->update(radius,length);
  myHemisphereEngine1->update(radius,length/2);
  myHemisphereEngine2->update(radius,-length/2);
}
