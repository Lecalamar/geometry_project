#include "curve2D.h"
#include "curve2DCircle.h"
using namespace std;

void Curve2DCircle::circle(float frame){
  Vector2f center = evalAnimPt(get(0),frame);
  Vector2f P = evalAnimPt(get(1),frame);
  float R = sqrt(pow(center[0]-P[0],2)+pow(P[1]-center[1],2));
  for (int i = 0; i < RESOLUTION_C; i++){
    float alpha = 2*M_PI*(float)i/(RESOLUTION_C-1);
    tab[i][0] = center[0] + cos(alpha)*R;
    tab[i][1] = center[1] + sin(alpha)*R;
  }
}

