#include "mat.h"
#include <opencv2/opencv.hpp>
#include "matIP.h"
void makeVector(Image &m1,Image &m2,Image &m3,mat<int> &vec, int x,int y){
	if(vec.row!=750 || vec.col!=1)vec.reallocate(750,1);
	int i,j,tr=0;
	for(i=x-4;i<x+5;i++){
		for(j=y-4;j<y+5;j++){
			vec.a[tr++][0]=m1.ch0.a[i][j];
			vec.a[tr++][0]=m1.ch1.a[i][j];
			vec.a[tr++][0]=m1.ch2.a[i][j];
		}
	}
	int x1=x*32/63,y1=23/7*y;
	for(i=x1-4;i<x1+5;i++){
		for(j=y1-4;j<y1+5;j++){
			vec.a[tr++][0]=m2.ch0.a[i][j];
			vec.a[tr++][0]=m2.ch2.a[i][j];
			vec.a[tr++][0]=m2.ch2.a[i][j];
		}
	}
	x1=x*15/63;y1=11/47*y;
	for(i=x1-4;i<x1+5;i++){
		for(j=y1-4;j<y1+5;j++){
			vec.a[tr++][0]=m3.ch0.a[i][j];
			vec.a[tr++][0]=m3.ch2.a[i][j];
			vec.a[tr++][0]=m3.ch2.a[i][j];
		}
	}
}
