#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define p 1000 
#define q 1000
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
int i , j , rni , current , previous , cs ;
float tmp,rn,V[p],Vspike[p],In[p],rate[p],RT[q] ;
FILE *frt ;
frt = fopen("Reactiontime.txt","w"); 
float sum_i ;

  double rands[1000];
  for (i=1; i<=q; i++){
  rands[i] = 100.0 + 15.0*random_normal();
  }	
for(j=1;j<=q;j++){

		
		for(i=1;i<=p;i++)
		{
			In[i] = 0 ; 
			In[i] = rands[j] ;
			V[i] = 0 ; 
			Vspike[i] = 0 ; 
		}
	


sum_i = 0 ; 
current = 0 ; 
previous = 0  ; 
cs=0 ;   

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
		
for(i=2;i<=p;i++){
	if(rate[i] > 0.05){ fprintf(frt,"%d\t %f \t %d \n" , j , In[5] ,  i ) ; RT[j] = i; break; }		
	}

}
FILE *RTdis ; 
RTdis = fopen("RTDis.txt","w");
int x,count ; 
x = 150 ; 
for(;;){
count = 0 ;
for(i=1;i<=q;i++) {

	if((RT[i]<=x+10) && (RT[i]>=x)) {

		count++ ; 	
			
		}
	}
fprintf(RTdis,"%d \t %d \n",count,x);
x = x + 1 ; 
if(x > 260 ) { break ; }	
}

fclose(RTdis);
}
