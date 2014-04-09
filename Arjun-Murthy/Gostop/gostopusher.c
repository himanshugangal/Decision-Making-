#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define p 1000 
#define q 200
#define s 230
#define r 250
#define n 1
#define dt 0.01
#define C 10  
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double drand()   /* uniform distribution, (0..1] */
{
  return (rand()+1.0)/(RAND_MAX+1.0);
}

double random_normal() 
 /* normal distribution, centered on 0, std dev 1 */
{
  return sqrt(-2*log(drand())) * cos(2*M_PI*drand());
}


int main()
{
int i , j , k , rni ,error, current , previous , cs , current1 , previous1 , cs1 ;
float tmp,tmp1,rn,V[p],Vspike[p],In[p],rate[p],RT[q] ;
float rn1,V1[p],V1spike[p],In1[p],rate1[p],RT1[q] ;
FILE *frt ;
frt = fopen("Reactiontimeusher.txt","w"); 
FILE *frt1 ;
frt1 = fopen("StopReactiontimeusher.txt","w"); 
FILE *ferror ;
ferror = fopen("Probabilityusher.txt","w"); 
float sum_i,sum1_i,errper ;
double rands[1000];
double rands1[1000];

for(k=1;k<=s;k++) {

   error = 0 ; 
	
    for (i=1; i<=q; i++){
	  rands[i] = 80.0 + 25.0*random_normal();
  }	
  	  
    for (i=1;i<=k;i++){
	rands1[i] = 0;
  }		
    for (;i<=q;i++){
	rands1[i] = 100.0 + 25.0*random_normal();
  }
	
for(j=1;j<=q;j++){

		
		for(i=1;i<=p;i++)
		{
			In[i] = 0 ; 
			In[i] = rands[j] ;
			V[i] = 0 ; 
			Vspike[i] = 0 ; 
		}
		
		for(i=1;i<=p;i++)
		{
			In1[i] = 0 ; 
			In1[i] = rands1[j] ;
			V1[i] = 0 ; 
			V1spike[i] = 0 ; 
		}


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

for(i=2;i<=p;i++)
	{
		sum_i = sum_i + (i*In[i])/p ;
		V[i] = V[i-1] + sum_i*dt/(C) -0.8*V1[i-1];
			
		sum1_i = sum1_i + (i*In1[i])/p ;
		V1[i] = V1[i-1] + sum1_i*dt/(C) - 0.1*V[i-1];

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
	
}
	

	
	
		cs = 0 ;
		for(i=2;i<=p;i++)
		{
			if (Vspike[i] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = i ; 
					tmp = current - previous ; 
					rate[i] = 1.0 / tmp;
					previous = i ;
					}
					
			}
			else {rate[i] = rate[i-1];}
		}
		
		cs1 = 0 ;
		for(i=2;i<=p;i++)
		{
			if (V1spike[i] == 100  ) 
			{
					cs1++ ; 
					if(cs1>1) {
					current1 = i ; 
					tmp1 = current1 - previous1; 
					rate1[i] = 1.0 / tmp1;
					previous1 = i ;
					}
					
			}
			else {rate1[i] = rate1[i-1];}
		}
/*		
for(i=2;i<=p;i++){
	if(rate[i] > 0.05){ fprintf(frt,"%d\t %f \t %d \n" , j , In[5] ,  i ) ; RT[j] = i; break; }		
	}
*/
for(i=2;i<=p;i++){
	if(rate1[i] > 0.05){ fprintf(frt1,"%d\t %f \t %d \t %f \n" , j , In1[5] ,  i , rate1[i] ) ; RT1[j] = i; break; }		
	}

if( (rate[r]>rate1[r]) && (rate[r]>0.05) ) { error++ ;
			 fprintf(frt,"%f \t %f \t %d \n",rate[r],rate1[r],error) ;  }
/*if( (rate1[r]>rate[r]) && (rate1[r]>0.05) ) {
			 fprintf(frt1,"%f \t %f \t %d \n",rate[r],rate1[r],error) ;  }
*/
}
errper = (float)error / q ; 
fprintf(ferror," %f \t %d \n " , errper , k ) ; 
}

}
