#ifndef MATIP_H_
#define MAT_H_
class Image{
	//various channels
public:
	mat <int>ch0;
	mat <int>ch1;
	mat <int>ch2;
	bool rgb;
	Image(): ch0(1,1){}

};
void loadImage(cv::Mat &,Image &,bool);
void loadMat(cv::Mat &,Image &,bool);
#endif
