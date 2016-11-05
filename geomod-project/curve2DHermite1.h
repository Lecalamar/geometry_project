#ifndef CURVE_2D_HERMITE1_H
#define CURVE_2D_HERMITE1_H
#define RESOLUTION_H1 50
#include "curve2D.h"
#include <vector>
using namespace std;

class Curve2DHermite1 : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_H1]; //points which will be linked
 public:
 Curve2DHermite1(const QString &name) : Curve2D(name) {}
 Curve2DHermite1(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  vector<float> H(float t);
  Vector2f coeff(float t, int i, float frame);
  void evalHermite1(int i,float frame);
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
  
    if (nbPts() > 2){
      tab[0]= evalAnimPt(get(0),frame); 
      p.moveTo(tab[0][0],tab[0][1]);
      for (unsigned int j = 0; j < nbPts()-1; j++){ //For every couple of points there are one cubic Hermite spline
	evalHermite1(j,frame);
	for (unsigned int i = 0; i < RESOLUTION_H1; i++){
	  p.lineTo(tab[i][0],tab[i][1]);
	}
      }
    }
    return p;    
  }
};

class Curve2DHermite1Constructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DHermite1Constructor()                     {}
  virtual const QString type() const                      { return "Hermite1Curve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DHermite1(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DHermite1(c,name); }
};

#endif
