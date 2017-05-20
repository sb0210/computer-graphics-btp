/* #include "license.txt" */

#include "geometry/GeometryEngine.h"

#include <QVector2D>
#include <QVector3D>
#include <QtMath>
#include <iostream>
#include <QDebug>
#define PI 3.1416
//! [0]
GeometryEngine::GeometryEngine(): indexBuf(QOpenGLBuffer::IndexBuffer),    calliberationMatrix(1,0,0,0,
                        0,1,0,0,
                        0,0,1,0,
                        0,0,0,1){
    initializeOpenGLFunctions();
    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    primitive = GL_TRIANGLE_STRIP;
    type = SPHERE;
    color = QVector3D(1,1,1);
    is_texture = false;
}

GeometryEngine::~GeometryEngine(){
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::setColor(QVector3D _color){
  color = _color;
}



void GeometryEngine::setTexture(string path){
  texture = new QOpenGLTexture(QImage(path.c_str()).mirrored());

  // Set nearest filtering mode for texture minification
  texture->setMinificationFilter(QOpenGLTexture::Nearest);

  // Set bilinear filtering mode for texture magnification
  texture->setMagnificationFilter(QOpenGLTexture::Linear);

  // Wrap texture coordinates by repeating
  // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
  texture->setWrapMode(QOpenGLTexture::Repeat);
  is_texture = true;
}
void GeometryEngine::init(){}
void GeometryEngine::init(float,float,float, float){}
void GeometryEngine::init(float**){}
void GeometryEngine::init(float, QVector2D[4]){}
void GeometryEngine::setPrimitive(unsigned int primitive){
  this->primitive = primitive;
}
void GeometryEngine::setCalliberation(QMatrix4x4 matrix){
  calliberationMatrix = matrix;
}
void GeometryEngine::setCalliberation(float pos[], float R[], float scaling[]){
  QMatrix4x4 cTranslationMatrix, cRotationMatrix, cScalingMatrix;
  cTranslationMatrix.setToIdentity();
  cTranslationMatrix.translate(pos[0],pos[1],pos[2]);
  cRotationMatrix.setToIdentity();
  QMatrix4x4 mat(R[0],R[1],R[2],0,
                  R[4],R[5],R[6],0,
                  R[8],R[9],R[10],0,
                  0,0,0,1);
  cRotationMatrix = mat*cRotationMatrix;
  cScalingMatrix.setToIdentity();
  cScalingMatrix.scale(scaling[0],scaling[1],scaling[2]);
  setCalliberation(cTranslationMatrix*cRotationMatrix*cScalingMatrix);
}
void Geometry::setCalliberation(float pos[], float scaling[]){
  float R[12] = {1,0,0,0,
                 0,1,0,0,
                 0,0,1,0};
  setCalliberation(pos,R,scaling);
}
void GeometryEngine::setPosition(float pos[]){
  float R[16] = {1,0,0,0,
                 0,1,0,0,
                 0,0,1,0,
                 0,0,0,1};
  float scale[3] = {1,1,1};               
  setCalliberation(pos,R,scale);               
}

void GeometryEngine::setPosition(QVector3D position){
  float pos[3] = {position.x(), position.y(), position.z()};
  float R[16] = {1,0,0,0,
                 0,1,0,0,
                 0,0,1,0,
                 0,0,0,1};
  float scale[3] = {1,1,1};               
  setCalliberation(pos,R,scale);               
}

void GeometryEngine::rotate(QQuaternion rotation){
  rotationMatrix.setToIdentity();
  rotationMatrix.rotate(rotation);
}
void GeometryEngine::update(float, float){}

void GeometryEngine::update(const float pos[], const float R[]){
  translationMatrix.setToIdentity();
  translationMatrix.translate(pos[0],pos[1],pos[2]);
  rotationMatrix.setToIdentity();
  QMatrix4x4 mat(R[0],R[1],R[2],0,
                  R[4],R[5],R[6],0,
                  R[8],R[9],R[10],0,
                  0,0,0,1);
  rotationMatrix = mat*rotationMatrix;
  }

void GeometryEngine::update(const float pos[], const float R[], float scaling[]){
  translationMatrix.setToIdentity();
  translationMatrix.translate(pos[0],pos[1],pos[2]);
  rotationMatrix.setToIdentity();
  QMatrix4x4 mat(R[0],R[1],R[2],0,
                  R[4],R[5],R[6],0,
                  R[8],R[9],R[10],0,
                  0,0,0,1);
  rotationMatrix = mat*rotationMatrix;
  scalingMatrix.setToIdentity();
  scalingMatrix.scale(scaling[0],scaling[1],scaling[2]);
  }
void GeometryEngine::update(float lx, float ly, float lz){
  float pos[3] = {0,0,0};
  float rotation[12] = {1,0,0,0,
                        0,1,0,0,
                        0,0,1,0};
  float scale[3] = {lx,ly,lz};
  update(pos, rotation, scale);
}
void GeometryEngine::draw(QOpenGLShaderProgram *program){
  // Tell OpenGL which VBOs to use
  arrayBuf.bind();
  indexBuf.bind();

  // Offset for position
  quintptr offset = 0;

  // Tell OpenGL programmable pipeline how to locate vertex position data
  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

  // Offset for texture coordinate
  offset += sizeof(QVector3D);

  // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
  int texcoordLocation = program->attributeLocation("a_texcoord");
  program->enableAttributeArray(texcoordLocation);
  program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

  offset += sizeof(QVector2D);
  // Tell OpenGL programmable pipeline how to locate vertex color data
  int colorLocation = program->attributeLocation("a_color");
  program->enableAttributeArray(colorLocation);
  program->setAttributeBuffer(colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

  program->setUniformValue("ind_matrix", translationMatrix*rotationMatrix*scalingMatrix*calliberationMatrix);
  if(is_texture){
    texture->bind();
  }

  if(is_texture){
    program->setUniformValue("is_texture",1.0f);
  }
  else program->setUniformValue("is_texture",-1.0f);
  program->setUniformValue("texture", 0);

  // Draw cube geometry using indices from VBO 1
  glDrawElements(primitive, numIndices, GL_UNSIGNED_SHORT, 0);
}
void GeometryEngine::bind(const void* vertices, const void* indices){
  // Transfer vertex data to VBO 0
  arrayBuf.bind();
  arrayBuf.allocate(vertices, numVertices * sizeof(VertexData));

  // Transfer index data to VBO 1
  indexBuf.bind();
  indexBuf.allocate(indices, numIndices * sizeof(GLushort));
}
