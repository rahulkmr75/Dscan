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
CAUTION - be careful while using this method you might loose the trained data
*/	

mat<double> **initNetwork(const int layers,const int *nodes);
mat<double> **initBias(const int layers,const int *nodes){

//this method computes the ouput vector for give input ,weights, bias	
void computeOutputs(mat<double> **weights,mat<double> **out,mat<double> **bias,mat<int> &x,int layers);

//it writes the matrix and bias to the file names given
void writeWeights(mat<double> **weights,mat<double> **bias,char **fileweights,char **fileweights,int layers);

//it loads  the learned data from the file
void loadWeights(mat<double> **weights,mat<double> **bias,char **fileweights,char **filebias,int layers);
	
#endif
