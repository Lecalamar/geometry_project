#ifndef CURVE_1D_SINUS_H
#define CURVE_1D_SINUS_H
#define PI 3.14159265

#include <math.h>
#include "curve1D.h"

class Curve1DSinus : public Curve1D {
 public:
 Curve1DSinus(const QString &name) : Curve1D(name) {}
 Curve1DSinus(Curve1D *curve,const QString &name) : Curve1D(curve,name) {}
  
  QPainterPath path(float xmin,float xmax) {
    QPainterPath p;

    // empty test 
    if(empty()) 
      return p;
      
    // global variable
 	unsigned int n = 50;
 			 int s = 150; 
 			 float w = 1./4;  
    
	// left part 
	if(xmin<_points[0][0]) {
		float a = xmin;
		float b = _points[0][0];
		float c = _points[0][1];
		n = 2*(b-a);
		p.moveTo(xmin,c);

		for(unsigned int j=0;j<n;j++){
			float x = a + ((j+0.)/(n-1))*(b-a);
			float y = c + s*sin(w*(x-a))*sin(w*(b-x));
			p.lineTo(x,y);
		}
	} else {
		p.moveTo(_points[0][0],_points[0][1]);
	}

    // draw function 
    for(unsigned int i=0;i<nbPts()-1;i++){	
        float a = _points[i][0];
      	float b = _points[i+1][0];
      	float c = _points[i][1];
      	float d = _points[i+1][1];
      	n = 2*(b-a);
      	// we are in interval [a;b] 
      
		for(unsigned int j=0;j<n;j++){
		float x = a + ((j+0.)/(n-1))*(b-a);
		float y = c+(d-c)*((x-a)/(b-a)) + s*sin(w*(x-a))*sin(w*(b-x));
		p.lineTo(x,y);
		}
    }

    // right part 
	if(xmax>_points[nbPts()-1][0]) {
		float a = _points[nbPts()-1][0];
		float b = xmax;
		float c = _points[nbPts()-1][1];
		n = 2*(b-a);
		for(unsigned int j=0;j<n;j++){
			float x = a + ((j+0.)/(n-1))*(b-a);
			float y = c + s*sin(w*(x-a))*sin(w*(b-x));
			p.lineTo(x,y);
		}
	}

    return p;
  }

  /* To maintain the curve already drawn */
  float evalAt(float x){
  	// special cases 
    if(empty()) return 0.0f;
    if(x<=_points[0][0]) return _points[0][1];
    if(x>=_points[nbPts()-1][0]) return _points[nbPts()-1][1];

    // linear interp
    for(unsigned int i=0;i<nbPts()-1;++i) {
      if(_points[i+1][0]>=x) {
	return _points[i][1]+(_points[i+1][1]-_points[i][1])*
	  ((x-_points[i][0])/(_points[i+1][0]-_points[i][0]));
      }
    }
    return _points[0][1];
  }
};


class Curve1DSinusConstructor : public Curve1DConstructor {
 public:
  virtual ~Curve1DSinusConstructor()                     {}
  virtual const QString type() const                      { return "SinusCurve";             }
  virtual Curve1D *create(const QString &name)            { return new Curve1DSinus(name);   }
  virtual Curve1D *create(Curve1D *c,const QString &name) { return new Curve1DSinus(c,name); }
};


#endif // CURVE_1D_SINUS_H
