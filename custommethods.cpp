#include "mat.h"
#include <fstream>
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
char **getWFileNames(char *name){
	ifstream file(name);
	char **wfiles=new char *[4];
	for(int i=0;i<4;i++){
		wfiles[i]=new char[30];
		file>>wfiles[i];
	}	
	return wfiles;
}
char **getBFileNames(char *name){
	ifstream file(name);
	char **bfiles=new char *[4];
	for(int i=0;i<8;i++){
		bfiles[i-4]=new char[30];
		if(i>3)file>>bfiles[i-4];
	}
	return bfiles;
}
void makeOutput(mat<double> **output){
	output[0]=new mat<double>(750,1);
	output[1]=new mat<double>(64,1);
	output[2]=new mat<double>(255,1);
	output[3]=new mat<double>(1,1);
}	
