#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <iostream>
#include "mat.h"
#include "matIP.h"
int main(){
	using namespace cv;
	Mat img=imread("img_0000_abs_smooth.png");
	Mat img2=imread("img_0000.png");
	Mat dst,gr(img.rows,img.cols,CV_8UC1);
	pyrDown(img2,dst,Size(img.cols/2,img.rows/2));
	cvtColor(img2,dst,CV_BGR2GRAY);
	Image m;
	loadImage(dst,m,false);
	loadMat(gr,m,false);
	imshow("check",gr);imshow("img",dst);
	waitKey(0);
	return 0;
}
