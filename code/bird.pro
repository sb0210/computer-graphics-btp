QT       += core gui widgets
CONFIG += debug c++11
LIBS =  -lode -ldrawstuff -lGL -lGLEW -lglfw -lX11 -lpthread -lGLU
TARGET = bird
INCLUDEPATH = include
DESTDIR=bin
OBJECTS_DIR=build #Intermediate object files directory
MOC_DIR=build #Intermediate moc files directory
QMAKE_CXXFLAGS_WARN_OFF -= -Wno-unused-parameter

SOURCES += src/main.cpp

SOURCES += \
    src/helpers/*.cpp \
    src/physics/*.cpp \
    src/widgets/*.cpp \
    src/geometry/*.cpp \
    src/simulation/*.cpp 


HEADERS += \
    include/helpers/*.h \
    include/physics/*.h \
    include/widgets/*.h \
    include/geometry/*.h \
    include/simulation/*.h \

RESOURCES += \
    src/resources/shaders.qrc \

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target
