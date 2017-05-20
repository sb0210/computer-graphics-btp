#include "physics/DOF.h"

DOF::DOF(){};

DOF::DOF(float q_min, float q_max, float u_up, float u_down, Category category){
  this->q_min = q_min;
  this->q_max = q_max;
  this->u_up = u_up;
  this->u_down = u_down;
  this->category = category;
  alpha = 0.5;
  beta = 0.5;

  vector<float>x, y;
  x.push_back(0);       y.push_back(0);
  x.push_back(0);       y.push_back(1);
  x.push_back(2*M_PI*alpha);  y.push_back(M_PI);
  x.push_back(2*M_PI);    y.push_back(2*M_PI);
  x.push_back(2*M_PI);    y.push_back(1);

  int sz = x.size();
  for(int i=1;i<sz;i++){
    if(x[i]==x[i-1]){
      y[i] = y[i-1] + 0.00001*y[i];
      x[i] = x[i]   + 0.00001;
    }
  }

  coeff = getNewtonCoefficient(x,y);
  x_coordinates = x;

  T = 2;

}
void DOF::setTimePeriod(float T){
  this->T = T;
}

float DOF::g1(float t){
    return (u_up - u_down)*(1 + cos(2*M_PI*t/T))/2 + u_down;
}

float DOF::speedg1(float t){
  return (u_up-u_down)*(-2*M_PI/T*sin(2*M_PI*t/T));
}

float DOF::g2(float t){
  if(t<T/2)
    return u_down;
  else
    return (u_up - u_down)*(1 - cos(2*M_PI*2*t/T))/2 + u_down;
}

float DOF::speedg2(float t){
  if(t<T/2){
    return 0;
  }
  else{
    return (u_up-u_down)*(2*M_PI*2/T*sin(2*M_PI*2*t/T));
  }
}

float DOF::qt(float t){
  if(category == ONE){
      return q_min + (q_max-q_min)*g1(t);
  }
  else return q_min + (q_max-q_min)*g2(t);
}

float DOF::getPhiDash(float phi){
  float ans;
  ans = getPolynomial(phi, coeff, x_coordinates);
  return ans;
}

float DOF::speedqt(float t){
  t = getPhiDash(t*2*M_PI/T);
  if(category==ONE){
    return (q_max-q_min)*speedg1(t);
  }
  else return (q_max-q_min)*speedg2(t);
}