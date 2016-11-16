#ifndef CURVE_2D_AITKEN_CENTRIPETAL_H
#define CURVE_2D_AITKEN_CENTRIPETAL_H
#define RESOLUTION_A 300

#include "curve2DAitken.h"
#include <vector>
using namespace std;

class Curve2DAitkenCentripetal : public Curve2DAitken {
 private:
  Vector2f tab[RESOLUTION_A]; //points which will linked
 public:
 Curve2DAitkenCentripetal(const QString &name) : Curve2DAitken(name) {}
 Curve2DAitkenCentripetal(Curve2D *curve,const QString &name) : Curve2DAitken(curve,name) {}
   
  void evalAitkenCentripetal(float frame);
  
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
    tab[0]= evalAnimPt(get(0),frame);
    p.moveTo(tab[0][0],tab[0][1]);
    evalAitkenCentripetal(frame);
    for (unsigned int i = 1; i < RESOLUTION_A; i++){
      p.lineTo(tab[i][0],tab[i][1]);
    }
    return p;
  }
};

class Curve2DAitkenCentripetalConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DAitkenCentripetalConstructor()                     {}
  virtual const QString type() const                      { return "AitkenCentripetalCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DAitkenCentripetal(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DAitkenCentripetal(c,name); }
};

#endif
