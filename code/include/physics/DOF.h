#ifndef DOF_H
#define DOF_H

#include "physics/DOF.h"

class DOF{
  public:
    float q_min,q_max;
    float u_up,u_down;
    float T;
    vector<float> coeff;
    vector<float> x_coordinates;
    float alpha, beta;
    enum Category{
      ONE,
      TWO
    };
    Category category;
    DOF();
    DOF(float q_min, float q_max, float u_up, float u_down, Category category);
    float g1(float t);
    float g2(float t);
    float qt(float t);
    float speedg1(float t);
    float speedg2(float t);
    float speedqt(float t);
    float getPhiDash(float phi);
    void setTimePeriod(float T);

};

#endif