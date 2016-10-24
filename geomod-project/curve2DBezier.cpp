#include "curve2D.h"
#include "curve2DBezier.h"
#include <iostream> //a supprimer quand ca fonctionnera
#include <vector>
using namespace std;

Vector2f Curve2DBezier::Casteljau(int k,int i,float t,float frame){

  Vector2f b;
  if (k==0){
    b = cpts[i];
    //b = evalAnimPt(get(i),frame);
    }else {
      for(int j = 0; j<2; j++){
	  b[j] = (1-t)*Casteljau(k-1,i,t, frame)[j] + t*Casteljau(k-1,i+1,t, frame)[j];
	}
    }
  return b;
}

void Curve2DBezier::evalCasteljau(float frame){
  for (int t = 0; t < RESOLUTION; t++){
    tab[t] = Casteljau(nbPts()-1, 0, t/RESOLUTION, frame);
  }
}
//a supprimer quand ca fonctionnera
void Curve2DBezier::affiche(){
  for(unsigned int i=1;i<nbPts();i++){
    cout << cpts[i][1] << endl;
  }
  cout << "------" << endl;
}

void Curve2DBezier::parse(float frame){
  for(unsigned int i=0;i<nbPts();i++) {
    cpts.push_back(evalAnimPt(get(i),frame)); 
    }
}
