#include "curve2D.h"
#include "curve2DWheel.h"
using namespace std;

void Curve2DWheel::circle(Vector2f center, float R, float frame){
  for (int i = 0; i < RESOLUTION_W; i++){
    float alpha = 2*M_PI*(float)(i+1)/(RESOLUTION_W);
    tab[i][0] = center[0] + cos(alpha)*R;
    tab[i][1] = center[1] + sin(alpha)*R;
  }
}

