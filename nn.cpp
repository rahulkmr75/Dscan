#include <iostream>
#include <cmath>
#include "mat.h"
#include "fmat.cpp"
#define alpha1 1.0e-05
#define alpha2 1.0e-05
#define alpha3 1.0e-05
#define alpha4 1.0e-05
mat<double> **initNetwork(const int layers,const int *nodes){
	mat<double> **weights=new mat<double>*[layers];
	int i,j;
	weights[0]=new mat<double>(nodes[0],1);weights[0]->ones();
	for (i=1;i<layers;i++){
		weights[i]=new mat<double>(nodes[i],nodes[i-1]);
		weights[i]->zeros();
	}
	weights[3]->ones();
	std::cout<<"network initialized\n";
	return weights;
}
mat<double> **initBias(const int layers,const int *nodes){
	//only the wo hidden layers have a bias
	mat<double> **bias=new mat<double>*[layers];
	for(int i=0;i<layers;i++){
		bias[i]=new mat<double>(nodes[i],1);
		bias[i]->zeros();
	}
	cout<<"bias initalized\n";
	return bias;
}
void activate(mat<double> *out){
	int i,j;
	for (i=0;i<out->row;i++){
		for(j=0;j<out->col;j++)out->a[i][j]=1/(1+exp(-1*out->a[i][j]));
	}
}
void computeOutputs(mat<double> **weights,mat<double> **out,mat<double> **bias,mat<int> &x,int layers){
	//the first layer make the input vector available to all the nodes
	//in the next layer
	correlate<double,int,double>(*(weights[0]),x,*(out[0]));
	int i;
	for(i=1;i<layers;i++){
		multiply<double,double,double>(*(weights[i]),*(out[i-1]),*(out[i]));
		add<double,double,double>(*(out[i]),*(bias[i]),*(out[i]));
		if(i==2){
			activate(out[2]);
		}
	}	
}
void backProp(mat<double> **weights,mat<double> **bias,mat<double> **out,mat<int> &x,double error){
	//b3=b3-alpha1*(a4-y)(a3.(1-a3))
	mat<double>a3dot_(255,1);
	mat<double>one_(255,1);
	mat<double>one_a3(255,1);
	one_.ones();
	subtract<double,double,double>(one_,*(out[2]),one_a3);
	correlate<double,double,double>(*(out[2]),one_a3,a3dot_);
	a3dot_.scale(alpha1*error);
	subtract<double,double,double>(*(bias[2]),a3dot_,*(bias[2]));
	
	//w3=w3-alpha2*(a4-y)((a3dot_)*a2_T)
	mat<double>a3dot_k(255,1);
	//a3dot_k=a3dot_*(alpha2/alpha1);
	a3dot_.copy<double>(a3dot_k);a3dot_k.scale(alpha2/alpha1);
	mat<double>a2_T(out[1]->col,out[1]->row);
	transpose<double,double>(*(out[1]),a2_T);
	mat<double>desw3(255,64);
	multiply<double,double,double>(a3dot_k,a2_T,desw3);	
	subtract<double,double,double>(*(weights[2]),desw3,*(weights[2]));
	
	//b2=b2-alpha3(a4-y)(w3_T*a3dot_)
	mat<double> desb2(64,1);
	mat<double> w3_T(64,255);
	transpose<double,double>(*(weights[2]),w3_T);
	multiply<double,double,double>(w3_T,a3dot_,desb2);
	desb2.scale(alpha3/alpha2);
	subtract<double,double,double>(*(bias[1]),desb2,*(bias[1]));

	//w2=w2-alpha4(w3T*a3dot_*x_T)
	mat<int> x_T(x.col,x.row);
	transpose<int,int>(x,x_T);
	mat<double> desw2(weights[1]->row,weights[1]->col);
	multiply<double,int,double>(desb2,x_T,desw2);
	desw2.scale(alpha4/alpha3);
	subtract<double,double,double>(*(weights[1]),desw2,*(weights[1]));
	
	//freeing the matrix
	desw2.free();x_T.free();w3_T.free();desb2.free();desw3.free();a2_T.free();
	a3dot_k.free();one_a3.free();one_.free();a3dot_.free();
}
void writeWeights(mat<double> **weights,mat<double> **bias,char **fileweights,char **filebias,int layers){
	for(int i=0;i<layers;i++){
		writemat<double>(*(weights[i]),fileweights[i]);
		writemat<double>(*(bias[i]),filebias[i]);
	}
}
//it loads the weights in the matrix object
//and returns mat<double> **
void loadWeights(mat<double> **weights,mat<double> **bias,char **fileweights,char **filebias,int layers){
	int i;
	for(i=0;i<layers;i++){
		readmat<double>(*(weights[i]),fileweights[i]);
		readmat<double>(*(bias[i]),filebias[i]);
	}
}
