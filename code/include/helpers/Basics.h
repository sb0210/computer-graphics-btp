#ifndef __BASICS_H_INCLUDED__
#define __BASICS_H_INCLUDED__

#include <QVector3D>

#include "helpers/Includes.h"

void setValue(float* R, int i, int j, float value);
void printMatrix(const float* R);
void printMatrix4x4(QMatrix4x4 matrix);
vector<float> getNewtonCoefficient(vector<float>& x, vector<float>& y);
float getPolynomial(float point, vector<float>& coeff, vector<float>& x);
float getCl(float);
float getForce(float t, float s, float a, float v);
float getCosine(const float* a, const float* c);
float getAngle(const float* a, const float* c);
void getFeatherLength(float feather_length_txt[], float factor, int numFeathers);
void getFeatherTexture(float ** feather_texture[], int numFeathers);
void readSpecifications(float ** arr, string birdSpecifications, int numElements);


// bool loadObj(
//   string path,
//   std::vector<QVector3D> & vertices,
//   std::vector<QVector3D> & u_v,
//   std::vector<QVector3D> & normals
// );
#endif
