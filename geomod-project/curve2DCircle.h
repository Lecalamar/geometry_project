#ifndef CURVE_2D_CIRCLE_H
#define CURVE_2D_CIRCLE_H
#define RESOLUTION_C 100
#include "curve1DSinus.h" //for definition of PI
#include "curve2D.h"
#include <vector>
#include <cmath>
using namespace std;

class Curve2DCircle : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_C]; //points which will linked
 public:
 Curve2DCircle(const QString &name) : Curve2D(name) {}
 Curve2DCircle(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
   
  void circle(float frame);
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
     if(nbPts() == 2) {
      circle(frame);
      p.moveTo(tab[0][0],tab[0][1]);
      for (unsigned int i = 1; i < RESOLUTION_C; i++){
	p.lineTo(tab[i][0],tab[i][1]);
      }
    }
   
    return p;
  }

};

class Curve2DCircleConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DCircleConstructor()                     {}
  virtual const QString type() const                      { return "CircleCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DCircle(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DCircle(c,name); }
};

#endif
