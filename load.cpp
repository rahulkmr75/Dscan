#include <opencv2/opencv.hpp>
#include <iostream>
#include "mat.h"
#include "matIP.cpp"
int main(){
	using namespace cv;
	Mat img=imread("img_0000_abs_smooth.png");
	namedWindow("original",1);
	imshow("original",img);
	Vec3b col=img.at<Vec3b>(Point(10,10));
	unsigned char r,g,b;
	r=col.val[0];
	g=col.val[1];
	b=col.val[2];
	std::cout<<(int)r<<g<<b<<img.rows<<img.cols<<std::endl;
	Image m;
	loadImage(img,m,true);
	m.ch1.print();
	waitKey(0);
	return 0;
}	
