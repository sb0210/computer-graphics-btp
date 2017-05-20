/* #include "license.txt" */

#include "widgets/DrawingWidget.h"

DrawingWidget::DrawingWidget(QWidget *parent):
  QWidget(parent),painter(this)
  {
  activeGroup = TORSO;
  pointActive = false;
  minimumDistance = 1000;
  size[0] = 24;size[1] = 24;size[2] = 24;size[3] = 24;
  radiusX = 60; radiusY = 100;
  showAll = true;

  for(int i=0;i<size[0];i++){
    float theta = 2*3.1415/size[0];
    points[0][i] = QPointF(radiusX*cos(theta*i),radiusY*sin(theta*i));
  }
  for(int i=0;i<size[1];i++){
    float theta = 2*3.1415/size[0];
    points[1][i] = QPointF(100,0) + QPointF(radiusX*cos(theta*i),radiusY*sin(theta*i));
  }
  for(int i=0;i<size[2];i++){
    float theta = 2*3.1415/size[0];
    points[2][i] = QPointF(-100,0) + QPointF(radiusX*cos(3.1415-theta*i),radiusY*sin(3.1415-theta*i));
  }
  for(int i=0;i<size[3];i++){
    float theta = 2*3.1415/size[0];
    points[3][i] = QPointF(0,-100) + QPointF(radiusX*cos(theta*i),radiusY*sin(theta*i));
  }

  pixmap.load("assets/parrot.png");

  int height = pixmap.height();
  int width = pixmap.width();
  imageCorner = center - QPointF(width/2,height/2);

  center.setX(QWidget::size().width()/2);
  center.setY(QWidget::size().height()/2);
  length = 18;
  wingspan = 25;
  trunk_width = 3;
  wing_width = 20;
  wing_offset_x = 3; 
  wing_offset_y = 6; 
  factor = 40 ;
  weight = 0.030;
  timePeriod = 1.5;
}

DrawingWidget::~DrawingWidget(){
}

void DrawingWidget::mousePressEvent(QMouseEvent *e){

  mouseClickPosition = QPointF(e->localPos());
  QVector2D point1 = QVector2D(mouseClickPosition);
  float minDistance = 10;
  int i=activeGroup;
  for(int j=0;j<size[i];j++){
    QVector2D point2 = QVector2D(center + points[i][j]);
    float distance = point1.distanceToPoint(point2);
    if(distance<minDistance && distance< minimumDistance){
      if(i==0 || i==3){
        currentElement = &points[i][j];
        int oppIndex = (size[i]/2 - j + size[i])%size[i];
        oppositeElement = &points[i][oppIndex];
        currentElementIndex = j;
      }
      else if(i==1||i==2){
        currentElement = &points[i][j];
        oppositeElement = &points[3-i][j];
        currentElementIndex = j;
      }
      minDistance = distance;
      pointActive = true;
    }
  }
  update();
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *e){
  if(pointActive){
    QPointF mousePosition = QPointF(e->localPos());
    *currentElement = mousePosition - center;
    if(oppositeElement!=currentElement){
      oppositeElement->setX(-currentElement->x());
      oppositeElement->setY(currentElement->y());
    }
    update();
  }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *e){
  if(pointActive){
    QPointF mousePosition = QPointF(e->localPos());
    *currentElement = mousePosition - center;
    if(oppositeElement!=currentElement){
      oppositeElement->setX(-currentElement->x());
      oppositeElement->setY(currentElement->y());
    }
    pointActive = false;
    update();
  }
}

void DrawingWidget::resizeEvent(QResizeEvent* e){
  center.setX(e->size().width()/2);
  center.setY(e->size().height()/2);
  int height = pixmap.height();
  int width = pixmap.width();
  imageCorner = center - QPointF(width/2,height/2);
}

void DrawingWidget::paintEvent(QPaintEvent *){
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

    for(int k=0;k<4;k++){
      if(!showAll)k=activeGroup;
      for(int i=0;i<size[k];i++){
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
          if(currentElement==&points[k][i])
            painter.drawEllipse(center + points[k][i],6,6);
          else
            painter.drawEllipse(center + points[k][i],4,4);
        }
        else
          painter.drawEllipse(center + points[k][i],4,4);
      }
      if(pointActive){
        string s = to_string(currentElement->x()) +" "+ to_string(currentElement->y());
        painter.drawText(center+QPointF(200,200),QString(s.c_str()));
        painter.drawText(center+QPointF(200,250),QString(to_string(currentElementIndex).c_str()));
      }


      painter.setBrush(Qt::NoBrush);
      painter.setPen(pen3);
      QPainterPath path(center + points[k][0]);
      for(int i=1;i<=size[k];i=i+3){
        path.cubicTo(center + points[k][i%size[k]],center + points[k][(i+1)%size[k]],center + points[k][(i+2)%size[k]]);
      }
      painter.drawPath(path);
      if(!showAll)break;
    }
}

void DrawingWidget::keyPressEvent(QKeyEvent* e){
  if(e->key()==Qt::Key_S){
    saveCoordinates("assets/coordinates.txt");
  }
  else if(e->key()==Qt::Key_L){
    loadCoordinates("assets/coordinates.txt");
  }
  else if(e->key()==Qt::Key_C){
    get3D("assets/coordinates.txt");
  }
  else if(e->key()==Qt::Key_T){
    showAll=!showAll;
    update();
  }
  else if(e->key()==Qt::Key_1){
    activeGroup = TAIL;
    update();
  }
  else if(e->key()==Qt::Key_2){
    activeGroup = RIGHTWING;
    update();
  }
  else if(e->key()==Qt::Key_3){
    activeGroup = LEFTWING;
    update();
  }
  else if(e->key()==Qt::Key_4){
    activeGroup = TORSO;
    update();
  }
}

void DrawingWidget::saveCoordinates(string filename){
  ofstream myfile;
  myfile.open(filename.c_str());
  for(int k=0;k<4;k++){
    myfile<<size[k]<<endl;
    for(int i=0;i<size[k];i++){
      myfile<<points[k][i].x()<<" "<<points[k][i].y()<<"\t";
    }
    myfile<<endl;
  }
  myfile.close();
}

void DrawingWidget::loadCoordinates(string filename){
  ifstream myfile;
  myfile.open(filename.c_str());
  for(int k=0;k<4;k++){
    myfile>>size[k];
    for(int i=0;i<size[k];i++){
      myfile>>points[k][i].rx()>>points[k][i].ry();
    }
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

void DrawingWidget::printDimensions(string filename){

  ofstream asset_dimension;
  asset_dimension.open(filename);
  asset_dimension<<"m "<<length<<" # length"<<endl;
  asset_dimension<<"m "<<wingspan<<" # Winspan"<<endl;
  asset_dimension<<"m "<<trunk_width<<" # Trunk_Width"<<endl;
  asset_dimension<<"m "<<wing_width<<" # Wing_width"<<endl;
  asset_dimension<<"m "<<bird_center<<" # Bird_Center"<<endl;
  asset_dimension<<"m "<<wing_offset_x<<" # Wing_offset_x"<<endl;
  asset_dimension<<"m "<<wing_offset_y<<" # Wing_offset_y"<<endl;
  asset_dimension<<"m "<<factor<<" # factor"<<endl;
  asset_dimension<<"m "<<weight<<" # Weight"<<endl;
  asset_dimension<<"m "<<timePeriod<<" # Time_period"<<endl;
} 

void DrawingWidget::getTexture(){

}

QVector2D getGlobalTex(float x, float y){
  return QVector2D((938/2.0+x)/938,(481/2.0-y)/481);
}

void DrawingWidget::get3D(string filename){
  ifstream myFile;
  myFile.open(filename.c_str());
  ofstream wholeFigure, wholeFigureObj;
  wholeFigure.open("assets/wholeFigure.txt");
  wholeFigureObj.open("assets/wholeFigure.obj");
  int k=4;
  int _size[k];
  vector<QPointF> _points[k];
  for(int i=0;i<k;i++){
    myFile>>_size[i];
    for(int j=0;j<_size[i];j++){
      float x,y;myFile>>x>>y;
      _points[i].push_back(QPointF(x,y));
    }
  }
  vector<QPointF> samples[k];

  float _length[8] = {0};
  for(int i=0;i<k;i++){
    QPainterPath path(_points[i][0]);
    int p=0;
    for(int j=1;j<=_size[i];j=j+3){
      _length[p] = path.length();
      path.cubicTo(_points[i][j%_size[i]],_points[i][(j+1)%_size[i]],_points[i][(j+2)%_size[i]]);
      p++;
    }
    if(i==TORSO){
      float mini1 = path.percentAtLength(_length[2]);
      float mini2 = path.percentAtLength(_length[6]);
      for(float pp=0;pp<=30;pp++){
        float x = mini1 + (pp/30.0)*(mini2-mini1);
        QPointF p = path.pointAtPercent(x);
        samples[i].push_back(p);
      }
      vector<QPointF> copy_sample = samples[i];
      sort(copy_sample.begin(), copy_sample.end(), ySort());
      float minY = copy_sample[0].y();
      float maxY = copy_sample[copy_sample.size()-1].y();
      float diff = maxY - minY;
      bird_center = (minY + maxY)/2;

      length = diff;
      vector<VertexData> vertices;
      vector<int> indices;
      trunk_width = 0;
      for(unsigned int j=0;j<samples[i].size()-1;j++){
        float divisions = 50;
        float theta = 2*3.1415/divisions;

        float height1 = samples[i][j].y();
        float radius1 = abs(samples[i][j].x());
        float height2 = samples[i][j+1].y();
        float radius2 = abs(samples[i][j+1].x());
        if(2*radius1>trunk_width){
          trunk_width = 2*radius1;
        }

        float x[4],y[4],z[4];
        VertexData v[4];
        QVector3D my_points[4];
        QVector2D texCoord[4];
        for(int l=0;l<divisions;l++){
          x[0] = radius1*cos(l*theta);
          y[0] = radius1*sin(l*theta);
          z[0] = height1;
          texCoord[0] = getGlobalTex(x[0],y[0]);
          x[1] = radius2*cos(l*theta);
          y[1] = radius2*sin(l*theta);
          z[1] = height2;
          texCoord[1] = getGlobalTex(x[1],y[1]);

          x[2] = radius2*cos((l+1)*theta);
          y[2] = radius2*sin((l+1)*theta);
          z[2] = height2;
          texCoord[2] = getGlobalTex(x[2],y[2]);

          x[3] = radius1*cos((l+1)*theta);
          y[3] = radius1*sin((l+1)*theta);
          z[3] = height1;
          texCoord[3] = getGlobalTex(x[3],y[3]);

          for(int i=0;i<4;i++){
            my_points[i] = {x[i],y[i],z[i]};
            v[i] = VertexData(my_points[i],texCoord[i],QVector3D(1,1,1));
          }

          vertices.push_back(v[0]);
          vertices.push_back(v[1]);
          vertices.push_back(v[2]);
          vertices.push_back(v[3]);
          indices.push_back(1+ j*divisions*4 + 4*l+1);
          indices.push_back(1+ j*divisions*4 + 4*l);
          indices.push_back(1+ j*divisions*4 + 4*l+2);
          indices.push_back(1+ j*divisions*4 + 4*l);
          indices.push_back(1+ j*divisions*4 + 4*l+2);
          indices.push_back(1+ j*divisions*4 + 4*l+3);
        }
      }

      ofstream output;
      output.open("assets/torso.txt");
      for(unsigned int i=0;i<vertices.size();i++){
        output<<"v "<<vertices[i].position.x()<<" "<<vertices[i].position.y()<<" "<<vertices[i].position.z()<<endl;
      }
      for(unsigned int i=0;i<vertices.size();i++){
        output<<"vt "<<vertices[i].texCoord.x()<<" "<<vertices[i].texCoord.y()<<endl;
      }

      for(unsigned int i=0;i<indices.size()-2;i=i+3){
        output<<"f "<<indices[i]<<" ";
        output<<indices[i+1]<<" ";
        output<<indices[i+2]<<endl;
      }
      cout<<vertices.size()<<" "<<indices.size()<<endl;
    }
    else if(i==RIGHTWING){
      int numFeathers = 60;
      float wing__lengths[numFeathers];
      float t1_start = path.percentAtLength(_length[6]);
      float t1_end = path.percentAtLength(_length[7]);
      float t2_start = path.percentAtLength(_length[5]);
      float t2_end = path.percentAtLength(_length[0]);

      QVector2D wing_start_position = QVector2D(path.pointAtPercent(t1_start));
      QVector2D wing_end_position = QVector2D(path.pointAtPercent(t1_end));
      wingspan = 2*(wing_start_position.distanceToPoint(wing_end_position)+trunk_width);
      wing_offset_x = wing_start_position.x(); 
      wing_offset_y = wing_start_position.y();
      vector<QVector2D> textures;

      for(int i=0;i<numFeathers;i++){
        float t1 = t1_start + (t1_end-t1_start)*i*1.0/numFeathers;
        float t2 = t2_start + (t2_end-t2_start)*i*1.0/numFeathers;
        t1 = t1 -0.0001;
        t2 = t2 -0.0002;
        QVector2D p1 = QVector2D(path.pointAtPercent(t1));
        QVector2D p2 = QVector2D(path.pointAtPercent(t2));
        wing__lengths[i] = p1.distanceToPoint(p2);
        textures.push_back(QVector2D(938/2.0+p1.x(),481/2.0-p1.y()));
        textures.push_back(QVector2D(938/2.0+p2.x(),481/2.0-p2.y()));
     }
      ofstream rightWingOutput;
      rightWingOutput.open("assets/rightwing.out");
      rightWingOutput<<numFeathers<<endl;
      for(int i=0;i<numFeathers;i++){
        rightWingOutput<<i<<" "<<wing__lengths[i]<<endl;
      }
      cout<<pixmap.width()<<" "<<pixmap.height()<<endl;
      ofstream rightWingOutputTex;
      rightWingOutputTex.open("assets/rightwingTex.out");
      rightWingOutputTex<<numFeathers<<endl;
      for(int i=0;i<numFeathers;i++){
        rightWingOutputTex<<i<<" "<<textures[2*i].x()/pixmap.width()<<" "<<abs(textures[2*i].y()/pixmap.height());
        rightWingOutputTex<<" "<<textures[2*i+1].x()/pixmap.width()<<" "<<abs(textures[2*i+1].y()/pixmap.height())<<endl;
      }

      rightWingOutput<<endl;
      rightWingOutput.close();
    }
    else if(i==TAIL){
      int total = 45;
      float _length[total];
      float t1_start = 0.25;
      float t1_end = 0.125;
      float t2_start = 0.75;
      float t2_end = 0.825;
      for(int i=0;i<total;i++){
        float t1 = t1_start + (t1_end-t1_start)*i*1.0/total;
        float t2 = t2_start + (t2_end-t2_start)*i*1.0/total;
        QVector2D p1 = QVector2D(path.pointAtPercent(t1));
        QVector2D p2 = QVector2D(path.pointAtPercent(t2));
        _length[i] = p1.distanceToPoint(p2);
      }
      ofstream tailOutput;
      tailOutput.open("assets/tail.out");
      tailOutput<<total<<endl;
      for(int i=0;i<total;i++){
        tailOutput<<i<<" "<<_length[i]<<endl;
      }
      tailOutput<<endl;
    }

    for(float t=0;t<=1;t=t+0.01){
       QPointF p = path.pointAtPercent(t);
       wholeFigure<<p.x()<<","<<p.y()<<endl;
    }
  }

  for(int i=0;i<k;i++)samples[i].clear();
  vector<VertexData> vertices;
  vector<int> indices;
  // int lastIndex = 0;
  int y[3] = {TORSO,RIGHTWING,TAIL};
  int p=1;
  for(int pp=0;pp<3;pp++){
    int i = y[pp];
    QPainterPath path(_points[i][0]);
    for(int j=1;j<=_size[i];j=j+3){
      path.cubicTo(_points[i][j%_size[i]],_points[i][(j+1)%_size[i]],_points[i][(j+2)%_size[i]]);
    }
    if(i==TORSO){
      for(float t = 0.75;t<1.25;t=t+0.03125){
        float x = t>1?t-1:t;
        QPointF p = path.pointAtPercent(x);
        samples[i].push_back(p);
      }
      int maxY = samples[i][0].y();
      int minY = samples[i][samples[i].size()-1].y();
      int diff = maxY - minY;
      for(unsigned int j=0;j<samples[i].size()-1;j++){
        float divisions = 50;
        float theta = 2*3.1415/divisions;

        float height1 = samples[i][j].y();
        float radius1 = samples[i][j].x();
        float height2 = samples[i][j+1].y();
        float radius2 = samples[i][j+1].x();

        float x[4],y[4],z[4];
        VertexData v[4];
        QVector3D my_points[4];
        QVector2D texCoord[4];
        for(int l=0;l<divisions;l++){
          x[0] = radius1*cos(l*theta);
          y[0] = radius1*sin(l*theta);
          z[0] = height1;
          texCoord[0] = QVector2D(l*1.0/divisions,(height1-minY)/(diff));
          x[1] = radius2*cos(l*theta);
          y[1] = radius2*sin(l*theta);
          z[1] = height2;
          texCoord[1] = QVector2D(l*1.0/divisions,(height2-minY)/(diff));

          x[2] = radius2*cos((l+1)*theta);
          y[2] = radius2*sin((l+1)*theta);
          z[2] = height2;
          texCoord[2] = QVector2D((l+1)*1.0/divisions,(height2-minY)/(diff));

          x[3] = radius1*cos((l+1)*theta);
          y[3] = radius1*sin((l+1)*theta);
          z[3] = height1;
          texCoord[3] = QVector2D((l+1)*1.0/divisions,(height1-minY)/(diff));

          for(int i=0;i<4;i++){
            my_points[i] = {x[i],y[i],z[i]};
            v[i] = VertexData(my_points[i]/10,texCoord[i],QVector3D(1,1,1));
          }

          vertices.push_back(v[0]);
          vertices.push_back(v[1]);
          vertices.push_back(v[2]);
          vertices.push_back(v[3]);
          indices.push_back(p+1);//1+ j*divisions*4 + 4*l+1);
          indices.push_back(p);//1+ j*divisions*4 + 4*l);
          indices.push_back(p+2);//1+ j*divisions*4 + 4*l+2);
          indices.push_back(p);//1+ j*divisions*4 + 4*l);
          indices.push_back(p+2);//1+ j*divisions*4 + 4*l+2);
          indices.push_back(p+3);//1+ j*divisions*4 + 4*l+3);
          // lastIndex = 1+ j*divisions*4 + 4*l+3+1;
          p=p+4;
        }
      }
    }
    else if(i==RIGHTWING){
      float t1_start = 0.75;
      float t1_end = 0.875;
      float t2_start = 0.625;
      float t2_end = 0;

      float x[4],y[4],z[4];
      VertexData v[4];
      QVector3D my_points[4];
      QVector2D texCoord[4];

      for(int i=0;i<180;i++){

        float t1 = t1_start + (t1_end-t1_start)*i/180.0;
        float t2 = t2_start + (t2_end-t2_start)*i/180.0;
        float t4 = t1_start + (t1_end-t1_start)*(i+1)/180.0;
        float t3 = t2_start + (t2_end-t2_start)*(i+1)/180.0;
        QVector2D p1 = QVector2D(path.pointAtPercent(t1));
        QVector2D p2 = QVector2D(path.pointAtPercent(t2));
        QVector2D p3 = QVector2D(path.pointAtPercent(t3));
        QVector2D p4 = QVector2D(path.pointAtPercent(t4));
{        //
        // x[0] = p1.x();
        // y[0] = 0.0;
        // z[0] = p1.y();
        // texCoord[0] = QVector2D(0,1);
        //
        // x[1] = p2.x();
        // y[1] = 0;
        // z[1] = p2.y();
        // texCoord[1] = QVector2D(0,0);
        //
        // x[2] = p3.x();
        // y[2] = 0;
        // z[2] = p3.y();
        // texCoord[2] = QVector2D(1,1);
        //
        // x[3] = p4.x();
        // y[3] = 0;
        // z[3] = p4.y();
        // texCoord[3] = QVector2D(1,0);
        //
        // x[4] = -p1.x();
        // y[4] = 0;
        // z[4] = p1.y();
        // texCoord[4] = QVector2D(0,1);
        //
        // x[5] = -p2.x();
        // y[5] = 0;
        // z[5] = p2.y();
        // texCoord[5] = QVector2D(0,0);
        //
        // x[6] = -p3.x();
        // y[6] = 0;
        // z[6] = p3.y();
        // texCoord[6] = QVector2D(1,1);
        //
        // x[7] = -p4.x();
        // y[7] = 0;
        // z[7] = p4.y();
        // texCoord[7] = QVector2D(1,0);
}
          QVector2D center1 = (p1 + p4)/2;
        QVector2D center2 = (p2 + p3)/2;
        float radius11 = (p1 - center1).length();
        float radius12Max = 25;
        float radius21 = (p2 - center2).length();
        float radius22Max = 25;


        int divisions = 5;
        float theta = 2*3.1415/divisions;

        for(int l=0;l<divisions;l++){
          float radius12 = radius12Max*(divisions-l)*1.0/divisions;
          float radius22 = radius22Max*(divisions-l)*1.0/divisions;
          x[0] = p1.x();
          z[0] = radius11*cos(l*theta);
          y[0] = radius12*sin(l*theta);
          texCoord[0] = QVector2D(l*1.0/divisions,cos(l*theta));

          x[1] = p2.x();
          z[1] = radius21*cos(l*theta);
          y[1] = radius22*sin(l*theta);
          texCoord[1] = QVector2D(l*1.0/divisions,cos(l*theta));

          x[2] = p2.x();
          z[2] = radius21*cos((l+1)*theta);
          y[2] = radius22*sin((l+1)*theta);
          texCoord[2] = QVector2D((l+1)*1.0/divisions,cos((l+1)*theta));

          x[3] = p1.x();
          z[3] = radius11*cos((l+1)*theta);
          y[3] = radius12*sin((l+1)*theta);
          texCoord[3] = QVector2D((l+1)*1.0/divisions,cos((l+1)*theta));

          for(int i=0;i<4;i++){
            my_points[i] = {x[i],y[i],z[i]};
            v[i] = VertexData(my_points[i]/10,texCoord[i],QVector3D(1,1,1));
          }

          vertices.push_back(v[0]);
          vertices.push_back(v[1]);
          vertices.push_back(v[2]);
          vertices.push_back(v[3]);
          indices.push_back(p+1);//1+ j*divisions*4 + 4*l+1);
          indices.push_back(p);//1+ j*divisions*4 + 4*l);
          indices.push_back(p+2);//1+ j*divisions*4 + 4*l+2);
          indices.push_back(p);//1+ j*divisions*4 + 4*l);
          indices.push_back(p+2);//1+ j*divisions*4 + 4*l+2);
          indices.push_back(p+3);//1+ j*divisions*4 + 4*l+3);
          // lastIndex = 1+ j*divisions*4 + 4*l+3+1;
          p=p+4;
        }

      }
    }
    else if(i==TAIL){
      int total = 45;
      float t1_start = 0.25;
      float t1_end = 0.125;
      float t2_start = 0.75;
      float t2_end = 0.825;

        float x[8],y[8],z[8];
        VertexData v[8];
        QVector3D my_points[8];
        QVector2D texCoord[8];

      for(int i=0;i<total-1;i++){
        float t1 = t1_start + (t1_end-t1_start)*i*1.0/total;
        float t2 = t2_start + (t2_end-t2_start)*i*1.0/total;
        float t4 = t1_start + (t1_end-t1_start)*(i+1.0)/total;
        float t3 = t2_start + (t2_end-t2_start)*(i+1.0)/total;
        QVector2D p1 = QVector2D(path.pointAtPercent(t1));
        QVector2D p2 = QVector2D(path.pointAtPercent(t2));
        QVector2D p3 = QVector2D(path.pointAtPercent(t3));
        QVector2D p4 = QVector2D(path.pointAtPercent(t4));

        x[0] = p1.x();
        y[0] = 0.1;
        z[0] = p1.y();
        texCoord[0] = QVector2D(0,1);

        x[1] = p2.x();
        y[1] = 0;
        z[1] = p2.y();
        texCoord[1] = QVector2D(0,0);

        x[2] = p3.x();
        y[2] = 0;
        z[2] = p3.y();
        texCoord[2] = QVector2D(1,1);

        x[3] = p4.x();
        y[3] = 0;
        z[3] = p4.y();
        texCoord[3] = QVector2D(1,0);

        x[4] = -p1.x();
        y[4] = 0;
        z[4] = p1.y();
        texCoord[4] = QVector2D(0,1);

        x[5] = -p2.x();
        y[5] = 0;
        z[5] = p2.y();
        texCoord[5] = QVector2D(0,0);

        x[6] = -p3.x();
        y[6] = 0;
        z[6] = p3.y();
        texCoord[6] = QVector2D(1,1);

        x[7] = -p4.x();
        y[7] = 0;
        z[7] = p4.y();
        texCoord[7] = QVector2D(1,0);

        for(int i=0;i<8;i++){
          my_points[i] = {x[i],y[i],z[i]};
          v[i] = VertexData(my_points[i]/10,texCoord[i],QVector3D(1,1,1));
        }

        vertices.push_back(v[0]);
        vertices.push_back(v[1]);
        vertices.push_back(v[2]);
        vertices.push_back(v[3]);
        vertices.push_back(v[0+4]);
        vertices.push_back(v[1+4]);
        vertices.push_back(v[2+4]);
        vertices.push_back(v[3+4]);
        indices.push_back(p+1);//lastIndex + 8*i+1);
        indices.push_back(p);//lastIndex + 8*i);
        indices.push_back(p+2);//lastIndex  + 8*i+2);
        indices.push_back(p);//lastIndex  + 8*i);
        indices.push_back(p+2);//lastIndex  + 8*i+2);
        indices.push_back(p+3);//lastIndex  + 8*i+3);
        indices.push_back(p+5);//lastIndex + 8*i+1+4);
        indices.push_back(p+4);//lastIndex + 8*i+4);
        indices.push_back(p+6);//lastIndex  + 8*i+2+4);
        indices.push_back(p+4);//lastIndex  + 8*i+4);
        indices.push_back(p+6);//lastIndex  + 8*i+2+4);
        indices.push_back(p+7);//lastIndex  + 8*i+3+4);
        p=p+8;
      }
    }

    for(float t=0;t<=1;t=t+0.01){
       QPointF p = path.pointAtPercent(t);
       wholeFigure<<p.x()<<","<<p.y()<<endl;
    }
  }

  for(unsigned int i=0;i<vertices.size();i++){
    wholeFigureObj<<"v "<<vertices[i].position.x()<<" "<<vertices[i].position.y()<<" "<<vertices[i].position.z()<<endl;
  }
  for(unsigned int i=0;i<vertices.size();i++){
    wholeFigureObj<<"vt "<<vertices[i].texCoord.x()<<" "<<vertices[i].texCoord.y()<<endl;
  }

  for(unsigned int i=0;i<indices.size()-2;i=i+3){
    wholeFigureObj<<"f "<<indices[i]<<" ";
    wholeFigureObj<<indices[i+1]<<" ";
    wholeFigureObj<<indices[i+2]<<endl;
  }
  myFile.close();
  wholeFigure.close();
  wholeFigureObj.close();
  printDimensions("assets/birdSpecifications/bird_dimensions.txt");
}
