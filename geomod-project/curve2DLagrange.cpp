#include "curve2D.h"
#include "curve2DLagrange.h"
#include "animatedPoint.h"
#include <iostream> //a supprimer quand ca fonctionnera
#include <vector>
using namespace std;

float Curve2DLagrange::evalPoly(int i, float x, float frame){
	float prod = 1;
	float xi = evalAnimPt(get(i),frame)[0];
	for(unsigned int j=0; j<nbPts(); j++){
		if(j != (unsigned int)i){
			float xj = evalAnimPt(get(j),frame)[0];
			prod = prod*((x-xj)/(xi-xj));
		}
	}
	return prod;
}

void Curve2DLagrange::lagrange(float frame){
	/* calcul du minimum et du maximum */
	float x0 = 10000;
	float xn = 0;
	for(unsigned int i=0;i<nbPts();i++){
		if(x0 > evalAnimPt(get(i),frame)[0]){
			x0 = evalAnimPt(get(i),frame)[0];
		}
		if(xn < evalAnimPt(get(i),frame)[0]){
			xn = evalAnimPt(get(i),frame)[0];
		}	
	}
	float x = x0;
	for(int i=1; i<5*RESOLUTION; i++){
		float som = 0;
		for(unsigned int j=0; j<nbPts(); j++){
			som = som + evalAnimPt(get(j),frame)[1]*evalPoly(j, x, frame);
		}
		Vector2f vect(x,som);
		tab[i] = vect;
		x = x0+i*((xn-x0)/(5*RESOLUTION-2));
	}
}
