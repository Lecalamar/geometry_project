#ifndef CURVE_2D_AITKEN_CHORDAL_H
#define CURVE_2D_AITKEN_CHORDAL_H
#define RESOLUTION_A 300

#include "curve2D.h"
#include <vector>
using namespace std;

class Curve2DAitkenChordal : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_A]; //points which will linked
 public:
 Curve2DAitkenChordal(const QString &name) : Curve2D(name) {}
 Curve2DAitkenChordal(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
   
  Vector2f AitkenChordal(int k, int i, float t, float frame, float *param);
  void evalAitkenChordal(float frame);
  
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
    tab[0]= evalAnimPt(get(0),frame);
    p.moveTo(tab[0][0],tab[0][1]);
    evalAitkenChordal(frame);
    for (unsigned int i = 1; i < RESOLUTION_A; i++){
      p.lineTo(tab[i][0],tab[i][1]);
    }
    return p;
  }
};

class Curve2DAitkenChordalConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DAitkenChordalConstructor()                     {}
  virtual const QString type() const                      { return "AitkenChordalCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DAitkenChordal(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DAitkenChordal(c,name); }
};

#endif
