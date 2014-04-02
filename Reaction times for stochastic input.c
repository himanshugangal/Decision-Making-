#include <stdio.h>
#include <stdlib.h>
#define p 1000 
#define q 1000
#define n 1
#define dt 0.01
#define C 10  


int main()
{
int i , j , rni , current , previous , cs ;
float tmp,rn,V[p],Vspike[p],In[p],rate[p],RT[q] ;
FILE *frt ;
frt = fopen("Reactiontime.txt","w"); 
float sum_i ;
	
for(j=1;j<=q;j++){

		rni = rand()%40 + 35 ;
		for(i=1;i<=p;i++)
		{
			In[i] = 0 ; 
			In[i] = rni ;
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

}
