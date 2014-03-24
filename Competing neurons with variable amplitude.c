#include <stdio.h>
#include <stdlib.h>
#define p 1000 
#define n 1
#define dt 0.01
#define C 10  


int main()
{
int i , rni ;
float rn ;

float V1[p],V2[p] ; 
float base1[p],base2[p] ;
float Vspike1[p],Vspike2[p] ;
float In1[p],In2[p] ;
float rate1[p],rate2[p] ; 
	
for(i=1;i<=250;i++)
{
	base1[i] = 35.0 ; 
	base2[i] = 31.0 ; 
}
for(i=251;i<=p;i++)
{
	base1[i] = 35.0 ; 
	base2[i] = 31.0 ;
}		

	
		for(i=1;i<=p;i++)
		{
			In1[i] = 0 ; 
			In2[i] = 0 ; 		
			rni = rand()%70 - 35 ; 
			rn = rni / 10.0 ; 
			In1[i] = base1[i] + rn ; 
			In2[i] = base2[i] + rn ; 
		}



FILE *f_V,*f_Rate ; 
float sum_i1 ;
sum_i1 = 0 ; 
float sum_i2 = 0 ; 
int current = 0 ; 
int previous = 0  ; 
float tmp ;
int	cs=0 ;   
f_V = fopen("Voltage OP's.txt","w");
f_Rate = fopen("Rates.txt","w");

V1[1] = 0 ;
V2[1] = 0 ; 
for(i=2;i<=p;i++)
	{
		sum_i1 = sum_i1 + (i*In1[i])/p ;
		sum_i2 = sum_i2 + (i*In2[i])/p ;		
		V1[i] = V1[i-1] + (sum_i1*dt)/C -0.1*V2[i-1] - 0.1*V1[i-1] ;
		V2[i] = V2[i-1] + (sum_i2*dt)/C -0.1*V1[i-1] - 0.1*V2[i-1];	
			if(V1[i] > 30)
				{
					V1[i] = 0 ; 
					Vspike1[i] = 100 ; 
					
				}
			
			if(V2[i] > 30)
				{
					V2[i] = 0 ; 
					Vspike2[i] = 100 ; 
					
				}
			
	}
	
FILE *test ; 
test = fopen("test.txt","w");
	
	
		cs = 0 ;
		for(i=2;i<=p;i++)
		{
			if (Vspike1[i] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = i ; 
					tmp = current - previous ; 
					printf("%f \n" , tmp );
					fprintf(test,"%f \t %f \n",tmp,V1[i]);
					rate1[i] = 1.0 / tmp;
					previous = i ;
					}
					
			}
			else {rate1[i] = rate1[i-1];}
		}
		
FILE *test2 ; 
test2 = fopen("test2.txt","w");
		for(i=2;i<=p;i++)
		{
			if (Vspike2[i] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = i ; 
					tmp = current - previous ; 
					printf("%f \n" , tmp );
					fprintf(test2,"%f \t %f \n",tmp,V2[i]);
					rate2[i] = 1.0 / tmp;
					previous = i ;
					}
					
			}
			else {rate2[i] = rate2[i-1];}
		}
fclose(test2) ; 		
fclose(test);	
FILE *f_V2;
FILE *f_Rate2;
f_V2 = fopen("2nd OP.txt","w");
f_Rate2 = fopen("2nd Rate.txt","w");
	
	for(i=2 ; i<= 800 ; i++){
		
			fprintf(f_V,"%f\n",V1[i] + Vspike1[i]);
			fprintf(f_Rate,"%f\n",rate1[i] );
			
		}

	for(i=2 ; i<= 800 ; i++){
		
			fprintf(f_V2,"%f\n",V2[i] + Vspike2[i]);
			fprintf(f_Rate2,"%f\n",rate2[i] );
			
		}

	fclose(f_V2);
	fclose(f_Rate2);
	fclose(f_V);
	fclose(f_Rate);
}
