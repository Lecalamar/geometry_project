#ifndef CURVE_1D_STEP_H
#define CURVE_1D_STEP_H

#include "curve1D.h"

class Curve1DStep : public Curve1D {
 public:
 Curve1DStep(const QString &name) : Curve1D(name) {}
 Curve1DStep(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;

    // empty test 
    if(empty()) 
      return p;

    // left part 
    if(xmin<_points[0][0]) {
      p.moveTo(xmin,_points[0][1]);
      p.lineTo(_points[0][0],_points[0][1]);
    } else {
      p.moveTo(_points[0][0],_points[0][1]);
    }

    // draw function 
    for(unsigned int i=1;i<nbPts();++i) {
      p.lineTo(_points[i][0],_points[i-1][1]);
      p.moveTo(_points[i][0],_points[i][1]);
    }

    // right part 
    if(xmax>_points[nbPts()-1][0]) {
      p.lineTo(xmax,_points[nbPts()-1][1]);
    }

    return p;
  }

  float evalAt(float x) {
    // special cases 
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    // linear interp
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
	return _points[i][1];
      }
    }
    return _points[0][1];
  }
};


class Curve1DStepConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DStepConstructor()                     {}
  virtual const QString type() const                      { return "StepCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DStep(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DStep(c,name); }
};


#endif // CURVE_1D_STEP_H
