
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define nt 500 
#define p 1000
//----------------------------------------------------------------------------------------------------
typedef struct neuron{ //Defining a structure for an individual neuron
		float In[p];
		float base[p];
		float mean ; 
		float std ; 
};
//----------------------------------------------------------------------------------------------------
int main()
{
int i,j,rni ;     
float rn, inc = 0.6 ; 
struct neuron Input[nt] ; 
float sum = 0 ; 
//------------------------------------------------------------------------------------------------
// Generating the input with noise 

for(j=0;j<nt;j++)
	{
		for(i=1;i<=p;i++)
		{
			Input[j].base[i] = inc ; 
			Input[j].In[i] = 0 ; 
			rni = rand()%70 - 35 ; 
			sum = sum + rni ;
			rn = rni / 100.0 ; 
			Input[j].In[i] = Input[j].base[i] + rn ; 
			}
		//printf("%f\n" , sum);
		sum = 0 ;
}

//--------------------------------------------------------------------------------------------------
// Finding the standard deviation of the varying input 
float tmp = 0 ; 
sum = 0 ; 
for(j=0;j<nt;j++)
{
	for(i=1;i<=p;i++)
	{
		sum = sum + Input[j].In[i] ; 
		
	}
		Input[j].mean = sum / p ; 
		//printf("%f\n" , Input[j].mean ) ; 
		sum = 0 ; 
	for(i=1 ; i<= p ; i++)
	{
		tmp = (Input[j].In[i] - Input[j].mean)*(Input[j].In[i] - Input[j].mean) ;
		sum = sum + tmp ;  
	}
		Input[j].std = sqrt(sum/p);
		printf("%f\n" , Input[j].std );
}
//------------------------------------------------------------------------------------------------------


}
