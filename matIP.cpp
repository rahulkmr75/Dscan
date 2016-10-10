/*
	this file has some linking functions from opencv libraries to 
	mat header library like loading images to struct Image   etc.
	THIS LIBRARY DEPENDS ON OPENCV LIBRARY ESPECIALLY Mat LIBRARY
	AS WELL AS THE mat HEADER FILE.
*/
#include <opencv2/opencv.hpp>
#include "mat.h"
using namespace cv;
class Image{
	//various channels
public:
	mat <int>ch0;
	mat <int>ch1;
	mat <int>ch2;
	bool rgb;
	Image(): ch0(1,1){}

};
void loadMat(Mat &img,Image &m,bool rgb){}
void loadImage(Mat &img,Image &m,bool rgb){
	int r=img.rows,c=img.cols,i,j;
	m.rgb=rgb;
	if(rgb){
		if((m.ch0).row!=r || m.ch0.col!=c)m.ch0.reallocate(r,c);
		if((m.ch1).row!=r || m.ch1.col!=c)m.ch1.reallocate(r,c);
		if((m.ch2).row!=r || m.ch2.col!=c)m.ch2.reallocate(r,c);
		
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				Vec3b intensity=img.at<Vec3b>(Point(i,j));
				m.ch0.a[i][j]=intensity.val[0];
				m.ch1.a[i][j]=intensity.val[1];
				m.ch2.a[i][j]=intensity.val[2];
			}
		}
	}
	else{
		if(m.ch0.row!=r || m.ch0.col!=c)m.ch0.reallocate(r,c);
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				Scalar intensity=img.at<uchar>(Point(i,j));
				m.ch0.a[i][j]=intensity.val[0];
			 }
		}
	}
}