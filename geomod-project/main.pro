# define your application name here 
TARGET = CurveDraw

# add your source cpp files here 
SOURCES += \
    main.cpp \
    mainWidget.cpp \
    toolsWidget.cpp \
    drawingWidgetItems.cpp \
    drawingWidget.cpp \
    animationWidgetItems.cpp \
    animationWidget.cpp \
    scene.cpp \
    animatedPoint.cpp \
    curve2DBezier.cpp\
    curve2DAitken.cpp\
    curve2DAitkenChordal.cpp\
    curve2DBezierClosed.cpp\
    parametrization.cpp

# add your header files here
HEADERS += \
    mainWidget.h \
    toolsWidget.h \
    drawingWidgetItems.h \
    drawingWidget.h \
    animationWidgetItems.h \
    animationWidget.h \
    scene.h \
    curve1D.h \
    curve2D.h \
    curve1DLinear.h \
    curve1DStep.h \
    curve2DLinear.h \
    curve2DLinearClosed.h \
    curve2DBezier.h \
    curve2DBezierClosed.h \
    curve2DAitken.h \
    curve2DAitkenChordal.h\
    animatedPoint.h\
    parametrization.h

TEMPLATE = app

INCLUDEPATH += eigen

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-misleading-indentation -Wno-deprecated-declarations

QT += core gui widgets
