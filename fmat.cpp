#include "mat.h"
#include <fstream>
template <typename Tp1>void writemat(mat<Tp1> &m,char *name){
	int r=m.row;
	int c=m.col;
	int i,j;
	ofstream file(name);
	file<<"rows: "<<r<<"\n";
	file<<"cols: "<<c<<"\n";
	file<<"data: \n";
	for(i=0;i<r;i++){
		file<<"\t";
		for(j=0;j<c;j++)file<<m.a[i][j]<<" ";
		file<<"\n";
	}
	file.close();
}
template <typename Tp1>void readmat(mat<Tp1> &m,char *name){
	int r,c,i,j;
	char word[30];
	ifstream file(name);
	if(file.is_open()){
		file>>word;
		file>>r;file>>word;
		file>>c;file>>word;
		if(m.row!=r || m.col!=c)m.reallocate(r,c);
		for(i=0;i<r;i++){
			for(j=0;j<c;j++)file>>m.a[i][j];
		}
	}
	else cout<<"file does not exist\n";
	file.close();
}
