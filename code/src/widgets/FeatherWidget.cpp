/* include "license.txt" */

#include "widgets/FeatherWidget.h"

FeatherWidget::FeatherWidget(QWidget *parent):
  QWidget(parent),painter(this)
  {
  pointActive = false;
  minimumDistance = 1000;
  size = 6;

  for(int i=0;i<size;i++){
    float theta = 2*3.1415/size;
    points[i] = QPointF(10*cos(theta*i),10*sin(theta*i));
  }

  pixmap.load("assets/aerofoil.png");

  int height = pixmap.height();
  int width = pixmap.width();
  imageCorner = center - QPointF(width/2,height/2);

  center.setX(QWidget::size().width()/2);
  center.setY(QWidget::size().height()/2);
}

FeatherWidget::~FeatherWidget(){
}

void FeatherWidget::mousePressEvent(QMouseEvent *e){

  mouseClickPosition = QPointF(e->localPos());
  QVector2D point1 = QVector2D(mouseClickPosition);
  float minDistance = 10;
  for(int j=0;j<size;j++){
    QVector2D point2 = QVector2D(center + points[j]);
    float distance = point1.distanceToPoint(point2);
    if(distance<minDistance && distance< minimumDistance){
      currentElement = &points[j];
      currentElementIndex = j;
      minDistance = distance;
      pointActive = true;
    }
  }
  update();
}

void FeatherWidget::mouseMoveEvent(QMouseEvent *e){
  if(pointActive){
    QPointF mousePosition = QPointF(e->localPos());
    *currentElement = mousePosition - center;
    update();
  }
}

void FeatherWidget::mouseReleaseEvent(QMouseEvent *e){
  if(pointActive){
    QPointF mousePosition = QPointF(e->localPos());
    *currentElement = mousePosition - center;
    pointActive = false;
    update();
  }
}

void FeatherWidget::resizeEvent(QResizeEvent* e){
  center.setX(e->size().width()/2);
  center.setY(e->size().height()/2);
  int height = pixmap.height();
  int width = pixmap.width();
  imageCorner = center - QPointF(width/2,height/2);
}

void FeatherWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);


    int height = pixmap.height();
    int width = pixmap.width();
    QPointF corner = center - QPointF(width/2,height/2);
    painter.drawPixmap(corner,pixmap);
    QPen pen1;
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidth(1);
    pen1.setBrush(Qt::blue);

    QPen pen2;
    pen2.setStyle(Qt::SolidLine);
    pen2.setWidth(1);
    pen2.setBrush(Qt::red);

    QPen pen3;
    pen3.setStyle(Qt::SolidLine);
    pen3.setWidth(2);
    pen3.setBrush(Qt::green);

    for(int i=0;i<size;i++){
      if(i==0){
        painter.setBrush(Qt::green);
        painter.setPen(pen1);
      }
      else if(i%3==0){
        painter.setBrush(Qt::blue);
        painter.setPen(pen1);
      }
      else {
        painter.setBrush(Qt::red);
        painter.setPen(pen2);
      }
      if(pointActive){
        if(currentElement==&points[i])
          painter.drawEllipse(center + points[i],6,6);
        else
          painter.drawEllipse(center + points[i],4,4);
      }
      else
        painter.drawEllipse(center + points[i],4,4);
    }
    if(pointActive){
      string s = to_string(currentElement->x()) +" "+ to_string(currentElement->y());
      painter.drawText(center+QPointF(200,200),QString(s.c_str()));
      painter.drawText(center+QPointF(200,250),QString(to_string(currentElementIndex).c_str()));
    }


    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen3);
    QPainterPath path(center + points[0]);
    for(int i=1;i<=size;i=i+3){
      path.cubicTo(center + points[i%size],center + points[(i+1)%size],center + points[(i+2)%size]);
    }
    painter.drawPath(path);

}

void FeatherWidget::saveBezierCoordinates(string filename){
    ofstream file;
    file.open(filename.c_str());
    QPainterPath path(points[0]);
    int p=0;
    float length[size/3];
    for(int j=1;j<=size;j=j+3){
      length[p] = path.length();
      path.cubicTo(points[j%size],points[(j+1)%size],points[(j+2)%size]);
      p++;
    }

    float start = path.percentAtLength(length[0]);
    float end = path.percentAtLength(length[1]);

    int partitions = 10;
    float diff = (end-start)/partitions;
    file<<partitions+1<<endl;
    float max = points[3].y();
    float min = points[0].y();
    float factor = 1/abs(max - min);
    file<<factor*points[0].x()<<" "<<factor*(points[0].y()-min)<<endl;


    for(int i=1;i<=partitions;i++){
      float t = start + i*diff;
      QPointF point = path.pointAtPercent(t);
      file<<factor*point.x()<<" "<<factor*(point.y()-min)<<endl;
    }
    diff = (end-1)/partitions;
    file<<factor*points[0].x()<<" "<<factor*(points[0].y()-min)<<endl;
    for(float i=1;i<=partitions;i++){
      float t = 1 + i*diff;
      QPointF point = path.pointAtPercent(t);
      file<<factor*point.x()<<" "<<factor*(point.y()-min)<<endl;
    }
}

void FeatherWidget::keyPressEvent(QKeyEvent* e){
  if(e->key()==Qt::Key_S){
    saveCoordinates("assets/Curve/bezier_coordinates.txt");
  }
  else if(e->key()==Qt::Key_L){
    loadCoordinates("assets/Curve/bezier_coordinates.txt");
  }
  else if(e->key()==Qt::Key_C){
    saveBezierCoordinates("assets/Curve/bezier.txt");
  }
}

void FeatherWidget::saveCoordinates(string filename){
  ofstream myfile;
  myfile.open(filename.c_str());
  myfile<<size<<endl;
  for(int i=0;i<size;i++){
    myfile<<points[i].x()<<" "<<points[i].y()<<"\t";
  }
  myfile<<endl;
  myfile.close();
}

void FeatherWidget::loadCoordinates(string filename){
  ifstream myfile;
  myfile.open(filename.c_str());
  myfile>>size;
  for(int i=0;i<size;i++){
    myfile>>points[i].rx()>>points[i].ry();
  }
  myfile.close();
  update();
}

struct ySort{
  bool operator()(QPointF point1, QPointF point2){
    return point1.y()<point2.y();
  }
};

class VertexData
{
public:
    QVector3D position;
    QVector2D texCoord;
    QVector3D color;
    VertexData(){}
    VertexData(QVector3D position, QVector2D texCoord, QVector3D color){
      this->position = position;
      this->texCoord = texCoord;
      this->color = color;
    }
};

