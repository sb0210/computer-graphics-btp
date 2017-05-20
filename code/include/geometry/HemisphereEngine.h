#ifndef HEMISPHEREENGINE_H
#define HEMISPHEREENGINE_H

#include "geometry/GeometryEngine.h"

class HemiSphereEngine: public GeometryEngine{
public:
    float radius;
    HemiSphereEngine(float radius, float angle1, float angle2);
    HemiSphereEngine(float radius, float angle_minx, float angle_maxX, float angle_minY, float angle_maxY);
    void update(float radius);
    void update(float radius, float distanceZ);
    void update(float lx, float ly, float lz);
    void init(float angle_minx, float angle_maxX, float angle_minY, float angle_maxY);
};

#endif