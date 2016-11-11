#include "curve2D.h"
#include "curve2DHermiteClosed.h"
#include <vector>
#include <cmath>
using namespace std;

vector<float> Curve2DHermiteClosed::H(float t){
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

float Curve2DHermiteClosed::distance(Vector2f P1, Vector2f P2){
  return sqrt(pow(P2[1]-P1[1],2)+pow(P2[0]-P1[0],2));
}

float Curve2DHermiteClosed::projection(Vector2f P1, Vector2f P2, Vector2f P3){
  return abs((P2[0]-P1[0])*(P3[0]-P1[0])+(P2[1]-P1[1])*(P3[1]-P1[1]))/distance(P1,P3);
}

float Curve2DHermiteClosed::tangent(Vector2f P1, Vector2f P2){
  return fmax(fmin((P2[1]-P1[1])/(P2[0]-P1[0]),10),-10); //we bound the derivative to limit the weight
}

Vector2f Curve2DHermiteClosed::coeff(float t, int i, float frame){
  Vector2f C;
  Vector2f P0;
  Vector2f P1 = evalAnimPt(get(i),frame);
  Vector2f P2;
  Vector2f P3;
  Vector2f D1;
  Vector2f D2;
  float L1; //It is the distance between the points around D1
  float L2;
  float L11;
  float L12;
  float L21;
  float L22;
  int p = 1;
  int l = 1;
  int m = 1; //m, p, and l change the sens of the derivative
  if (i!=0 && i == (int)nbPts() - 1){
    P3 = evalAnimPt(get(1),frame);
    P2 = evalAnimPt(get(0),frame);
    P0 = evalAnimPt(get(i-1),frame);

  } else if (i == 0){ //derivatives for first point

    P2 = evalAnimPt(get(i+1),frame);
    P3 = evalAnimPt(get(i+2),frame);
    P0 = evalAnimPt(get(nbPts()-1),frame);

  }else if(i != 0 && i == (int)nbPts() - 2){ //derivatives for last point
    
    P2 = evalAnimPt(get(i+1),frame);
    P0 = evalAnimPt(get(i-1),frame);
    P3 =  evalAnimPt(get(0),frame);
  }else{ //derivatives for other points
    
    P2 = evalAnimPt(get(i+1),frame);
    P0 = evalAnimPt(get(i-1),frame);
    P3 = evalAnimPt(get(i+2),frame); 
  }
  if(P1[0]>P2[0]){
      m = -1;
    }
    if(P1[0]<P0[0]){
      l = -1;
    }
    if (P2[0]>P3[0]){
      p = -1;
    }
    L1 = distance(P0,P2);
    L11 = projection(P0,P1,P2);
    L12 = L1-L11;
    L2 = distance(P3,P1);
    L21 = projection(P1,P2,P3);
    L22 = L2-L21;
    
    D1[1] = l*L11*tangent(P0,P1)+m*L12*tangent(P2,P1); 
    D1[0] = l*L11+m*L12;
    
    D2[1] = p*L22*tangent(P3,P2)+m*L21*tangent(P2,P1);
    D2[0] = m*L21 + p*L22;
    
  for(int j = 0; j < 2; j++){
    C[j] = H(t)[0]*P1[j]+H(t)[1]*P2[j]+H(t)[2]*D1[j]+H(t)[3]*D2[j];
  }
  return C;
}

void Curve2DHermiteClosed::evalHermiteClosed(int i, float frame){
  for (int t = 0; t < RESOLUTION_HC; t++){
    tab[t] = coeff((float)t/(RESOLUTION_HC-1), i, frame);  
  }
}


