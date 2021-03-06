#ifndef CURVE_2D_WHEEL_H
#define CURVE_2D_WHEEL_H
#define RESOLUTION_W 100
#include "curve2D.h"
#include <vector>
#include <cmath>
using namespace std;

class Curve2DWheel : public Curve2D {
 private:
  Vector2f tab[RESOLUTION_W]; //points which will linked
 public:
 Curve2DWheel(const QString &name) : Curve2D(name) {}
 Curve2DWheel(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
  void circle(Vector2f center, float R, float frame);
  QPainterPath path(float frame){
    QPainterPath p;
    if(nbPts()==0) 
      return p;
    if(nbPts() == 2) {
      Vector2f center = evalAnimPt(get(0),frame);
      Vector2f P = evalAnimPt(get(1),frame);
      float R = sqrt(pow(center[0]-P[0],2)+pow(P[1]-center[1],2));
      p.moveTo(center[0]+R,center[1]);
      circle(center, R,frame);
      for (unsigned int i = 0; i < RESOLUTION_W; i++){
	p.lineTo(tab[i][0],tab[i][1]);
      }
      int j = (int)(frame)%(RESOLUTION_W);
      int l = RESOLUTION_W/25;
      p.moveTo(tab[(j)%(RESOLUTION_W)][0],tab[(j)%(RESOLUTION_W)][1]);
      p.lineTo(tab[(j+(RESOLUTION_W/2)+l)%(RESOLUTION_W)][0],tab[(j+RESOLUTION_W/2+l)%(RESOLUTION_W)][1]);
      p.moveTo(tab[(j+l)%(RESOLUTION_W)][0],tab[(j+l)%(RESOLUTION_W)][1]);
      p.lineTo(tab[(j+(RESOLUTION_W/2))%(RESOLUTION_W)][0],tab[(j+RESOLUTION_W/2)%(RESOLUTION_W)][1]);
      p.moveTo(tab[(j+RESOLUTION_W/4)%(RESOLUTION_W)][0],tab[(j+RESOLUTION_W/4)%(RESOLUTION_W)][1]);
      p.lineTo(tab[(j+(RESOLUTION_W/2+RESOLUTION_W/4)+l)%(RESOLUTION_W)][0],tab[(j+RESOLUTION_W/2+RESOLUTION_W/4+l)%(RESOLUTION_W)][1]);
      p.moveTo(tab[(j+l+RESOLUTION_W/4)%(RESOLUTION_W)][0],tab[(j+l+RESOLUTION_W/4)%(RESOLUTION_W)][1]);
      p.lineTo(tab[(j+(RESOLUTION_W/2+RESOLUTION_W/4))%(RESOLUTION_W)][0],tab[(j+RESOLUTION_W/2+RESOLUTION_W/4)%(RESOLUTION_W)][1]);
      p.moveTo(center[0]+4.0/3*R,center[1]);
      circle(center, 4.0/3*R, frame);
      for (unsigned int i = 0; i < RESOLUTION_W; i++){
	p.lineTo(tab[i][0],tab[i][1]);
      }
    }   
    return p;
  }
};

class Curve2DWheelConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DWheelConstructor()                     {}
  virtual const QString type() const                      { return "WheelCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DWheel(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DWheel(c,name); }
};

#endif
