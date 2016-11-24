#ifndef CURVE_2D_GEAR_H
#define CURVE_2D_GEAR_H
#define RESOLUTION_G 1000
#include "curve2D.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Curve2DGear : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_G]; //points which will linked
  int sense;
 public:
 Curve2DGear(const QString &name) : Curve2D(name) {}
 Curve2DGear(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  Vector2f M(float alpha, float teta, Vector2f P, float R, float frame);
  void gear(Vector2f center, float R, int sense, int N, float B, float frame);
  QPainterPath path(float frame){
    QPainterPath p;
    float B = 5.0; //we chose that, B is a constant because gears must have the same size of teeth
    if(nbPts()==0) 
      return p;
    if(nbPts() >= 2) { 
      sense = nbPts()%2; //to chose the rotation sense you must be 2 or 3 points
      for(unsigned int j = 0; j < nbPts(); j++){ 
	Vector2f center = evalAnimPt(get(nbPts()-2),frame);
	Vector2f P = evalAnimPt(get(nbPts()-1),frame);
	float R = sqrt(pow(center[0]-P[0],2)+pow(P[1]-center[1],2));
	int N = floor(M_PI*(float)R/(2*B));
	R = 2*N*B/M_PI; //The radius can not have all values

	for(int i = 0; i < RESOLUTION_G; i++){
	  tab[i] = {0,0}; 
	}
	gear(center, R, sense, N, B, frame);
	p.moveTo(tab[0][0],tab[0][1]);
	for (int i = 1; tab[i][0]!=0; i++){ //we do not know how many points there will have. We could use vectors 
	  p.lineTo(tab[i][0],tab[i][1]);
	}
      }
    }
    return p;
  }
};

class Curve2DGearConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DGearConstructor()                     {}
  virtual const QString type() const                      { return "GearCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DGear(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DGear(c,name); }
};

#endif
