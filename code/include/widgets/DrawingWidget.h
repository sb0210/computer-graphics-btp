/* #include "license.txt" */

#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QVector2D>
#include <QVector3D>
#include <QPainter>
#include <QPointF>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QString>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

class DrawingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = 0);
    ~DrawingWidget();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* e) Q_DECL_OVERRIDE;

    void saveCoordinates(string filename);
    void loadCoordinates(string filename);
    void get3D(string filename);
    void printDimensions(string filename);
    void getTexture();

private:
    enum Parts {TAIL=3, RIGHTWING=1, LEFTWING = 2,TORSO= 0 };
    QPointF points[4][100];
    int size[4];
    Parts activeGroup;
    QPointF* currentElement;
    int currentElementIndex;
    QPointF* oppositeElement;
    bool pointActive;
    bool groupActive;
    bool showAll;
    QPainter painter;

    QPixmap pixmap;
    float minimumDistance;
    QPointF center;
    int numPoints;
    float radiusX, radiusY;
    QPointF imageCorner;

    QPointF mouseClickPosition;

    float length,
        wingspan,
        trunk_width,
        wing_width,
        bird_center,
        wing_offset_x,
        wing_offset_y,
        factor,
        weight,
        timePeriod;
};

#endif // DRAWINGWIDGET_H
