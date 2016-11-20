#include "curve2D.h"
#include "curve2DAitken.h"
#include <vector>

Vector2f Curve2DAitken::Aitken(int k,int i,float t, float frame, float *param){

  Vector2f P;
  if (k==0){
    P = evalAnimPt(get(i),frame);
  }else{
    for(int j = 0; j < 2; j++){
      float ti = param[i];
      float tik = param[i+k];
      P[j] = (Aitken(k-1,i,t,frame, param)[j]*(tik-t)+Aitken(k-1,i+1,t,frame, param)[j]*(t-ti))/(tik-ti);
    }
  }
  return P;
}

void Curve2DAitken::evalAitken(float frame){
  float *param = new float[nbPts()];
  for (unsigned int i = 0; i < nbPts(); i++)
    param[i] = (float)i/(nbPts()-1);
  for (int t = 1; t < RESOLUTION_A; t++){
    tab[t] = Aitken(nbPts()-1, 0, (float)t/(RESOLUTION_A-1), frame, param);
  }
}




