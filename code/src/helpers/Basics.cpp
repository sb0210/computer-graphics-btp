#include "helpers/Basics.h"


void setValue(float* R, int i, int j, float value){
  R[i*4+j] = value;
}

void printMatrix(const float* R){
  for(int i=0;i<12;i++){
    cout<<R[i]<<" ";
    if((i+1)%4==0)cout<<endl;
  }
}

void printMatrix4x4(QMatrix4x4 matrix){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      std::cout<<matrix(i,j)<<" ";
    }
    std::cout<<std::endl;
  }
}

vector<float> getNewtonCoefficient(vector<float>& x, vector<float>& y){
  int sz = x.size();

  vector< vector<float> > v (sz);
  for(int i = 0;i<sz;i++){
    v[i].resize(sz);
  }
  for(int i=0;i<sz;i++){
    v[0][i] = y[i];
  }
  for(int i=1;i<sz;i++){
    for(int j=0;j<sz-i;j++){
      v[i][j] = (v[i-1][j] - v[i-1][j+1])/(x[j] - x[i+j]);
    }
  }  

  vector<float> ans;
  for(int i=0;i<sz;i++){
    ans.push_back(v[i][0]);
  }
  return ans;
}


float getPolynomial(float point, vector<float>& coeff, vector<float>& x ){

  float ans = 0;
  for(unsigned int i=0;i<x.size();i++){
    float val = 1;
    for(unsigned int j = 0;j<i;j++){
      val = val*(point - x[j]);
    }
    ans = ans + coeff[i]*val;
  }
  return ans;
}



float getCl(float){
  return 5;
}

float getForce(float t, float s, float a, float v){
  float cl = getCl(t);
  float rho = 1;
  float force = 0.5*cl*rho*s*a*v*v;
  return force;
}



float getCosine(const float* a, const float* c){
  float b[4] = {c[0],c[1],c[2],c[3]};
  float ans[4] ={
  a[0] * b[0] - a[1] * b[1] - a[2] * b[2] - a[3] * b[3],  // 1
  a[0] * b[1] + a[1] * b[0] + a[2] * b[3] - a[3] * b[2],  // i
  a[0] * b[2] - a[1] * b[3] + a[2] * b[0] + a[3] * b[1],  // j
  a[0] * b[3] + a[1] * b[2] - a[2] * b[1] + a[3] * b[0]};
  float angle = cos(2*acos(ans[0]));
  return angle;
};
float getAngle(const float* a, const float* c){
  return acos(getCosine(a,c));
}

void getFeatherLength(float feather_length_txt[], float factor, int numFeathers){
  ifstream file;
  file.open("assets/rightwing.out");
  int num;
  file>>num;
  for(int i=0;i<numFeathers;i++){
    int x;
    float length;
    file>>x>>length;
    feather_length_txt[x] = length/factor;
  }
}

void getFeatherTexture(float ** feather_texture[], int numFeathers){
  ifstream file;
  file.open("assets/rightwingTex.out");
  int num;
  file>>num;
  int x;
  float x1,y1,x2,y2;
  file>>x>>x1>>y1>>x2>>y2;
  for(int i=0;i<numFeathers-1;i++){
    int next_x;
    float next_x1,next_y1,next_x2,next_y2;
    file>>next_x>>next_x1>>next_y1>>next_x2>>next_y2;
    feather_texture[i][0][0] = (x1+next_x1)/2;
    feather_texture[i][0][1] = (y1+next_y1)/2;
    feather_texture[i][1][0] = (next_x1+next_x2)/2;
    feather_texture[i][1][1] = (next_y1+next_y2)/2;
    feather_texture[i][2][0] = (x1+x2)/2;
    feather_texture[i][2][1] = (y1+y2)/2;
    feather_texture[i][3][0] = (next_x2+x2)/2;
    feather_texture[i][3][1] = (next_y2+y2)/2;
    x1=next_x1;
    y1=next_y1;
    x2=next_x2;
    y2=next_y2;
  } 
  feather_texture[numFeathers-1] = feather_texture[numFeathers-2];
  for(int i=0;i<numFeathers-50;i++){
    feather_texture[i][1][0] = feather_texture[i+50][1][0];
    feather_texture[i][1][1] = feather_texture[i+50][1][1];
    feather_texture[i][3][0] = feather_texture[i+50][3][0];
    feather_texture[i][3][1] = feather_texture[i+50][3][1];
  }
  for(int i=numFeathers-50;i<numFeathers;i++){
    feather_texture[i][1][0] = feather_texture[numFeathers-1][1][0];
    feather_texture[i][1][1] = feather_texture[numFeathers-1][1][1];
    feather_texture[i][3][0] = feather_texture[numFeathers-1][3][0];
    feather_texture[i][3][1] = feather_texture[numFeathers-1][3][1];
  }
}

void readSpecifications(float ** arr, string birdSpecifications, int numElements){
  FILE * file = fopen(birdSpecifications.c_str(), "r");
  if( file == NULL ){
    printf("Impossible to open the file !\n");
    return ;
  }
  char lineHeader[256];
  for(int i=0;i<numElements;i++){
     fscanf(file, "m %f # %s\n", arr[i], lineHeader);
  }
}

// bool loadObj(
//   string path,
//   std::vector<QVector3D> & vertices,
//   std::vector<QVector3D> & u_v,
//   std::vector<QVector3D> & normals
// ){
//   std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
//   std::vector< QVector3D > temp_vertices;
//   std::vector< QVector2D > temp_uvs;
//   std::vector< QVector2D > temp_normals;
//   FILE * file = fopen(path.c_str(), "r");
//   if( file == NULL ){
//     printf("Impossible to open the file !\n");
//     return false;
//   }
//   while(1){
//     char lineHeader[128];
//     // read the first word of the line
//     int res = fscanf(file, "%s", lineHeader);
//     if (res == EOF)
//     break; //
//     if ( strcmp( lineHeader, "v" ) == 0 ){
//       float v1,v2,v3;
//       fscanf(file, "%f %f %f\n", &v1, &v2, &v3 );
//       QVector3D vertex(v1,v2,v3);
//       temp_vertices.push_back(vertex);
//     }else if ( strcmp( lineHeader, "vt" ) == 0 ){
//       float x,y;
//       fscanf(file, "%f %f\n", &x, &y );
//       QVector2D uv(x,y);
//       temp_uvs.push_back(uv);
//     }else if ( strcmp( lineHeader, "f" ) == 0 ){
//       std::string vertex1, vertex2, vertex3;
//       unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//       int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
//       if (matches != 9){
//         printf("File can't be read by our simple parser : ( Try exporting with other options\n");
//         return false;
//       }
//       vertexIndices.push_back(vertexIndex[0]);
//       vertexIndices.push_back(vertexIndex[1]);
//       vertexIndices.push_back(vertexIndex[2]);
//       uvIndices    .push_back(uvIndex[0]);
//       uvIndices    .push_back(uvIndex[1]);
//       uvIndices    .push_back(uvIndex[2]);
//       normalIndices.push_back(normalIndex[0]);
//       normalIndices.push_back(normalIndex[1]);
//       normalIndices.push_back(normalIndex[2]);
//     }
//   }
//   for(int i=0;i<vertexIndices.size();i++){
//     unsigned int vertexIndex = vertexIndices[i];
//     vertices.push_back(temp_vertices[vertexIndex-1]);
//   }
//   for(int i=0;i<uvIndices.size();i++){
//     unsigned int uvIndex = uvIndices[i];
//     u_v.push_back(temp_uvs[uvIndex-1]);
//   }
//   for(int i=0;i<normalIndices.size();i++){
//     unsigned int normalIndex = normalIndices[i];
//     normals.push_back(temp_normals[normalIndex-1]);
//   }
// }
