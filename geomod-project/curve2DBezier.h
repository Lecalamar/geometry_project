#ifndef CURVE_2D_BEZIER_H
#define CURVE_2D_BEZIER_H

#include "curve2D.h"

class Curve2DBezier : public Curve2D {
 public:
 Curve2DBezier(const QString &name) : Curve2D(name) {}
 Curve2DBezier(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  
  QPainterPath path(float frame) {
    QPainterPath p;
    if(nbPts()==0) 
      return p;

    Vector2f pt = evalAnimPt(get(0),frame);
//DEBUT A COMPLETER
    p.moveTo(pt[0],pt[1]);
    for(unsigned int i=1;i<nbPts();++i) {
      pt = evalAnimPt(get(i),frame);
    }
    return p;
  }
  //FIN A COMPLETER
};


class Curve2DBezierConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DBezierConstructor()                     {}
  virtual const QString type() const                      { return "BezierCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DBezier(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DBezier
		  (c,name); }
};


#endif
