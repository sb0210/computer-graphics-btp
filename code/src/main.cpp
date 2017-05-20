/* #include "license.txt" */
#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#ifndef QT_NO_OPENGL
#include "widgets/MainWidget.h"
#include "widgets/MainWindow.h"
#endif

#include "simulation/World.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Bird");
    app.setApplicationVersion("0.1");
#ifndef QT_NO_OPENGL
    int x = 0;
    cin>>x;
    if(x==0){
        FeatherWidget window;
        window.show();
        return app.exec();
    }
    else if(x==1){
        DrawingWidget window;
        window.show();
        return app.exec();
    }
        // MainWindow window;
    else if(x==2){
        MainWidget window;
        window.show();
    return app.exec();
    }
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
}
