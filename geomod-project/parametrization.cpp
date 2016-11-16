#include "parametrization.h"
#include <cmath>

float l2_norm(Vector2f P) {
  float res = 0.;
  for (int j = 0; j <= 1; j++) {
    res += pow(P[j],2);
  }
  return sqrt(res);
}

int ChordalTab(float frame, float *param, unsigned int n, Curve2D *c) {
  Vector2f P_i0, P_i1;
  int L = 0;
  for (unsigned int i = 1; i < n; i++) {
    P_i1 = c->evalAnimPt(c->get(i),frame);
    P_i0 = c->evalAnimPt(c->get(i-1),frame);
    param[i] = l2_norm(P_i1 - P_i0);
    L += param[i];
  }
  return L;
}

int CentripetalTab(float frame, float *param, unsigned int n, Curve2D *c) {
  Vector2f P_i0, P_i1;
  int L = 0;
  for (unsigned int i = 1; i < n; i++) {
    P_i1 = c->evalAnimPt(c->get(i),frame);
    P_i0 = c->evalAnimPt(c->get(i-1),frame);
    param[i] = sqrt(l2_norm(P_i1 - P_i0));
    L += param[i];
  }
  return L;
}

void ParamTab(float *param, int L, unsigned int n) {
  /*t_0 = a = 0*/
  param[0] = 0;
  for (unsigned int i = 1; i < n; i++){
    param[i] = param[i-1] + param[i]/L;
  }
}


