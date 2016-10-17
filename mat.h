#ifndef MAT_H_
#define MAT_H_
#include <iostream>
using namespace std;
template <class T>
class mat{
public:
	int row,col;
	T **a;
	//this boolean value stores the mode for auto garbage collection
	bool auto_gc;
public:
	//constructor; by default the rows and col are 1
	mat(const int r=1,const int c=1,const bool fr=false){
		//by  default the garbage collection is set to 
		//false; to enable auto garbage collection the 
		//third parameter should be true 
		auto_gc=fr;
		row=r;
		col=c;
		a=new T *[r];
		if(a==NULL){
			cout <<"System out of memory\n";
			throw "OutOfMemoryException";
		}
		int i;
		for (i=0;i<r;i++){
			a[i]=new T[c];
			if (a[i]==NULL){
				cout <<"System out of memory\n";
				throw "OutOfMemoryException";
			}
		} 
	}
	~mat(){
		//if the garbage collection is set to 
		//automatic it frees the allocated space
		if(auto_gc)free();
	}
	//initialixes the matrix object by user 
	void initialize(){
		int i,j;
		for (i=0;i<row;i++){
			for(j=0;j<col;j++){
				cin>>a[i][j];
			}
		}
	}
	//prints the matrix data
	void print(){
		int i,j;
		for (i=0;i<row;i++){
			for(j=0;j<col;j++){
				cout<<a[i][j]<<"  ";
			}
		cout<<endl;
		} 
	}
	//deletes a matrix a frees the space
	void free(){
		int i;
		for (i=0;i<row;i++){
			delete(a[i]);
		}
		delete(a);
	}
	//resizes the matrix
	void reallocate(int r=1,int c=1){
		free();
		row=r;
		col=c;
		a=new T *[r];
		int i;
		for (i=0;i<c;i++){
			a[i]=new T[c];
		} 
	}
	//copies the matrix data of the object called the function
	//into the one one provided as a parameter 
	template <typename U>
	void copy(mat<U> &b){
		if(row!=b.row ||col!=b.col)b.reallocate(row,col);
		int i,j;
		for (i=0;i<row;i++){
			for (j=0;j<col;j++){
				b.a[i][j]=a[i][j];
			}
		}
	}
	//fills the matrix with zero
	void zeros(){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++)a[i][j]=0;
		}
	}
	//fills the matrix with one
	void ones(){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++)a[i][j]=1;
		}
	}
	void scale(const double d){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++)a[i][j]=d*a[i][j];
		}
	}
	//creates an identity matrix and stores in the matrix
	//of the object called
	void identity(){
		if (row!=col){
			cout<<"can not make  a non square  identity matrix\n";
			throw "BadArgumentDimensions";
		}
		for (int i=0;i<row;i++){
			for (int j=0;j<col;j++){
				if(i==j)
					a[i][j]=1.0;
				else
					a[i][j]=0.0;
			}
		}
	}
	//operator overloading 
	//multiplies two matrix of same data types
	mat operator*(mat<T> &b){
		if(col!=b.row){
                        cout<<"matrix multiplication not possible col(mat1)!=row(mat2)\n";
                        throw "BadArgumentsDimensions";

                }
                mat<T> c(row,b.col,true);
                int i,j,k;
                T sum;
                for (i=0;i<row;i++){
                        for(j=0;j<b.col;j++){
                                sum=0.0;
                                for(k=0;k<col;k++){
                                        sum+=a[i][k]*b.a[k][j];
                                }
                                c.a[i][j]=sum;
                        }
                }
                return c;
        }
	//multiplies the matrix with a scalar 
	//FORMAT SHOULD BE MAT*SCALAR
	//the return type is always mat<double> no matter what	
	mat<double> operator*(const double d){
		mat<double> c(row,col,true);
		int i,j;
		for (i=0;i<row;i++){
			for (j=0;j<col;j++){
				c.a[i][j]=a[i][j]*d;
			}
		}
		return c;
	}
	//adds two matrix if possible :
	mat operator+(mat<T> &b){
		if(row!=b.row and col!=b.col){
			cout<<"matrix addition not possible : unequal dimensions\n";
			throw "BadArgumentsDimensions";
		}
		mat<T> c(row,col,true);
		int i,j;
		for (i=0;i<row;i++){
			for (j=0;j<col;j++)c.a[i][j]=a[i][j]+b.a[i][j];
		}
		return c;
	}
	//subtracts two matrix if possible
	mat operator-(mat<T> &b){
                if(row!=b.row and col!=b.col){
			cout<<"matrix addition not possible : unequal dimensions\n";
                        throw "BadArgumentsDimensions";
		}
                mat<T> c(row,col,true);
                int i,j;
                for (i=0;i<row;i++){
                        for (j=0;j<col;j++)c.a[i][j]=a[i][j]-b.a[i][j];
                }return c;
        }

	//inverts a matrix and stores in the param provided
	void inverse(mat<double> &I){
		if(row!=col)
			throw "BadArgumentsDimension";
		/*if(determinant()==0)
			throw "ZeroValueDeterminant";*/
		mat<double> temp(row,col);
		copy<double>(temp);
		I.reallocate(row,col);
		I.identity();
		double t1,t2;
		int i,j,k;
		for(i=0;i<row;i++){
			for (j=0;j<row;j++){
				if(i==j)
					continue;
				t1=temp.a[i][i];
				t2=temp.a[j][i];
				//cout<<t1<<t2<<endl;
				for (k=0;k<col;k++){
					temp.a[j][k]=temp.a[j][k]-temp.a[i][k]*t2/t1;
					I.a[j][k]=I.a[j][k]-I.a[i][k]*t2/t1;
					//cout<<i<<j<<k<<"temp\n";
					//temp.print();
					//cout<<"I\n";
					//I.print();
				}
			}//j
			for(j=0;j<col;j++){
				temp.a[i][j]/=t1;
				I.a[i][j]/=t1;
			}
		}
		temp.free();
	}//inverse
	void  inv(mat<double> &I){
		if(row!=col)
			throw "BadArgumentsDimensions";
		double det=determinant();
		if(det==0)
			throw "ZeroValueDeterminant";
		I.reallocate(row,col);
		for (int i=0;i<row;i++){
			for(int j=0;j<col;j++)I.a[j][i]=cofactor(i,j)/det;
		}
	}

	//returns a region of interest like a row, a col or a part of matrix 
	mat getrow(const int i){ 
		mat c=roi(i,0,i+1,col);
		return c;
	}
	mat getcol(const int i){
		mat c=roi(0,i,row,i+1);
		return c;
	}
	mat roi(const int x0,const int y0,const int x1,const int y1){
		mat<T> r(x1-x0,y1-y0);
		int i,j;
		for (i=x0;i<x1;i++){
			for (j=y0;j<y1;j++)r.a[i-x0][j-y0]=a[i][j];
		}
		return r;
	}		
	double determinant(){
		if(row!=col){
			cout<<"not a square matrix\n";
			throw "BadArgumentDimensions";
		}
		else if(row==1)
			return a[0][0];
		else if(col==2)
			return(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
		else{
			double det=0;
			for(int i=0;i<row;i++)det+=a[0][i]*cofactor(0,i);
			return det;
		}
	}
	double cofactor(const int i,const int j){
		if(row==col && col==1)
			throw "InsufficientMatrixSize";
		return((i+j)%2?minorval(i,j):-1*minorval(i,j));
	}
	double minorval(const int i,const int j){
		if(row==col && col==1)
			throw "InsufficientMatrixSize";
		int trow=row-1,tcol=col-1;
		mat<T> temp(trow,tcol);
		//tracks copy from  parent matrix to child matrix
		int trvar1=0,trvar2=0,size=row*col;
		
		//the loop extracts the minorval matrix
		for(;trvar1<size;trvar1++){
			if(trvar1%col==j || trvar1/col==i)
				continue;
			else
				temp.a[trvar2/tcol][trvar2++%tcol]=a[trvar1/col][trvar1%col];
			
		}
		//return the determinant and free the matrix
		double det=temp.determinant();
		temp.free();
		return det;
	}
};
//multiplies matrix a and b and stores the result in matrix c
template <typename Tp1,typename Tp2,typename Tp3>
void multiply(mat<Tp1> &a,mat<Tp2> &b,mat<Tp3> &c){
	if(a.col!=b.row){
		cout<<"matrix multiplication not possible col(mat1)!=row(mat2)\n";
		throw "BadArgumentsDimensions";
	}
	double sum=0;
	if(c.row!=a.row || c.col!=b.col)c.reallocate(a.row,b.col);	
	int i,j,k;
	for (i=0;i<a.row;i++){
		for(j=0;j<b.col;j++){
			sum=0.0;
			for(k=0;k<a.col;k++){
				sum+=a.a[i][k]*b.a[k][j];
			}
			c.a[i][j]=sum;
		}
	}
}
//adds two matrix a and b and stores the result in c
template <typename Tp1,typename Tp2,typename Tp3>
void add(mat<Tp1> &a,mat<Tp2> &b,mat<Tp3> &c){
	if(a.row!=b.row || a.col!=b.col){
		cout<<"matrix addition not possible col(mat1)!=row(mat2)\n";
		throw "BadArgumentsDimensions";
	}
	if(c.row!=a.row || c.col!=b.col)c.reallocate(a.row,a.col);
	int i,j;
	for (i=0;i<a.row;i++){
		for(j=0;j<a.col;j++){
			c.a[i][j]=a.a[i][j]+b.a[i][j];
		}
	}
}
template <typename Tp1,typename Tp2,typename Tp3>
void subtract(mat<Tp1> &a,mat<Tp2> &b,mat<Tp3> &c){
	if(a.row!=b.row || a.col!=b.col){
		cout<<"matrix addition not possible col(mat1)!=row(mat2)\n";
		throw "BadArgumentsDimensions";
	}
	if(c.row!=a.row || c.col!=b.col)c.reallocate(a.row,a.col);
	int i,j;
	for (i=0;i<a.row;i++){
		for(j=0;j<a.col;j++){
			c.a[i][j]=a.a[i][j]-b.a[i][j];
		}
	}
}
//similar to hadamard product
template <typename Tp1,typename Tp2,typename Tp3>
void correlate(mat<Tp1> &m1,mat<Tp2> &m2,mat<Tp3> &out){
	if(m1.row!=m2.row || m2.col!=m1.col){
		cout<<"hadamard prouct not passible : improper matrix dimension\n";
		throw "BadArgumentsDimensions";
	}
	if(out.row!=m1.row || out.col!=m1.col)out.reallocate(m1.row,m1.col);
	int i,j;
	for(i=0;i<m1.row;i++){
		for(j=0;j<m1.col;j++)out.a[i][j]=m1.a[i][j]*m2.a[i][j];
	}
}
//tranposes the object matrix and returns a mat object
template <typename Tp1,typename Tp2>
void transpose(mat<Tp1> &m,mat<Tp2> &tr){
	if(m.row!=tr.col || m.col!=tr.row)tr.reallocate(m.col,m.row);
	int i,j;
	for (i=0;i<m.row;i++){
		for (j=0;j<m.col;j++){
			tr.a[j][i]=m.a[i][j];
		}
	}
}	
#endif
