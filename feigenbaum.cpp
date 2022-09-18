#include<iostream>
#include<iomanip>
#include<cmath>
#include<fstream>

using namespace std;



/*-------------------Funcao f^n ()----------------------------------*/


double fn(double y,double par,int order)
{
	
	
	int m;
	double x;

	x=y;
	
	m=pow(2,order);
	
	for(int i=0;i<m;i++)
	{
		x=4*par*x*(1-x);
	}
	
	return x;
}




/*---------------------------- DERIVADA------------------*/
double dn( double fp,double par,int order) 
{
	int n,m;
	double l,x,d;
	l = par;
	x=fp;
	d=1;
	
	m=pow(2,order);
	
	for( int j=0;j<m;j++) 
	{
		// d é a derivada anterior; está a fazer f'(x0)*f'(x1) porque entretanto x já foi atualizado
		
		d = 4*l*(1.-2.*x)*d;/* este d no início nao faz nada */
		x=4*l*x*(1.-x);
	}

	return d;
}


/*---------Localiza Ponto Fixo-------------*/
double ffp(double par1,double e,int order) /* find fixed point */ 
{
	double xl=0.5-e;
	double xu=0.5+e;
	double x,y;

	double dd=fn(xl,par1,order)-xl;
	
	for(int i=1;i<40;i++)
	{

		x=0.5*(xl+xu);
		y=fn(x,par1,order);

		if((y-x)/dd <0)
		{
			xu=x;
		}
		else
			xl=x;

	}

	return 0.5*(xl+xu);
}



int main() // how to find fixed point when the point is divergent
{
	ofstream myfile;
	myfile.open ("feigen.txt");

	double a1v[20];
	double del;
	double alfa,delta,t,tl,tu;
	a1v[0]=0.25;
	a1v[1]=0.75;
	double d[20];

	
	double fp,der;
	double a1,a1u,a1l;
	double eta = 0.1*2.5029; // começa-se a 10%
	double dif = 0.01;
	d[0]=0.5;
	d[1]=0.25;
	


	cout<<"k"<<"      "<<"del"<<"      "<<"alfa"<<"      "<<"a1"<<"      "<<"x"<<endl;

for(int k=1;k<=13;k++)
{
			eta=eta/2.5029;
			
			a1=a1v[k]+dif; // começo para lá de 0.75

									
	

										// start search for critical lambda
				for(int i=1;i<100;i++)
				{
					fp=ffp(a1,eta,k);
					der = dn(fp,a1,k);
					t=1.+der;

					if( t<0)
					{
						break;
					}
					else
					{
						a1=a1+dif;
						tl=t;
						a1l=a1-dif;
										}

				}

				tu=t;
				a1u=a1;

			while(a1u-a1l>10e-14)
			{


				a1=0.5*(a1l+a1u);

				fp=ffp(a1,eta,k);
				der=dn(fp,a1,k);
				t=1.+der;
					if(t*tl>0)
					{
						a1l=a1;
						tl=t;

					}
					else
					{
						a1u=a1;
						tu=t;
					}


			}

				a1v[k+1]=a1;
				d[k+1]=abs(fp-0.5);
				alfa=(d[k]-d[k-1]) /(d[k+1]-d[k]);
				del	= (a1v[k]-a1v[k-1])/(a1v[k+1]-a1v[k]);
				dif=0.1*( a1v[k] -a1v[k-1])/del;
				
				myfile<<k<<"   "<<del<<"    "<<alfa<<"    "<<a1<<"    "<<fp<<"   "<<endl;

	}

	return 0;
}


