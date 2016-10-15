#ifndef CST_METHODS_H_
#define CST_METHODS_H_
/*
	makes a one dimensional vector for given image pyramid, with a width 5 in both dimension
	Here the vector is 750 dimension long. int x , y are the centroid point of the window to
	beconsidered.
*/
void makeVector(Image &,Image &,Image &,mat<int> &, int,int);


/*
	given the path of the index files for weights and bias returns a array of string with 
	weights and bias respectively wtih layer1 at index 0 of the array
*/	
char **getWFileNames(char *name);
char **getBFileNames(char *file);

//initializes output matrix
void makeOutput(mat<double> **output);
#endif
