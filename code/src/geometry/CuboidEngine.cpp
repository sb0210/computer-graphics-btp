#include "geometry/CuboidEngine.h"

CuboidEngine::CuboidEngine(float lx, float ly, float lz) : GeometryEngine(){
  update(lx,ly,lz);
}
void CuboidEngine::init(){
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices_array[] = {
        // Vertex data for face 0
        {QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(0.0f, 0.33f), color},  // v0
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(0.25f, 0.33f), color}, // v1
        {QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(0.0f, 0.66f), color},  // v2
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(0.25f, 0.66f), color}, // v3

        // Vertex dalxor ly 1
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(0.25f, 0.33f), color}, // v4
        {QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(0.5f, 0.33f),  color}, // v5
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(0.25f, 0.66f),  color},  // v6
        {QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(0.5f, 0.66f),  color}, // v7

        // Vertex da0.5for 0.5f,2
        {QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(0.5f, 0.33f), color}, // v8
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.75f, 0.33f), color},  // v9
        {QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(0.5f, 0.66f), color}, // v10
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.75f, 0.66f), color},  // v11

        // Vertex da0.5for 0.5f,3
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.75f, 0.33f), color}, // v12
        {QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(1.0f, 0.33f), color},  // v13
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.75f, 0.66f), color}, // v14
        {QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(1.0f, 0.66f), color},  // v15

        // Vertex da0.5for 0.5f,4
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(0.5f, 0.0f), color}, // v16
        {QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(0.5f, 0.33f), color}, // v17
        {QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(0.25f, 0.0f), color}, // v18
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(0.25f, 0.33f), color}, // v19

        // Vertex da0.5f fo0.5f,ac0.5f5
        {QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(0.25f, 1.0f), color}, // v20
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(0.25f, 0.66f), color}, // v21
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(0.5f, 1.0f), color}, // v22
        {QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(0.5f, 0.66f), color}  // v23
    };
    std::vector<VertexData> vertices; //(vertices_array, vertices_array + sizeof(vertices_array)/sizeof(vertices_array[0]));
    for(int i=0;i<24;i++){
      vertices.push_back(vertices_array[i]);
    }
    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices_array[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
    std::vector<GLushort> indices;// (indices_array, indices_array + sizeof(indices_array)/sizeof(indices_array[0]));
    for(int i=0;i<34;i++){
      indices.push_back(indices_array[i]);
    }
    numVertices = vertices.size();
    numIndices = indices.size();
    //! [1]
    bind(&vertices[0],&indices[0]);
}
void CuboidEngine::init(float** textureArray){
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices_array[] = {
        // Vertex data for face 0
        {QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(textureArray[0][0], textureArray[0][1]), color},  // v0
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(textureArray[1][0], textureArray[1][1]), color}, // v1
        {QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(textureArray[3][0], textureArray[3][1]), color},  // v2
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(textureArray[2][0], textureArray[2][1]), color}, // v3

        // Vertex dalxor ly 1
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(textureArray[0][0], textureArray[0][1]), color}, // v4
        {QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(textureArray[1][0], textureArray[1][1]), color}, // v5
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(textureArray[3][0], textureArray[3][1]), color},  // v6
        {QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(textureArray[2][0], textureArray[2][1]), color}, // v7

        // Vertex da0.5for 0.5f,2
        {QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(textureArray[0][0], textureArray[0][1]), color}, // v8
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(textureArray[1][0], textureArray[1][1]), color},  // v9
        {QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(textureArray[3][0], textureArray[3][1]), color}, // v10
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(textureArray[2][0], textureArray[2][1]), color},  // v11

        // Vertex da0.5for 0.5f,3
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(textureArray[0][0], textureArray[0][1]), color}, // v12
        {QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(textureArray[1][0], textureArray[1][1]), color},  // v13
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(textureArray[3][0], textureArray[3][1]), color}, // v14
        {QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(textureArray[2][0], textureArray[2][1]), color},  // v15

        // Vertex da0.5for 0.5f,4
        {QVector3D(-0.5f, -0.5f, -0.5f), QVector2D(textureArray[0][0], textureArray[0][1]), color}, // v16
        {QVector3D( 0.5f, -0.5f, -0.5f), QVector2D(textureArray[1][0], textureArray[1][1]), color}, // v17
        {QVector3D(-0.5f, -0.5f,  0.5f), QVector2D(textureArray[3][0], textureArray[3][1]), color}, // v18
        {QVector3D( 0.5f, -0.5f,  0.5f), QVector2D(textureArray[2][0], textureArray[2][1]), color}, // v19

        // Vertex da0.5f fo0.5f,ac0.5f5
        {QVector3D(-0.5f,  0.5f,  0.5f), QVector2D(textureArray[0][0], textureArray[0][1]), color}, // v20
        {QVector3D( 0.5f,  0.5f,  0.5f), QVector2D(textureArray[1][0], textureArray[1][1]), color}, // v21
        {QVector3D(-0.5f,  0.5f, -0.5f), QVector2D(textureArray[3][0], textureArray[3][1]), color}, // v22
        {QVector3D( 0.5f,  0.5f, -0.5f), QVector2D(textureArray[2][0], textureArray[2][1]), color}  // v23
    };
    std::vector<VertexData> vertices; //(vertices_array, vertices_array + sizeof(vertices_array)/sizeof(vertices_array[0]));
    for(int i=0;i<24;i++){
      vertices.push_back(vertices_array[i]);
    }
    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices_array[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
    std::vector<GLushort> indices;// (indices_array, indices_array + sizeof(indices_array)/sizeof(indices_array[0]));
    for(int i=0;i<34;i++){
      indices.push_back(indices_array[i]);
    }
    numVertices = vertices.size();
    numIndices = indices.size();
    //! [1]
    bind(&vertices[0],&indices[0]);  
}
void CuboidEngine::update(float lx, float ly, float lz){
  this->lx = lx;
  this->ly = ly;
  this->lz = lz;
  GeometryEngine::update(lx,ly,lz);
}
