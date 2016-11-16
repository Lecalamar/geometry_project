#include "curve2D.h"
#include "curve2DAitken.h"
#include <vector>

using namespace std;

float l2_norm(Vector2f P) {
  float res = 0.;
  for (int j = 0; j <= 1; j++) {
    res += pow(P[j],2);
  }
  return sqrt(res);
}

Vector2f Curve2DAitken::Aitken(int k,int i,float t, float frame){

  Vector2f P;
  if (k==0){
    P = evalAnimPt(get(i),frame);
  }else{
    for(int j = 0; j < 2; j++){
      float ti = (float)i/(nbPts()-1);
      float tik = (float)(i+k)/(nbPts()-1);
      P[j] = (Aitken(k-1,i,t,frame)[j]*(tik-t)+Aitken(k-1,i+1,t,frame)[j]*(t-ti))/(tik-ti);
    }
  }
  return P;
}

void Curve2DAitken::evalAitken(float frame){
  for (int t = 1; t < RESOLUTION_A; t++){
    tab[t] = Aitken(nbPts()-1, 0, (float)t/RESOLUTION_A, frame);
  }
}




