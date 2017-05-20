/* #include "license.txt" */

#ifndef FEATHERWIDGET_H
#define FEATHERWIDGET_H

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

class FeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FeatherWidget(QWidget *parent = 0);
    ~FeatherWidget();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent* e) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent* e) Q_DECL_OVERRIDE;

    void saveCoordinates(string filename);
    void loadCoordinates(string filename);
    void saveBezierCoordinates(string filename);

private:
    QPointF points[100];
    int size;
    QPointF* currentElement;
    int currentElementIndex;
    bool pointActive;
    QPainter painter;

    QPixmap pixmap;
    float minimumDistance;
    QPointF center;
    int numPoints;
    QPointF imageCorner;

    QPointF mouseClickPosition;

};

#endif // FEATHERWIDGET_H
