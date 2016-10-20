#include "curve2D.h"
#include "curve2DBezier.h"

using namespace std;

Vector2f Curve2DBezier::Casteljau(int k,int i,float t,float frame){

Vector2f b;
		if (k==0){
			b = evalAnimPt(get(i),frame);
		}else{
			for(int j = 0; j<2; j++){
			  //	b[j] = (1-t)*Casteljau(matrix,k-1,i,t)[j] + t*Casteljau(matrix,k-1,i+1,t)[j];
			}
		}
		return b;
}
