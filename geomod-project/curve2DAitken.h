#ifndef CURVE_2D_AITKEN_H
#define CURVE_2D_AITKEN_H
#define RESOLUTION_A 300

#include "curve2D.h"
#include <vector>
using namespace std;
class Curve2DAitken : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_A]; //points which will linked
 public:
 Curve2DAitken(const QString &name) : Curve2D(name) {}
 Curve2DAitken(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
   
  Vector2f Aitken(int k,int i,float t, float frame);
  void evalAitken(float frame);
  void ChordalParam(float frame, float *t);
  Vector2f AitkenParam(int k, int i, float t, float frame, float *param);
  void evalAitkenChord(float frame);
  
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
    tab[0]= evalAnimPt(get(0),frame);
    p.moveTo(tab[0][0],tab[0][1]);
    evalAitken(frame);
    for (unsigned int i = 1; i < RESOLUTION_A; i++){
      p.lineTo(tab[i][0],tab[i][1]);
    }
    return p;
  }
};

class Curve2DAitkenConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DAitkenConstructor()                     {}
  virtual const QString type() const                      { return "AitkenCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DAitken(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DAitken(c,name); }
};

#endif
