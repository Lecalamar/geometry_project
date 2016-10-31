#ifndef CURVE_2D_BEZIER_CLOSED_H
#define CURVE_2D_BEZIER_CLOSED_H

#define RESOLUTION_BC 300
#include "curve2D.h"
#include <vector>
using namespace std;
class Curve2DBezierClosed : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_BC]; //points which will linked
 public:
 Curve2DBezierClosed(const QString &name) : Curve2D(name) {}
 Curve2DBezierClosed(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
   
  Vector2f CasteljauClosed(int k,int i,float t, float frame);
  void evalCasteljauClosed(float frame);
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
    tab[0]= evalAnimPt(get(0),frame);
    p.moveTo(tab[0][0],tab[0][1]);
      evalCasteljauClosed(frame);
    for (unsigned int i=1; i<RESOLUTION_BC; i++){
      p.lineTo(tab[i][0],tab[i][1]);
    }
   
    return p;
  }

};

class Curve2DBezierClosedConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DBezierClosedConstructor()                     {}
  virtual const QString type() const                      { return "BezierClosedCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DBezierClosed(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DBezierClosed(c,name); }
};

#endif
