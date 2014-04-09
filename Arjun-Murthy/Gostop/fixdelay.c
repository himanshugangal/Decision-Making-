#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define p 1000 
#define q 1
#define s 230
#define r 250
#define n 1
#define dt 0.01
#define C 10  
#define k 100


int main()
{
int hit , i , j , rni ,error, current , previous , cs , current1 , previous1 , cs1 ;
float tmp,tmp1,rn,V[p],Vspike[p],In[p],rate[p],RT[q] ;
float rn1,V1[p],V1spike[p],In1[p],rate1[p],RT1[q] ;
FILE *frt ;
frt = fopen("Rates.txt","w"); 
FILE *frt1 ;
frt1 = fopen("StopReactiontimeusher.txt","w"); 
FILE *ferror ;
ferror = fopen("Probabilityusher.txt","w"); 
float sum_i,sum1_i;
double rands[1000];
double rands1[1000];

    for (i=1; i<=p; i++){
	  rands[i] = 100.0 ;
  }	
  	  
    for (i=1;i<=k;i++){
	rands1[i] = 0;
  }		
    for (;i<=p;i++){
	rands1[i] = 100.0 ;
  }
		
		for(i=1;i<=p;i++)
		{
			In[i] = 0 ; 
			In[i] = rands[i] ;
			V[i] = 0 ; 
			Vspike[i] = 0 ; 
		}
		
		for(i=1;i<=p;i++)
		{
			In1[i] = 0 ; 
			In1[i] = rands1[i] ;
			V1[i] = 0 ; 
			V1spike[i] = 0 ; 
		}

hit = 0 ; 
sum_i = 0 ; 
current = 0 ; 
previous = 0  ; 
cs=0 ;   

sum1_i = 0 ; 
current1 = 0 ; 
previous1 = 0  ; 
cs1=0 ;   

V[1] = 0 ;
V1[1] = 0 ;
float f,g ;
int m ;  
for(i=2;i<=p;i++)
	{
		sum_i = sum_i + 0.75*(i*In[i])/p ;
		if(V1[i-1]>0) { f = V1[i-1] ; } else { f = 0 ; }
		V[i] = V[i-1] + sum_i*dt/(C) -0.01*f ;
			
		sum1_i = sum1_i + 0.98*(i*In1[i])/p ;
		if(V[i-1]>0) { g = V1[i-1] ; } else { g = 0 ; }
		V1[i] = V1[i-1] + sum1_i*dt/(C) - 0.0005*g;
		
			if(V[i] > 10)
				{
					V[i] = 0 ; 
					Vspike[i] = 100 ; 
					
				}
			if(V1[i] > 10)
				{
					V1[i] = 0 ; 
					V1spike[i] = 100 ; 
					
				}
	
	
		

	
	
		cs = 0 ;
		for(m=2;m<=i;m++)
		{
			if (Vspike[m] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = m ; 
					tmp = current - previous ; 
					rate[m] = 1.0 / tmp;
					previous = m ;
					}
					
			}
			else {rate[m] = rate[m-1];}
		}
		
		cs1 = 0 ;
		for(m=2;m<=i;m++)
		{
			if (V1spike[m] == 100  ) 
			{
					cs1++ ; 
					if(cs1>1) {
					current1 = m ; 
					tmp1 = current1 - previous1; 
					rate1[m] = 1.0 / tmp1;
					previous1 = m ;
					}
					
			}
			else {rate1[m] = rate1[m-1];}
		}
/*
for(j=1;j<=m;j++){
if(( rate1[j]>=rate[j] ) && (rate1[j] > 0.1) && (hit != 1)) { 
	hit = 1; 		
	printf("%d\n",j); 

} 
}
*/
}
for(i=2;i<=p;i++){
	if(( rate1[i]>rate[i] ) && (rate1[i] > 0.1) && (hit != 1)) { 
	hit = 1; 		
	printf("%d\n",i); }
	fprintf(frt,"%f\t %f\t %d \t %f \n" , rate[i] , rate1[i] ,  i , In[i] ) ; }
}

