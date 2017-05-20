#include "geometry/OBJEngine.h"

OBJEngine::OBJEngine(string path, float lx, float ly, float lz){
  this->path = path;
  cout<<path<<endl;
  init();
  update(lx, ly, lz);
}
void OBJEngine::init(){

  std::vector< GLushort > indices;//,uvIndices;//, normalIndices;
  std::vector< VertexData> vertexData;
  std::vector< QVector3D > vertices;
  std::vector< QVector2D > uvs;
  std::vector< QVector3D > temp_normals;
  std::vector< QVector3D > colors;
  FILE * file = fopen(path.c_str(), "r");
  if( file == NULL ){
    printf("Impossible to open the file !\n");
    return ;
  }
  while(1){
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break; //
    if ( strcmp( lineHeader, "v" ) == 0 ){
      float v1,v2,v3;
      fscanf(file, "%f %f %f\n",  &v1,&v2, &v3 );
      QVector3D vertex(v1,v2,v3);
      QVector3D vertex_color(1,1,1);
      vertices.push_back(vertex);
      colors.push_back(vertex_color);
    }else if ( strcmp( lineHeader, "vt" ) == 0 ){
      float x,y;
      fscanf(file, "%f %f\n", &x, &y );
      QVector2D uv(x,y);
      uvs.push_back(uv);
    }else if ( strcmp( lineHeader, "f" ) == 0 ){
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3];
      fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
      indices.push_back(vertexIndex[0]-1);
      indices.push_back(vertexIndex[1]-1);
      indices.push_back(vertexIndex[2]-1);
    }
  }
  for(unsigned int i=0;i<vertices.size();i++){
    vertexData.push_back({vertices[i],uvs[i],colors[i]});
  }
  numVertices = vertexData.size();
  numIndices = indices.size();
  bind(&vertexData[0],&indices[0]);
  setPrimitive(GL_TRIANGLES);
  cout<<numIndices<<" "<<numVertices<<endl;

}
