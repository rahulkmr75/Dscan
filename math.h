#ifndef MATH_H_
#define MATH_H_
#define PI 3.1415926536
class math{
public:
	double pow(const int x,const int n){
		if(n==1)return x;
		return x*pow(x,n-1);
	}
	double abs(const double x){
		return ((x>0)?x:-1*x);
	}
	double ceil(const double x){
		int t=(int)x;
		return ((x>0)?t+1:t);
	}
	double floor(const double x){
		int t=(int)x;
		return ((x>0)?t:t+1);
	} 
	int abs(const int x){
		return ((x>0)?x:-1*x);
	}
	double exp(const double d=1.0){
		double pe,ne=1,pv=d;
		//previous and new value and x^loop
		double fact=1,loop=2;
		//factorial and loop count+2
		do{
			pe=ne;
			ne+=pv/fact;
			pv*=d;
			fact*=loop++;
		}while(pe!=ne);
		return ne;
	}
	double sine(const double xt){
		double x;
		if (xt>2*PI)x=abs(xt)-(floor(xt/2/PI))*2*PI;
		else x=xt;

		double pv,nv=0,xpow=x;
		int n=1,fact=1;
		do{
			pv=nv;
			nv+=xpow/fact*(2-n%4);
			xpow*=x*x;
			n+=2;
			fact*=(n-1)*(n-2);
		}while(pv!=nv);
		return nv;
	}
	double cos(const double xt){
		double x;
		if (x>2*PI)x=xt-((int)xt/(2*PI))*2*PI;
                else x=xt;
		double pv,nv,xpow,n=1,fact=1;
	}
	double tan(const double xt){
	}
};	
#endif
