#include <stdio.h>
#include <stdlib.h>
#define p 1000 	// Defining constant parameters 
#define n 2	// Number of neurons competing , competition algo written for 2 , but can be extended to n neurons  
#define dt 0.001
#define C 1  
#define B 0.001 // Neural inhibition parameter 
#define K 0.001 // Leakage Parameter
//----------------------------------------------------------------------------------------------
typedef struct Neurons{ 		//Defining the structure of a neuron 
		float In[p];
		float base[p] ;
		float V[p] ; 
		float Vspike[p] ; 
		float rate[p] ; 
		}; 
//----------------------------------------------------------------------------------------------
int main()
{

// Basic Variable Declarations 


int i , rni , j   ;
struct Neurons Neuron[n] ; // Generating 
float rn ;

//---------------------------------------------------------------------------------------------

// Initialising arrays to null value  

 
FILE *f_In ; 
f_In = fopen("Input stochastic current.txt" , "w"); 
for(j=0;j<n;j++){
	for(i=1;i<=p;i++)
		{
			Neuron[j].base[i] = 0 ; 
			Neuron[j].rate[i] = 0 ;
			Neuron[j].Vspike[i] = 0 ; 
		}

	}

//---------------------------------------------------------------------------------------------
// Inputs 

for(i=1;i<=150;i++)
{
	Neuron[0].base[i] = 2 ; 
	Neuron[1].base[i] = 1 ; 
	//Neuron[2].base[i] = 5 ; 
}

for(i=151;i<=p;i++)
{
	Neuron[0].base[i] = 2 ; 
	Neuron[1].base[i] = 1 ; 
	//Neuron[2].base[i] = 5 ; 
}		


//----------------------------------------------------------------------------------------------
// Adding noise 
for(j=0;j<n;j++)
	{
		for(i=1;i<=p;i++)
		{
			Neuron[j].In[i] = 0 ; 
			rni = rand()%70 - 35 ; 
			rn = rni / 100.0 ; 
			Neuron[j].In[i] = Neuron[j].base[i] + rn ; 
			
		}

}

		for(i=1;i<=p;i++)
		{
			fprintf(f_In,"%f \t %f \n", Neuron[0].In[i] , Neuron[1].In[i]);
			
		}
		
//------------------------------------------------------------------------------------------------
fclose(f_In);

// Merging the recurrent spiking integrate and fire model and the Usher and Mclelland competitions 

FILE *f_V,*f_Rate ; 
float sum_i[n] ;
sum_i[0] = 0 ; 
sum_i[1] = 0 ;
//sum_i[2] = 0 ;   
int current = 0 ; 
int previous = 0  ; 
float tmp,sum_v = 0 ;
int q=0 ; 
int	cs=0 ;   
f_V = fopen("Voltage OP's.txt","w");
f_Rate = fopen("Rates.txt","w");

Neuron[0].V[1] = 0 ;
Neuron[1].V[1] = 0 ;
for(i=2;i<=p;i++)
	{
		sum_i[0] = sum_i[0] + Neuron[0].In[i] ;
		sum_i[1] = sum_i[1] + Neuron[1].In[i] ;

		Neuron[0].V[i] = 0 ; 
		Neuron[0].Vspike[i] = 0 ; 
		
		Neuron[1].V[i] = 0 ; 
		Neuron[1].Vspike[i] = 0 ; 

		if(Neuron[1].V[i-1]>=0) { sum_v = Neuron[1].V[i-1] ; }
		else { sum_v = 0; } 
		Neuron[0].V[i] = Neuron[0].V[i-1] + sum_i[0]*dt/C - B*sum_v; // Lateral inhibition introduction 
		Neuron[0].V[i] = Neuron[0].V[i] -K*Neuron[0].V[i] ; //Leakage introduction
		
		if(Neuron[0].V[i-1]>=0) { sum_v = Neuron[0].V[i-1] ; }
		else { sum_v = 0; } 
		Neuron[1].V[i] = Neuron[1].V[i-1] + sum_i[1]*dt/C - B*sum_v; // Lateral inhibition introduction 
		Neuron[1].V[i] = Neuron[1].V[i] -K*Neuron[1].V[i] ;//Leakage introduction
		
		for(j=0;j<n;j++){				// Standard spiking points 
			if(Neuron[j].V[i] > 20)
				{
					Neuron[j].V[i] = 0 ; 
					Neuron[j].Vspike[i] = 100 ; 	
				
						}
				}
			
	}

//--------------------------------------------------------------------------------------------------------	
	// Finding Inter spiking intervals and spiking rates 	

	for(j=0;j<n;j++)
	{
		cs = 0 ;
		for(i=1;i<=p;i++)
		{
			if ( Neuron[j].Vspike[i] == 100  ) 
			{
					cs++ ; 
					if(cs>1) {
					current = i ; 
					tmp = current - previous ; 
					Neuron[j].rate[i] = 1.0 / tmp;
					previous = i ;
					}
					
			}
			else {Neuron[j].rate[i] = Neuron[j].rate[i-1];}
		}
		cs = 0 ; 
	}	
//-----------------------------------------------------------------------------------------------------------------		
	// Printing results to files 
	
	for(i=1 ; i<= 800 ; i++){
		for(j=0;j<n;j++){
			fprintf(f_V,"%f",Neuron[j].V[i] + Neuron[j].Vspike[i]);
			fprintf(f_V,"\t");
			fprintf(f_Rate,"%f",Neuron[j].rate[i] );
			fprintf(f_Rate,"\t");
		}
		fprintf(f_V,"\n");
		fprintf(f_Rate,"\n");
}
	for(j=0;j<n;j++){
		for(i=1;i<=800;i++){
			if(Neuron[j].rate[i] > 0.3)
				{
					printf("neuron %d crosses at %d\n",j+1,i);
					break;
				} 		
			}
		}
	fclose(f_V);
	fclose(f_Rate);
}
