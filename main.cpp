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
	
	//file that contains the index of the rgb-d data
	ifstream rgb_f("rgb_files.txt");
	ifstream depth_f("depth_files.txt");
	
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
	//writeWeights(weights,bias,listw,listb,4);
	//return 0;

	
	//assigning the saved data
	mat<double> **output=new mat<double> *[4];
	makeOutput(output);
	
	//cout<<bias[0]->row<<bias[0]->col;
	
	//name says it all ;-p
	Image m_imgrgb1,m_imgd1,m_imgrgb2,m_imgrgb3;
	Mat imgrgb2,imgrgb3;

	char namergb[100],namedepth[100];
	while(rgb_f>>namergb && depth_f>>namedepth){
		Mat imgrgb1=imread(namergb);
		Mat imgd1=imread(namedepth);
		imshow("depth",imgd1);
		cvtColor(imgd1,imgd1,CV_BGR2GRAY);
		equalizeHist(imgd1,imgd1);
		imshow("bgr",imgrgb1);
		imshow("gray",imgd1);
		char c=waitKey(0);
		cout<<c;
		return 0;
		
		//reducing the rgb images
		pyrDown(imgrgb1,imgrgb2,Size(imgrgb1.cols/2,imgrgb1.rows/2));
		pyrDown(imgrgb2,imgrgb3,Size(imgrgb2.cols/2,imgrgb2.rows/2));
		
		//loading the images to my matrix
		loadImage(imgrgb1,m_imgrgb1,true);
		loadImage(imgrgb2,m_imgrgb2,true);
		loadImage(imgrgb3,m_imgrgb3,true);
		loadImage(imgd1,m_imgd1,false);
		cout<<"loaded image : "<<namergb<<"\n";
		
		//computation part
		mat<int> x(750,1,true);
		for(int i=20;i<460;i++){
			for(int j=20;j<620;j++){
				//making a vector for input 
				makeVector(m_imgrgb1,m_imgrgb2,m_imgrgb3,x,i,j);
				
				computeOutputs(weights,output,bias,x,4);
				//output[1]->scale(0.00001);			
				//output[0]->print();
				double err=output[3]->a[0][0]-m_imgd1.ch0.a[i][j];
				backProp(weights,bias,output,x,err);
				cout<<"error : "<<err<<"\n";
			}
		cout<<"computation done on row : "<<i<<"\n";
		writeWeights(weights,bias,listw,listb,4);
		}
		cout<<"stochastic descent completed on image : "<<namergb<<"\n";
		cout<<"writing files to webi/layer_0....\n";
		cout<<"writing files to webi/bias_0.....\n";
		writeWeights(weights,bias,listw,listb,4);
		cout<<"Done writing\nloading next image\n";			
	}
	return 0;
}
