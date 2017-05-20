/* #include "license.txt" */

#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include "geometry/GeometryEngine.h"
#include "simulation/World.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class GeometryEngine;

class DisplayWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent* e) Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent* e) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;

    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void initShaders();
    void initTextures();

private:
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    World* world;
    GeometryEngine *geometries;

    QOpenGLTexture *texture;

    QMatrix4x4 perspective_projection;
    QMatrix4x4 orthographic_projection;
    QMatrix4x4 projection;

    QMatrix4x4 translation_matrix;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;

    float scaleFactor;
    qreal angularSpeed;
    QQuaternion rotation,tempRotation;

    QVector3D eye;
    float left,right,bottom,top;
    float near_plane;
    float far_plane;

};

#endif // DISPLAYWIDGET_H
