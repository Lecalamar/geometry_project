#include "curve2D.h"
#include "curve2DBezier.h"
#include <vector>
using namespace std;

Vector2f Curve2DBezier::Casteljau(int k,int i,float t, float frame){

  Vector2f b;
  if (k==0){
    b =  evalAnimPt(get(i),frame);
  }else{
    for(int j = 0; j < 2; j++){
      b[j] = (1-t)*Casteljau(k-1,i,t,frame)[j] + t*Casteljau(k-1,i+1,t,frame)[j];
    }
  }
  return b;
}

void Curve2DBezier::evalCasteljau(float frame){
  for (int t = 1; t < RESOLUTION_B; t++){
    tab[t] = Casteljau(nbPts()-1, 0, (float)t/(RESOLUTION_B-1), frame);
  }
}


