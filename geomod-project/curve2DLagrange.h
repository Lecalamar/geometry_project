#ifndef CURVE_2D_LAGRANGE_H
#define CURVE_2D_LAGRANGE_H

#define RESOLUTION 100
#include "curve2D.h"
#include <vector>
using namespace std;
#include <iostream>
class Curve2DLagrange : public Curve2D {
	private:
	Vector2f tab[5*RESOLUTION]; //points which will linked 
	public:
	Curve2DLagrange(const QString &name) : Curve2D(name) {}
	Curve2DLagrange(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
	float evalPoly(int i, float x, float frame);
	void lagrange(float frame);
	QPainterPath path(float frame){
		QPainterPath p;
		if(nbPts()==0) 
			return p;
			
		//tab[0]= evalAnimPt(get(0),frame);
		//p.moveTo(tab[0][0],tab[0][1]);
		float x0 = 10000;
		float y0 = 0;
		for(unsigned int i=0;i<nbPts();i++){
			if(x0 > evalAnimPt(get(i),frame)[0]){
				x0 = evalAnimPt(get(i),frame)[0];
				y0 = evalAnimPt(get(i),frame)[1];
			}
		}
		p.moveTo(x0,y0);
		lagrange(frame);
		for (unsigned int i=1; i<5*RESOLUTION; i++){
			  p.lineTo(tab[i][0],tab[i][1]);
		}
	 
		return p;
	}

};

class Curve2DLagrangeConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DLagrangeConstructor()                     {}
  virtual const QString type() const                      { return "LagrangeCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DLagrange(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DLagrange(c,name); }
};

#endif
