#include "scene.h"

// add all your types of 2D curves here 
#include "curve2DLinear.h"
#include "curve2DLinearClosed.h"
#include "curve2DBezier.h"
#include "curve2DBezierClosed.h"
#include "curve2DAitken.h"
#include "curve2DAitkenChordal.h"
//#include "curve2DHermite1.h"

#include "curve1DLinear.h"
#include "curve1DStep.h"
Scene *Scene::_instance = NULL;

using namespace std;

// add 2D curve builders here 
void Scene::initCurveBuilders() {
  addCurveBuilder(new Curve2DLinearConstructor());
  addCurveBuilder(new Curve2DLinearClosedConstructor());
  addCurveBuilder(new Curve2DBezierConstructor());
  addCurveBuilder(new Curve2DBezierClosedConstructor());
  addCurveBuilder(new Curve2DAitkenConstructor());
  addCurveBuilder(new Curve2DAitkenChordalConstructor());
  //  addCurveBuilder(new Curve2DHermite1Constructor());
}

// add 1D curve builders (functions) here
void Scene::initFunctionBuilders() {
  addFunctionBuilder(new Curve1DLinearConstructor());
  addFunctionBuilder(new Curve1DStepConstructor());
}


void Scene::cleanCurveBuilders() {
  map<QString,Curve2DConstructor *>::const_iterator mit(_curveBuilders.begin()),mend(_curveBuilders.end());
  
  for(;mit!=mend;++mit) { 
    delete mit->second; 
  }

  _curveBuilders.clear();
}

void Scene::cleanFunctionBuilders() {
  map<QString,Curve1DConstructor *>::const_iterator mit(_functionBuilders.begin()),mend(_functionBuilders.end());
  
  for(;mit!=mend;++mit) { 
    delete mit->second; 
  }

  _functionBuilders.clear();
}


Scene::Scene() {
  initFunctionBuilders();
  initCurveBuilders();
  setDefaultSettings();
}

Scene::~Scene() {
  clean();
  cleanFunctionBuilders();
  cleanCurveBuilders();
}

