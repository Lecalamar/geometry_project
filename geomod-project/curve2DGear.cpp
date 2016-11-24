#include "curve2DGear.h"

Vector2f Curve2DGear::M(float alpha, float teta, Vector2f P, float R, float frame){
  Vector2f center = evalAnimPt(get(nbPts()-2),frame);
  Vector2f P1;
  float gamma = alpha + teta; //It is a property from rotation, we can compose rotations (so add angles)
  P1[0] = center[0]+(P[0])*cos(gamma) + (R+P[1])*sin(gamma);
  P1[1] = center[1]-(P[0])*sin(gamma) + (R+P[1])*cos(gamma);
  return P1;
}
void Curve2DGear::gear(Vector2f center, float R, int sense, int N, float B, float frame){
  float alpha;
  float teta = 0;
  Vector2f P0 = {0,0};
  if (sense)
    {
      teta = 5*frame/R; //teta is the time angle
    }else{
      teta = -5*frame/R;
    }
  Vector2f P = evalAnimPt(get(nbPts()-1),frame);
  teta = teta + (-2*(center[1]<P[1])+1)*2*acos(sqrt(pow(center[0]-P[0]-R,2)+pow(P[1]-center[1],2))/(2*R)); //this is because we want the the gear follows the mouse, so we adapt 
  for(int i = 0; i < 4*N + 1; i += 4){ //There are sequences of 4 points
    for (int j = 0; j < 2; j++){
      alpha = M_PI/(2*N)*i; //alpha is the "geometric" angle
      tab[i][j] = M(alpha, teta, {0,-B}, R, frame)[j];
      tab[i + 1][j] = M(alpha+M_PI/(2*N), teta, {0,B}, R, frame)[j];
      tab[i + 2][j] = M(alpha+M_PI/N, teta, {0,B}, R, frame)[j];
      tab[i + 3][j] = M(alpha+3*M_PI/(2*N), teta, {0,-B}, R, frame)[j];
    }
  }
}
