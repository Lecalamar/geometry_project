#include "curve2D.h"
#include "curve2DAitkenChordal.h"
#include "parametrization.h"
#include <vector>
#include <cmath>

Vector2f Curve2DAitkenChordal::AitkenChordal(int k,int i,float t, float frame, float *param){

  Vector2f P;
  if (k==0){
    P = evalAnimPt(get(i),frame);
  }else{
    for(int j = 0; j < 2; j++){
      float ti = param[i];
      float tik = param[i+k];
      P[j] = (AitkenChordal(k-1,i,t,frame,param)[j]*(tik-t)+AitkenChordal(k-1,i+1,t,frame,param)[j]*(t-ti))/(tik-ti);
    }
  }
  return P;
}

void Curve2DAitkenChordal::evalAitkenChordal(float frame){
  float *param =  new float[nbPts()];
  int L = DistanceTab(frame, param, nbPts(), this);
  ChordalParam(param, L, nbPts());
  for (int t = 1; t < RESOLUTION_A; t++){
    tab[t] = AitkenChordal(nbPts()-1, 0, (float)t/RESOLUTION_A, frame, param);
  }
}
