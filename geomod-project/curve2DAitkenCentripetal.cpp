#include "curve2DAitkenCentripetal.h"
#include "parametrization.h"
#include <vector>
#include <cmath>

void Curve2DAitkenCentripetal::evalAitkenCentripetal(float frame){
  float *param =  new float[nbPts()];
  int L = CentripetalTab(frame, param, nbPts(), this);
  ParamTab(param, L, nbPts()); /* Creates centripetal parameter array */
  for (int t = 1; t < RESOLUTION_A; t++){
    tab[t] = Aitken(nbPts()-1, 0, (float)t/RESOLUTION_A, frame, param);
  }
}
