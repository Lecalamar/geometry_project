#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include "curve2D.h"
#include "Matrice.h"
#include "curve2DSquare.h"
#include "animatedPoint.h"
#include <iostream> //a supprimer quand ca fonctionnera
#include <vector>
using namespace std;
	
	float Curve2DSquare::polyVal(Matrice p, float x){
		float sum = 0;
		for(int i=p.getNC();i>0;i--){
			sum = sum + p.get(0,p.getNC()-i)*pow(x,i-1);
		}
		return sum;
	}
	void Curve2DSquare::meanSquare(float frame){
		int n = nbPts();
		Matrice Bx(1,n);
		Matrice By(1,n);
		for(int i=0;i<n;i++){
			Vector2f pt = evalAnimPt(get(i),frame);
			Bx.put(0,i,pt[0]);
			By.put(0,i,pt[1]);
		}
		int d = n-1;
		Matrice t(n,1);
		for(int i=0;i<n;i++){
			t.put(i,0,(i+0.)/(n-1)); 
		}
		Matrice A(n,d+1);
		for(int i=0;i<n;i++){
			for(int j=0;j<d+1;j++){
				A.put(i,j,pow(t.get(i,0),d-j)); 
			}
		}
		/*cout << "Bx \n";
		Bx.display();
		cout << "By \n";
		By.display();*/
		Matrice Ux = (A.transpose().multiply(A)).solve(A.transpose().multiply(Bx.transpose()));
		Matrice Uy = (A.transpose().multiply(A)).solve(A.transpose().multiply(By.transpose()));
		/*cout << "Ux \n";
		Ux.transpose().display();
		cout << "Uy \n";
		Uy.transpose().display();*/
		for(int i=0;i<RESOLUTION_SQUARE;i++){
			Vector2f pt;
			pt[0] = polyVal(Ux.transpose(),(i+0.)/(RESOLUTION_SQUARE-1)); 
			pt[1] = polyVal(Uy.transpose(),(i+0.)/(RESOLUTION_SQUARE-1));
			tab[i] = pt; 
		}
	}
