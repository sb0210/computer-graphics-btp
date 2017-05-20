/* #include "license.txt" */

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QPointF>
#include <QPainterPath>
#include <vector>
#include <QVector2D>
#include <QVector3D>
#include <stack>
#include <fstream>

#include "helpers/Basics.h"

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D color;
};

class GeometryEngine : public QOpenGLFunctions{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void draw(QOpenGLShaderProgram *program);
    void rotate(QQuaternion);
    void bind(const void* vertices, const void* indices);
    void setColor(QVector3D color);
    void setPrimitive(unsigned int primitive);
    void setCalliberation(float pos[], float R[], float scaling[]);
    void setCalliberation(QMatrix4x4 matrix);
    void setCalliberation(float pos[], float scaling[]);
    void setTexture(string path);
    void setPosition(float pos[]);
    void setPosition(QVector3D position);
    virtual void init();
    virtual void init(float**);
    virtual void init(float, float, float, float);
    virtual void init(float, QVector2D[4]);
    virtual void update(float, float);
    virtual void update(float, float, float);
    virtual void update(const float* position,const float* rotation, float* scaling);
    virtual void update(const float* position,const float* rotation);
    enum types{
      HEMISPHERE=0,
      SPHERE
    };
    int type;
protected:
    int numVertices;
    int numIndices;
    QVector3D color;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLTexture *texture;
    bool is_texture;
    QMatrix4x4 calliberationMatrix;
    QMatrix4x4 scalingMatrix;
    QMatrix4x4 rotationMatrix;
    QMatrix4x4 translationMatrix;
    unsigned int primitive;

};

#endif // GEOMETRYENGINE_H


