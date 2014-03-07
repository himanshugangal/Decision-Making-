#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define p 1000
#define q 1000
#define n 2 
#define B 4
#define C 1
float tt = 10; // Total time for simulation
float dt = 0.001; // Time step for simulation
float T = 0.2 ; // Tau value for modelling the behavior 
typedef struct neuron{ //Defining a structure for an individual neuron
		float In[p];
		float dx[p];
		float x[p];
		float V[p];
		float Spike[p];	
		float fr[q] ; 
		float dfr[q] ; 
		
		};

//------------------------------------------------------------------------------------------------------------------------------------------------------

int main()

{
	float z,tmp,sum,f = 0 ;
	struct neuron cell[n] ; // Defining an array of neurons with the declared structure 
	int i , j , k ; 
	int d = 2 ;
	int test = 500 ; 
 // Index for delay b/w spike and epsp
	//--------------------------------------------------------------------------------------------------------------------------------------------------	
// Initialising system arrays to zero 

for(j=0 ; j < n ; j++){

	for(i=1 ; i <= p ; i++){

			cell[j].dx[i] = 0 ;
			cell[j].In[i] = 0 ;
			cell[j].x[i]  = 0 ;
			cell[j].V[i]  = 0 ; 
			cell[j].Spike[i] = 0 ;  
			cell[j].fr[q] = 0 ; 
			cell[j].dfr[q] = 0 ;

		}

}

//------------------------------------------------------------------------------------------------------------------------------------------------------
// Give inputs to the neurons  . 

		//printf("Current till 4secs for decision %d  neuron  " , j+1);
		//scanf("%f",&tmp);
		for(i=1;i<=test;i++)
			{
				cell[0].In[i] = 5 ; 
				cell[1].In[i] = 0 ;
		}
		//printf("Current from 4 to 10secs for decision %d neuron  " , j+1 );
		//scanf("%f",&tmp);
		for(i=test+1;i<=1000;i++)
			{
				cell[0].In[i] = 0 ; 
				cell[1].In[i] = 5 ; 
		}
	
//-----------------------------------------------------------------------------------------------------------------------------------------------------
//Generating o/p from the neurons with
FILE *frtest ;
frtest = fopen("Firing rates testing.txt" , "w");
int a=0 ;
int b ;
int o = 0  ; 
float c,sum_1 = 0;  
b = 0 ; 
for( j = 0 ; j < n ; j++ ) {
		
		for ( i = 1 ; i<= p ; i++ ) {

			for(o=0 ; o<n ; o++)
			{
				if(o==j) { break; }
				else {
				sum_1 = sum_1 + cell[o].In[i] ; 
					}
				}
			cell[j].V[i+1] = cell[j].V[i] + cell[j].In[i]*(dt/C)*i -0.1*sum_1 ; 

			if(cell[j].V[i+1] >= 10)

			{
			b = b + 1 ; 
			c = i - a ;
			cell[j].fr[b] = 1 / c ;
			cell[j].V[i+1] = 0 ;
			cell[j].Spike[i] = 100 ; 
			for ( k = 1 ; k <= 50 ; k++ ) {
					
					if(i+k+d<=p){
						z = 10*exp(-k/10);
						cell[j].x[i+k+d] = cell[j].x[i+k+d] + z ; 	
						}
			
					}
			
			a = i ; 	
			}
			
			}
		
	}
fclose(frtest);

FILE *frtest1 ;
frtest1 = fopen("Firing rates testing.txt" , "w");

		for(j=0;j<n;j++){
			for(i=1;i<=b;i++){
			fprintf(frtest1,"%f \n" , cell[j].fr[i]);		
			
			}
			fprintf(frtest,"\t %d \n" , i);	
	}
fclose(frtest1);

FILE *fp1 ; 
fp1 = fopen("Voltage values.txt","w");
for(i=1;i<=1000;i++)
	{
		for(j=0;j<n;j++)

				{ fprintf(fp1,"%f \t",cell[j].V[i] + cell[j].Spike[i]);}
				
		fprintf(fp1,"\n");	
	
	}
fclose(fp1);

//------------------------------------------------------------------------------------------------------------------------------------------------------
// Appllying the leakage , laterabal ihibition model to the neural o/p
//FILE *fp2 ;
//fp2 = fopen("Decision output.txt","w");
for(i=1;i<=q;i++){
		
		for ( j= 0 ; j< n ; j++ ) { 

			sum = 0 ; 
				for ( k = 0 ; k < n ; k++ ){

						if ( j == k ) { continue ; }
						else { 
								if(cell[k].fr[i-1]<0){f=0;}
									else { f = cell[k].fr[i-1] ; }
										sum = sum + f ; }}

				   cell[j].dfr[i] = ( 1/cell[j].In[i] - cell[j].fr[i-1] - B*sum )*dt/T ; 
				   cell[j].fr[i] = cell[j].fr[i-1] + cell[j].dfr[i] ; 	
				   //fprintf(fp2,"%f \t",cell[j].x[i]);		
			   }

		//fprintf(fp2,"\t %d \n" , i);
}									 
//fclose(fp2);
FILE *dr ;
dr = fopen("Firing rates.txt" , "w");
for(i=1;i<=q;i++){
		for(j=0;j<n;j++){
			fprintf(dr,"%f \t" , cell[j].fr[i]);		
			
			}
			fprintf(dr,"\t %d \n" , i);	
	}
fclose(dr);
}
