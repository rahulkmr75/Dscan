#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include "mat.h"
#include "matIP.h"
#include "nn.h"
#include "custommethods.h"
#include "math.h"
int main(){
	using namespace std;
	using namespace cv;
	int n=0;
	
	//string array data that stores the name of weight and bias file
	char **listw=getWFileNames("webi/wfiles.txt");
	char **listb=getBFileNames("webi/bfiles.txt");

	//cout<<listw[0]<<listw[1]<<listw[2]<<listw[3];
	//initializes the weights and bias with 0's and 1's
	int *nodes=new int[4];
	nodes[0]=750;nodes[1]=64;nodes[2]=255;nodes[3]=1;
	mat<double> **weights=initNetwork(4,nodes);
	mat<double> **bias=initBias(4,nodes);
	loadWeights(weights,bias,listw,listb,4);

	
	//assigning the saved data
	mat<double> **output=new mat<double> *[4];
	makeOutput(output);
	
	//cout<<bias[0]->row<<bias[0]->col;
	
	//name says it all ;-p
	Image m_imgrgb1,m_imgd1,m_imgrgb2,m_imgrgb3;
	Mat imgrgb2,imgrgb3;

	//char namergb[100],namedepth[100];
	Mat imgrgb1=imread("test2.jpg");
	Size size(640,480);
	resize(imgrgb1,imgrgb1,size);
	Mat depth=imgrgb1.clone();
		
	//reducing the rgb images
	pyrDown(imgrgb1,imgrgb2,Size(imgrgb1.cols/2,imgrgb1.rows/2));
	pyrDown(imgrgb2,imgrgb3,Size(imgrgb2.cols/2,imgrgb2.rows/2));
		
	//loading the images to my matrix
	loadImage(imgrgb1,m_imgrgb1,true);
	loadImage(imgrgb2,m_imgrgb2,true);
	loadImage(imgrgb3,m_imgrgb3,true);
	loadImage(depth,m_imgd1,true);
	cout<<"loaded image : "<<"\n";
	
	//computation part
	mat<int> x(750,1,true);
	for(int i=20;i<460;i++){
		for(int j=20;j<620;j++){
			//making a vector for input 
			makeVector(m_imgrgb1,m_imgrgb2,m_imgrgb3,x,i,j);
			
			computeOutputs(weights,output,bias,x,4);
			if(output[3]->a[0][0]>255)output[3]->a[0][0]=255;
			else if(output[3]->a[0][0]<0)output[3]->a[0][0]=0;
			m_imgd1.ch0.a[i][j]=m_imgd1.ch1.a[i][j]=m_imgd1.ch2.a[i][j]=output[3]->a[0][0];
			break;
    		}
	cout<<"computation done on row : "<<i<<"\n";
	break;
	}
	loadMat(depth,m_imgd1,true);
	namedWindow("depth");
	cvtColor(depth,depth,CV_BGR2GRAY);
	equalizeHist(depth,depth);
	imshow("depth",depth);
	imshow("org1",imgrgb1);
	imshow("org2",imgrgb2);
	imshow("org3",imgrgb3);
	waitKey(0);
	for(int i=0;i<4;i++){
	    weights[i]->free();
	    bias[i]->free();
	    output[i]->free();
	}
	freeImage(m_imgrgb1);
	freeImage(m_imgrgb2);
	freeImage(m_imgrgb3);
	freeImage(m_imgd1);
	delete nodes;

	return 0;
}
