#include "Matrice.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 
#include <cmath> 
#include "Matrice.h"
#include <iostream> //a supprimer quand ca fonctionnera
#include <vector>
using namespace std;
	Matrice::Matrice(int a, int b){
		nl = a;
		nc = b;
		tab = (float**)malloc(nl*sizeof(*tab));
		for(int i=0 ; i<nl; i++){
 			tab[i] =(float*)malloc(nc*sizeof(float));
 		}
	}
	int Matrice::getNL(){
		return nl;
	}
	int Matrice::getNC(){
		return nc;
	}
	void Matrice::put(int i, int j, float f){
		if(i<nl && j<nc){
			tab[i][j] = f;
		}else{
			cerr << "Index out of bounds.";
		}
	}
	float Matrice::get(int i, int j){
			return tab[i][j];
	}
	void Matrice::display(){
		for(int i=0;i<nl;i++){
			for(int j=0;j<nc;j++){
				cout << tab[i][j] << " " ;
			}
			cout << "\n" ;
		}
	}
	Matrice Matrice::transpose(){
		Matrice ret(nc,nl);
		for(int i=0;i<nl;i++){
			for(int j=0;j<nc;j++){
				ret.tab[j][i] = tab[i][j];
			}
		}
		return ret;
	}
	/* We suppose that A is inversible */
	Matrice Matrice::solve(Matrice b){
			//float eps = 1.0e-15;
			for(int i=0;i<nl;i++){
				float pivotI = tab[i][i];
				for(int j=i+1;j<nl;j++){
					float coef = tab[i][i]/tab[j][i];
					float pivotJ = tab[j][i];
					//cout << "coef : " << coef << "\n";
					for(int k=i;k<nc;k++){
						//tab[j][k] = tab[i][k]-coef*tab[j][k];
							//float c = tab[i][k]-coef*tab[j][k];
							/*if(abs(tab[j][k])<eps){
								tab[j][k]=0;
							}*/
						tab[j][k] = (tab[i][k]*pivotJ) - (pivotI*tab[j][k]);

					}
					//b.tab[j][0] = b.tab[i][0]-coef*b.tab[j][0];
					b.tab[j][0] = (b.tab[i][0]*pivotJ) - (pivotI*b.tab[j][0]);
				}
				if(nl>=3)
					this->display();
					b.display();
			}
			
			Matrice ret(nl,1);
			for(int i=nl-1;i>=0;i--){
				float sum = 0;
				for(int j=i+1;j<nc;j++){
					sum = sum + tab[i][j]*ret.tab[j][0];
				}
				ret.tab[i][0] = (b.tab[i][0]-sum)/tab[i][i];
			}
			
			return ret;
	}
	Matrice Matrice::multiply(Matrice A){
			Matrice ret(nl,A.nc);
			for (int i=0;i<nl;i++){
				for(int j=0;j<A.nc;j++){
					float sum = 0;
					for(int k=0;k<nc;k++){
						sum = sum + tab[i][k]*A.tab[k][j];
					}
					ret.tab[i][j] = sum;
				}
			}
			return ret;
	}
