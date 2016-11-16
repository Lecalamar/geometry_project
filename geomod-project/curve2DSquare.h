#ifndef CURVE_2D_SQUARE_H
#define CURVE_2D_SQUARE_H

#define RESOLUTION_SQUARE 1000
#include "curve2D.h"
#include "Matrice.h"
#include <vector>
using namespace std;
#include <iostream>
class Curve2DSquare : public Curve2D {
	private:
	Vector2f tab[RESOLUTION_SQUARE]; //points which will linked 
	public:
	Curve2DSquare(const QString &name) : Curve2D(name) {}
	Curve2DSquare(Curve2D *curve,const QString &name) : Curve2D(curve,name) {}
	float polyVal(Matrice p, float x);
	void meanSquare(float frame);
	QPainterPath path(float frame){
		QPainterPath p;
		if(nbPts()==0) 
			return p;
			
		meanSquare(frame);
		p.moveTo(tab[0][0],tab[0][1]);
		for (unsigned int i=1; i<RESOLUTION_SQUARE; i++){
			  p.lineTo(tab[i][0],tab[i][1]);
		}
	 
		return p;
	}

};

class Curve2DSquareConstructor : public Curve2DConstructor {
 public:
  virtual ~Curve2DSquareConstructor()                     {}
  virtual const QString type() const                      { return "MeanSquareCurve";             }
  virtual Curve2D *create(const QString &name)            { return new Curve2DSquare(name);   }
  virtual Curve2D *create(Curve2D *c,const QString &name) { return new Curve2DSquare(c,name); }
};

#endif
