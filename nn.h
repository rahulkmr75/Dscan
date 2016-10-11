#include <iostream>
#include "mat.h"
#include "fmat.h"
#ifndef NETWORK_H_
#define NETWORK_H_
/************************************************************************
*	This file contains functions related to a fully connected 	*	
*	artificial neural  network  the   dependecies are  mat.h  	*
*	and math.h.                                               	*
*	The first layers takes the input vector and has only one  	*
*	weight per node, the  nodes of the following layers have  	*
*	weights with  dimension  equal to no. of   nodes in   the 	*
*	previous layer.						 	*
*	The weight vector are rows in 2D matrix.			*
*	Bias has  not  been  implicitly    provide so one has to 	*
*	explicitly provide the bias.					*
*************************************************************************/

/*
the init network function initializes the weight marix to zero
has one weight per node for the first layer, the nodes of the following layer
have weights with dimension equal to no.of nodes in the previous layer.
one can explicitly change the weights by calling zeros, ones , or initialize
fuction of the mat instance.
*/	

mat<double>** initNetwork(const int layers,const int *nodes){
	mat<double> **weights=new mat<double>*[layers];
	int i,j;
	weights[0]=new mat<double>(nodes[0],1);weights[0]->ones();
	for (i=1;i<layers;i++){
		weights[i]=new mat<double>(nodes[i],nodes[i-1]);
		weights[i]->zeros();
	}
	return weights;
}
void trainlayer(){};

//this function write the weights to txt file
//in the order of the matrix present in 
//mat<double> **weights
void writeWeights(mat<double> **weights,int layers){
	char name[15]="layer_01.txt";
	for(int i=1;i<=layers;i++){
		name[7]=48+i;
		writemat(*(weights[i-1]),name);
	}
}
//it loads the weights in the matrix object
//and returns mat<double> **
void loadWeights(char **files){
}
#endif
