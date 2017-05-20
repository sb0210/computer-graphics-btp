/* #include "license.txt" */

#include "widgets/MainWidget.h"

#include <QMouseEvent>
#include <QtMath>
#include <math.h>
#include <QDebug>
dWorldID World::world;
dSpaceID World::space;
// MyBird* World::bird;
Bird* World::bird;
dJointGroupID World::contactgroup;
GeometryEngine* World::box;
BodyPart* World::plane;

float t = 0;
MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    world(0),
    geometries(0),
    texture(0),
    angularSpeed(0)
{
  eye = QVector3D(0,0,30);
  left = -10;right = 10;
  bottom = -10;top = 10;
  near_plane = 10;
  far_plane = 50;
  scaleFactor = 1;

  translation_matrix.setToIdentity();
  translation_matrix.translate(-1*eye);
  perspective_projection.setToIdentity();
  perspective_projection.frustum(left, right, bottom, top, near_plane, far_plane);
  orthographic_projection.setToIdentity();
  orthographic_projection.ortho(left, right, bottom, top, near_plane, far_plane);
  projection = perspective_projection;
  
  forwardForce= 0;
  upwardThrust = 0;
  torque = 0;

}

MainWidget::~MainWidget(){
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e){
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseMoveEvent(QMouseEvent* e){
  // Mouse release position - mouse press position
  QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

  // Rotation axis is perpendicular to the mouse position difference
  // vector
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

  // Accelerate angular speed relative to the length of the mouse sweep
  qreal acc = diff.length()/5;

  // Calculate new rotation axis as weighted sum
  rotationAxis = n;

  if(e->modifiers() & Qt::ControlModifier){
    if(rotationAxis.x()>=rotationAxis.y() && rotationAxis.x()>=rotationAxis.z()){
      rotationAxis.setY(0);
      rotationAxis.setZ(0);
    }
    else if(rotationAxis.y()>=rotationAxis.z() && rotationAxis.y()>=rotationAxis.x()){
      rotationAxis.setX(0);
      rotationAxis.setZ(0);
    }
    else if(rotationAxis.z()>=rotationAxis.y() && rotationAxis.z()>=rotationAxis.x()){
      rotationAxis.setX(0);
      rotationAxis.setY(0);
    }
  }
  rotation = tempRotation* old_rotation;

  // Increase angular speed
  angularSpeed = acc;
}
void MainWidget::mouseReleaseEvent(QMouseEvent *){
  // rotation =  rotation;
  old_rotation = rotation;
  tempRotation = QQuaternion::fromAxisAndAngle(rotationAxis, 0);
  angularSpeed = 1;
}

void MainWidget::wheelEvent(QWheelEvent* e){
  float numDegrees = e->delta() / 8;
  float tempScaleFactor = numDegrees / 100;

  if (e->orientation() == Qt::Horizontal) {
  } else {
    scaleFactor += tempScaleFactor;
    if(scaleFactor<0.1)
      scaleFactor = 0.1;
  }
  e->accept();
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        tempRotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed);
        // rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
        // Request an update
    }
    world->simLoop();
    update();

}
//! [1]
void MainWidget::keyPressEvent(QKeyEvent* e){
  if( e->key() == Qt::Key_P){
    projection= (projection==perspective_projection)? orthographic_projection:perspective_projection;
  }
  if(e->key() == Qt::Key_U){
    cin>>forwardForce>>upwardThrust>>torque;
  }
}

void MainWidget::initializeGL()
{

    initializeOpenGLFunctions();
    world->init();
    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
//! [2]

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "src/shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, "src/shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage("assets/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]


void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();


    QMatrix4x4 matrix;
    matrix.scale(scaleFactor);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection*translation_matrix*matrix);
    world->plane->draw(&program);

    QMatrix4x4 m;
    m.rotate(t,QVector3D(0,1,0));
    m.translate(14 ,0,0);
    m.rotate(-60,QVector3D(1,0,0));

    m.scale(scaleFactor);
    matrix.rotate(rotation);
    program.setUniformValue("mvp_matrix", projection*translation_matrix*matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);


    world->applyExternalForce(0,upwardThrust,forwardForce);
    world->applyExternalTorque(torque,0,0);

    world->bird->draw(&program);
    t+=0.7;
}
