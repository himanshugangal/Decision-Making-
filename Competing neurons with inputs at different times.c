#include <stdio.h>
#include <stdlib.h>
#define p 1000 
#define n 1
#define dt 0.01
#define C 10  
#define f 800
#define s_time 10

int main()
{
float sum_i1 ;
float sum_i2 = 0 ; 
int current = 0 ; 
int previous = 0  ; 
int b ; 
float tmp ;
int cs ; 
int i , rni ;
int l = s_time / dt ;  
float rn ;
float z,dz=0.1 ;
float time = 0 ;
float V1[p],V2[p] ; 
float base1[p],base2[p] ;
float Vspike1[p],Vspike2[p] ;
float In1[p],In2[p] ;
float rate1[p],rate2[p]; 
FILE *result ; 
result = fopen("results.txt","w");
FILE *rate11 ; 
rate11 = fopen("rate1.txt","w");
FILE *rate22 ; 
rate22 = fopen("rate2.txt","w");
float resultarr[l] ; 
for ( b = 1 ; b <= p ; b++ )
{
resultarr[b] = 0 ; 
}
b = 1 ; 
for ( b = 1  ; b <= p  ; b++  ){	
for(i=1;i<=b;i++)
{
	base1[i] = 35.0 ; 
	base2[i] = 0 ; 	
	V1[i] = 0 ; 
	Vspike1[i] = 0 ; 
	rate1[i] = 0 ; 
	V2[i] = 0 ; 
	Vspike2[i] = 0 ; 
	rate2[i] = 0 ; 
	}

for(i=b+1;i<=p;i++)
{
	base1[i] = 35.0 ; 
	base2[i] = 50.0 ;
	V1[i] = 0 ; 
	Vspike1[i] = 0 ; 
	rate1[i] = 0 ; 
	V2[i] = 0 ; 
	Vspike2[i] = 0 ; 
	rate2[i] = 0 ;
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



 
 
cs=0 ;   
V1[1] = 0 ;
V2[1] = 0 ; 
sum_i1 = 0 ;
sum_i2 = 0 ; 
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

	
		cs = 0 ;
		current = 0 ; 
		previous = 0 ;	 
		for(i=2;i<=p;i++)
		{
			if (Vspike1[i] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = i ; 
					tmp = current - previous ; 
					rate1[i] = 1.0 / tmp;
					previous = i ;
					}
					
			}
			else {rate1[i] = rate1[i-1];}
		}
		
		cs = 0 ; 
		current = 0 ; 
		previous = 0 ;		
		for(i=2;i<=p;i++)
		{
			if (Vspike2[i] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = i ; 
					tmp = current - previous ; 
					rate2[i] = 1.0 / tmp;
					previous = i ;
					}
					
			}
			else {rate2[i] = rate2[i-1];}
		}

fprintf(rate22,"%f \t %f \t %f \n", rate1[f] , rate2[f] , z) ; 

time = time + b*dt ; 

if ((rate1[f] > 0.1 )&&(rate1[f]>rate2[f]))
	{ resultarr[b] = 1.0 ; 
	 fprintf(result,"%f \t %d \t %f \t %f \n", resultarr[b] , b , rate1[f] , rate2[f] ) ;}  
if ((rate2[f] > 0.1 )&&(rate1[f]<rate2[f]))
	{ resultarr[b] = 2.0 ;  
	 fprintf(result,"%f \t %d \t %f \t %f \n", resultarr[b] , b , rate1[f] , rate2[f]) ;}
  	
}

}
