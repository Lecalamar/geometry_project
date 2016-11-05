#include "curve2D.h"
#include "curve2DHermite1.h"
#include <vector>
#include <cmath>
using namespace std;

vector<float> Curve2DHermite1::H(float t){
  vector<float> tab;
  float H0 = 2*t*t*t-3*t*t+1;
  float H1 = -2*t*t*t+3*t*t;
  float H2 = t*t*t-2*t*t+t;
  float H3 = t*t*t - t*t;
  tab.push_back(H0);
  tab.push_back(H1);
  tab.push_back(H2);
  tab.push_back(H3);
  return tab;
}

Vector2f Curve2DHermite1::coeff(float t, int i, float frame){
  Vector2f C;
  Vector2f P1 = evalAnimPt(get(i),frame);
  Vector2f P2 = evalAnimPt(get(i+1),frame);
  Vector2f D1;
  Vector2f D2;
  float L1; //It is the distance between the points around D1
  float L2;
  if (i == 0){ //derivatives for first point
    L1 = sqrt(pow(P2[1]-P1[1],2)+pow(P2[0]-P1[0],2));
    L2 = sqrt(pow(evalAnimPt(get(i+2),frame)[1]-P1[1],2)+pow(P1[0]-evalAnimPt(get(i+2),frame)[0],2));
    D1[1] = (P2[1]-P1[1])/(P2[0]-P1[0])*L1;
    D1[0] = L1;
    D2[1] = 0.5*((evalAnimPt(get(2),frame)[1]-P2[1])/(evalAnimPt(get(2),frame)[0]-P2[0])+(P2[1]-P1[1])/(P2[0]-P1[0]))*L2;
    D2[0] = L2;
  }else if(i != 0 && i == (int)nbPts() - 2){ //derivatives for last point
    L1 = sqrt(pow(evalAnimPt(get(i-1),frame)[1]-P2[1],2)+pow(evalAnimPt(get(i-1),frame)[0]-P2[0],2));
    L2 = sqrt(pow(P2[1]-P1[1],2)+pow(P2[0]-P1[0],2));
    D1[1] = 0.5*((evalAnimPt(get(i-1),frame)[1]-P1[1])/(evalAnimPt(get(i-1),frame)[0]-P1[0])+(P2[1]-P1[1])/(P2[0]-P1[0]))*L1;
    D1[0] = L1;
    D2[1] = (P2[1]-P1[1])/(P2[0]-P1[0])*L2;
    D2[0] = L2;
  }else{ //derivatives for other points
    L1 = sqrt(pow(evalAnimPt(get(i-1),frame)[1]-P2[1],2)+pow(evalAnimPt(get(i-1),frame)[0]-P2[0],2));
    L2 = sqrt(pow(P1[1]-evalAnimPt(get(i+2),frame)[1],2)+pow(P1[0]-evalAnimPt(get(i+2),frame)[0],2));
    D1[1] = 0.5*((evalAnimPt(get(i-1),frame)[1]-P1[1])/(evalAnimPt(get(i-1),frame)[0]-P1[0])+(P2[1]-P1[1])/(P2[0]-P1[0]))*L1;
    D1[0] = L1;
    D2[1] = 0.5*((evalAnimPt(get(i+2),frame)[1]-P2[1])/(evalAnimPt(get(i+2),frame)[0]-P2[0])+(P2[1]-P1[1])/(P2[0]-P1[0]))*L2;
    D2[0] = L2;
  }
  for(int j = 0; j < 2; j++){
    C[j] = H(t)[0]*P1[j]+H(t)[1]*P2[j]+H(t)[2]*D1[j]+H(t)[3]*D2[j];
  }
  return C;
}

void Curve2DHermite1::evalHermite1(int i, float frame){
  for (int t = 0; t < RESOLUTION_H1; t++){
    tab[t] = coeff((float)t/(RESOLUTION_H1-1), i, frame);  
  }
}


