#include "geometry/CubeEngine.h"

CubeEngine::CubeEngine(float length): CuboidEngine(length, length, length){}
void CubeEngine::update(float length){
  CuboidEngine::update(length,length,length);
}
