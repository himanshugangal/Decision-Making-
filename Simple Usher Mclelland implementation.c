// Simple 2 free variable implementation of the Usher and Mclelland Algorithm


#include <stdio.h>
#include <stdlib.h>
#define p 

int main()

{
   
	float f1 , f2 ;
	float x1[p]; // free variables  
	float x2[p];
	float dx1[p] ; // activation variables  
	float dx2[p] ; 
	int i;
	float in1[p],in2[p] ; 
	
	// Inputs to the system 
	//-------------------------------------------------------------------
	for(i=1;i<=200;i++)
	{
	in1[i] = 10;
	in2[i] = 10;
	}

	for(i=201 ; i<= p ; i++)
	{
	in1[i] = 40;
	in2[i] = 20;
	}
	//--------------------------------------------------------------------
	// Initialising the free variables 
	
	for(i=1;i<=p;i++)
	{
	x1[i] = 0 ;
	x2[i] = 0 ;
	dx1[i] = 0 ; 
	dx2[i] = 0 ; 
	}
	
	//---------------------------------------------------------------------
	// Implementing the algorithm 

	FILE *fp ;
	fp = fopen("gg.txt","w");

	for(i=1;i<=p;i++)
	{

	if(x2[i-1] < 0 ) { f2 = 0 ; }
	else { f2 = x2[i-1]; }
	dx1[i] = ( in1[i] - x1[i-1] - 0.5*f2 ) * 0.01 ; // This term involves excitation , leakage and lateral inhibition 
	x1[i] = x1[i-1] + dx1[i] ; 

	if(x1[i-1] < 0 ) { f1 = 0 ; }
	else { f1 = x1[i-1]; }
	dx2[i] = ( in2[i] - x2[i-1] - 0.5*f1 ) * 0.01 ; 
	x2[i] = x2[i-1] + dx2[i] ; 
	

	//---------------------------------------------------------------------
	// Printing to the files 
			
	fprintf(fp,"%f \t %f \t %d \n ", x1[i] , x2[i] , i); 
	//fprintf(fp,"%f \t %f \t %f \t %f \t %f \t %f \t %d \n" , x1[i] , x2[i] ,in1[i] , in2[i], dx1[i] , dx2[i] , i ); 
	
	}
	fclose(fp);
	}

