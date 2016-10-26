#include "curve2D.h"
#include "curve2DBezier.h"
#include <vector>
#include <cmath> /*pow and sqrt*/
using namespace std;

int l2_norm(Vector2f P) {
  int res = 0;
  for (int j = 0; j <= 1; j++) {
    res += pow(P[j],2);
  }
  return sqrt(res);
}

Vector2f Curve2DBezier::Casteljau(int k,int i,float t, float frame){

  Vector2f b;
  if (k==0){
    b =  evalAnimPt(get(i),frame);;
  }else {
    for(int j = 0; j<2; j++){ /*two coordinates to fill*/
      b[j] = (1-t)*Casteljau(k-1,i,t,frame)[j] + t*Casteljau(k-1,i+1,t,frame)[j];
    }
  }
  return b;
}

void Curve2DBezier::evalCasteljau(float frame){
  for (int t = 1; t < RESOLUTION_B; t++){
    tab[t] = Casteljau(nbPts()-1, 0, (float)t/RESOLUTION_B, frame);
  }
}

void Curve2DBezier::evalChord(float frame) {
  int t[nbPts()];
  Vector2f P_i0, P_i1;
  int L = 0;
  for (unsigned int i = 1; i < nbPts(); i++) {
    P_i1 = evalAnimPt(get(i),frame);
    P_i0 = evalAnimPt(get(i-1),frame);
    t[i] = l2_norm(P_i1 - P_i0);
    L += t[i];
  }
  /*t_0 = a = 0*/
  t[0] = 0;
  for (unsigned int i = 1; i < nbPts(); i++){
    t[i] = t[i-1] + (float)t[i]/L;
  }
}


                                                                                

