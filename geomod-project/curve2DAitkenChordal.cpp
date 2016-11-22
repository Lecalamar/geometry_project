#include "curve2DAitkenChordal.h"
#include "parametrization.h"
#include <vector>
#include <cmath>

void Curve2DAitkenChordal::evalAitkenChordal(float frame){
  float *param =  new float[nbPts()];
  int L = ChordalTab(frame, param, nbPts(), this);
  ParamTab(param, L, nbPts()); /*Creates chordal parameters array*/
  for (int t = 1; t < RESOLUTION_A; t++){
    tab[t] = Aitken(nbPts()-1, 0, (float)t/(RESOLUTION_A-1), frame, param);
  }
}
