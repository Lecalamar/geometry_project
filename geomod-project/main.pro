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
    parametrization.cpp \
    curve2DBezier.cpp \
    curve2DAitken.cpp \
    curve2DHermite1.cpp\
    curve2DHermiteClosed.cpp\
    curve2DBezierClosed.cpp \
    curve2DLagrange.cpp \
    curve2DSquare.cpp \
    Matrice.cpp \
    curve2DAitkenChordal.cpp \
    curve2DAitkenCentripetal.cpp \
    curve2DWheel.cpp \
    curve2DGear.cpp \
    curve2DCircle.cpp 

# add your header files here
HEADERS += \
    mainWidget.h \
    toolsWidget.h \
    drawingWidgetItems.h \
    drawingWidget.h \
    animationWidgetItems.h \
    animationWidget.h \
    scene.h \
    animatedPoint.h \
    parametrization.h \
    curve1D.h \
    curve2D.h \
    curve1DLinear.h \
    curve1DStep.h \
    curve2DLinear.h \
    curve2DLinearClosed.h \
    curve2DBezier.h \
    curve2DBezierClosed.h \
    curve2DAitken.h \
    curve2DHermite1.h \
    curve2DHermiteClosed.h \
    animatedPoint.h \
    curve2DLagrange.h \
    curve1DSinus.h \
    curve2DSquare.h \
    Matrice.h \
    curve2DAitkenChordal.h \
    curve2DAitkenCentripetal.h \
    curve2DWheel.h \
    curve2DGear.h \
    curve2DCircle.h

TEMPLATE = app

INCLUDEPATH += eigen

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-misleading-indentation -Wno-deprecated-declarations

QT += core gui widgets
