#ifndef CURVE_2D_HERMITE_CLOSED_H
#define CURVE_2D_HERMITE_CLOSED_H
#define RESOLUTION_HC 50
#include "curve2D.h"
#include <vector>
using namespace std;

class Curve2DHermiteClosed : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_HC]; //points which will be linked
 public:
 Curve2DHermiteClosed(const QString &name) : Curve2D(name) {}
 Curve2DHermiteClosed(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}

  vector<float> H(float t);
  float distance(Vector2f P1,Vector2f P2);
  float projection(Vector2f P1,Vector2f P2, Vector2f P3);
  float tangent(Vector2f P1,Vector2f P2);
  Vector2f coeff(float t, int i, float frame);
  void evalHermiteClosed(int i,float frame);
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
  
    if (nbPts() > 2){
      tab[0]= evalAnimPt(get(0),frame); 
      p.moveTo(tab[0][0],tab[0][1]);
      for (unsigned int j = 0; j < nbPts(); j++){ //For every couple of points there are one cubic Hermite spline
	evalHermiteClosed(j,frame);
	for (unsigned int i = 0; i < RESOLUTION_HC; i++){
	  p.lineTo(tab[i][0],tab[i][1]);
	}
      }
    }
    return p;    
  }
};

class Curve2DHermiteClosedConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DHermiteClosedConstructor()                     {}
  virtual const QString type() const                      { return "HermiteClosedCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DHermiteClosed(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DHermiteClosed(c,name); }
};

#endif
