#ifndef _PARAMETRIZATION_H_
#define _PARAMETRIZATION_H_

#include "curve2D.h"
#include <vector>

using namespace std;

float l2_norm(Vector2f P);
int ChordalTab(float frame, float *param, unsigned int n, Curve2D *c);
int CentripetalTab(float frame, float *param, unsigned int n, Curve2D *c);
void ParamTab(float *param, int L, unsigned int n);


#endif
