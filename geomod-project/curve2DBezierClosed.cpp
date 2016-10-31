#include "curve2D.h"
#include "curve2DBezierClosed.h"
#include <vector>
using namespace std;

Vector2f Curve2DBezierClosed::CasteljauClosed(int k,int i,float t, float frame){

  Vector2f b;
  if (k==0){
    if ((unsigned int)i == nbPts()){
      b = evalAnimPt(get(0),frame);
    } else {
      b = evalAnimPt(get(i),frame);
    }
  }else{
    for(int j = 0; j < 2; j++){
      b[j] = (1-t)*CasteljauClosed(k-1,i,t,frame)[j] + t*CasteljauClosed(k-1,i+1,t,frame)[j];
    }
  }
  return b;
}

void Curve2DBezierClosed::evalCasteljauClosed(float frame){
  for (int t = 1; t < RESOLUTION_BC; t++){
    tab[t] = CasteljauClosed(nbPts(), 0, (float)t/RESOLUTION_BC, frame);
  }
}


