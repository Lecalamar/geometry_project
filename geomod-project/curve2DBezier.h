#ifndef CURVE_2D_BEZIER_H
#define CURVE_2D_BEZIER_H

#define RESOLUTION 100
#include "curve2D.h"
#include <vector>
using namespace std;
class Curve2DBezier : public Curve2D {
 private:
  Vector2f tab[RESOLUTION]; //points which will be linked
 public:
 Curve2DBezier(const QString &name) : Curve2D(name) {}
 Curve2DBezier(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
   
  Vector2f Casteljau(int k,int i,float t, float frame);
  void evalCasteljau(float frame);
  void evalChord(float frame);
  
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
    tab[0]= evalAnimPt(get(0),frame);
    p.moveTo(tab[0][0],tab[0][1]);
    
    evalCasteljau(frame);
    for (unsigned int i=1; i<RESOLUTION; i++){
      p.lineTo(tab[i][0],tab[i][1]);
    }
   
    return p;
  }

};

class Curve2DBezierConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DBezierConstructor()                     {}
  virtual const QString type() const                      { return "BezierCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DBezier(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DBezier(c,name); }
};

#endif
