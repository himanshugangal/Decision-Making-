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
#define k 200
#define nt 200
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
int  l , hit , i , j , current , previous , cs , current1 , previous1 , cs1 ;
float tmp,tmp1,rn,V[p],Vspike[p],In[p],rate[p],RT[q] ;
float rn1,V1[p],V1spike[p],In1[p],rate1[p],RT1[q] ;
FILE *frt ;
frt = fopen("Rates.txt","w"); 
float sum_i,sum1_i;
double rands1[nt],rands[nt];
float f,g ;
int TSRT[nt] ; 
for(l=1;l<=nt;l++) {
	TSRT[l] = 0 ; 
	rands[l] = 100.0 + 25.0*random_normal();
	rands1[l] = 105.0 + 25.0*random_normal();
	//printf("%f \t %f \t \n " , rands[l] , rands1[l] );
}

for(l=1;l<=nt;l++){    


		for(i=1;i<=p;i++)
		{
			In[i] = 0 ; 
			In[i] = rands[l] ;
			V[i] = 0 ; 
			Vspike[i] = 0 ; 
		}
		
		for(i=1;i<=k;i++)
		{
			In1[i] = 0 ; 
			V1[i] = 0 ; 
			V1spike[i] = 0 ; 
		}

		for(i=k+1;i<=p;i++)
		{
			In1[i] = 0 ; 
			In1[i] = rands1[l] ;
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


for(i=2;i<=p;i++){
	if(( rate1[i]>rate[i] ) && (rate1[i] > 0.15) && (hit != 1)) { 
	hit = 1; 		
	TSRT[l] = i;	
	fprintf(frt,"%d \t %d \n",TSRT[l],l);
	 } }
	//fprintf(frt,"%f\t %f\t %d \t %f \n" , rate[i] , rate1[i] ,  i , In[i] ) ; }
}

for(i=1;i<=nt;i++){ printf("%d \n" , TSRT[i]); }
FILE *TSRTdis ; 
TSRTdis = fopen("TSRTdis.txt","w");
int x,count ; 
x = 100 ; 
for(;;){
count = 0 ;
for(i=1;i<=nt;i++) {

	if((TSRT[i]<=x+10) && (TSRT[i]>=x)) {

		count++ ; 	
			
		}
	}
fprintf(TSRTdis,"%d \t %d \n",count,x);
x = x + 1 ; 
if(x > 600 ) { break ; }	
}

fclose(TSRTdis);

fclose(frt);

}
