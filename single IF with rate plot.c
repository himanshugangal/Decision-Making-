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

float V[p] ; 
float base[p] ;
float Vspike[p] ;
float In[p] ;
float rate[p] ; 
	
for(i=1;i<=250;i++)
{
	base[i] = 35.0 ; 
	
}
for(i=251;i<=p;i++)
{
	base[i] =35 ; 
	
}		

	
		for(i=1;i<=p;i++)
		{
			In[i] = 0 ; 
			rni = rand()%70 - 35 ; 
			rn = rni / 10.0 ; 
			In[i] = base[i] + rn ; 
			
		}



FILE *f_V,*f_Rate ; 
float sum_i ;
sum_i = 0 ; 

int current = 0 ; 
int previous = 0  ; 
float tmp ;
int	cs=0 ;   
f_V = fopen("Voltage OP's.txt","w");
f_Rate = fopen("Rates.txt","w");

V[1] = 0 ;

for(i=2;i<=p;i++)
	{
		sum_i = sum_i + (i*In[i])/p ;
		V[i] = V[i-1] + sum_i*dt/(C);
			
			if(V[i] > 30)
				{
					V[i] = 0 ; 
					Vspike[i] = 100 ; 
					
				}
			
	
}
	
FILE *test ; 
test = fopen("test.txt","w");
	
	
		cs = 0 ;
		for(i=2;i<=p;i++)
		{
			if (Vspike[i] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = i ; 
					tmp = current - previous ; 
					printf("%f \n" , tmp );
					fprintf(test,"%f \t %f \n",tmp,V[i]);
					rate[i] = 1.0 / tmp;
					previous = i ;
					}
					
			}
			else {rate[i] = rate[i-1];}
		}
		
		
fclose(test);	

	
	for(i=2 ; i<= 800 ; i++){
		
			fprintf(f_V,"%f\n",V[i] + Vspike[i]);
			fprintf(f_Rate,"%f\n",rate[i] );
			
		}

	fclose(f_V);
	fclose(f_Rate);
}
