#ifndef MATIP_H_
#define MAT_H_
/*
	this file has some linking functions from opencv libraries to 
	mat header library like loading images to struct Image   etc.
	THIS LIBRARY DEPENDS ON OPENCV LIBRARY ESPECIALLY Mat LIBRARY
	AS WELL AS THE mat HEADER FILE.
*/
class Image{
	//various channels
public:
	mat <int>ch0;
	mat <int>ch1;
	mat<int> ch2;
	bool rgb;
	Image(): ch0(1,1), ch1(1,1),ch2(1,1){}

};
//fills the Image struct from Mat and vice-versa respectively
//the boolean represents the rgb state rgb->true, grayscale->false
void freeImage(Image &);
void loadImage(cv::Mat &,Image &,bool);
void loadMat(cv::Mat &,Image &,bool);
#endif
