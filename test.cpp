#include "nn.h"
#include <string>
#include "fmat.h"
#include <iostream>
#include <cassert>
#include "mat.h"
#include "math.h"
//#include "math.h"
int main(){
	/*mat <double>a(2,2);
	*/
	/*Stack s;
	s.Push(10);
	*/
	/*mat <double>a(10,10);
	a.identity();
	mat <double>d(10,10);
	mat<double> **ls=new mat<double>*[2];
	ls[0]=new mat<double>(2,2);
	ls[0]->print();
	a.free();
	d.free();
	int n[]={5,4,3};
	mat<double>** w=initNetwork(3,n);
	w[0]->print();
	w[1]->print();
	w[2]->print();
	*/
	mat<int> d(10,10);
	d.identity();
	int n[]={200,130,45};
	mat<double>** m=initNetwork(3,n);
	writeWeights(m,3);
	char s1[10]="layer_01";
	return 0;
}
