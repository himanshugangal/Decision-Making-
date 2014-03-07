

//----- Include files -------------------------------------------------------
#include <stdio.h>              // Needed for printf()
#include <stdlib.h>             // Needed for exit() and ato*()
#include <math.h>               // Needed for log()

//----- Function prototypes -------------------------------------------------
int    poisson(double x);       // Returns a Poisson random variable
double expon(double x);         // Returns an exponential random variable
double rand_val(int seed);      // Jain's RNG

//===== Main program ========================================================
int main()
{
  FILE     *fp,*fpisi;                 // File pointer to output file
  char     file_name[256];      // Output file name string
  char     temp_string[256];    // Temporary string variable
  double   lambda;              // Mean rate
  int      pois_rv;             // Poisson random variable
  int      num_values;          // Number of values
  int      i;                   // Loop counter

  // Output banner
  printf("-  Program to generate Poisson random variables        - \n");
  printf("-------------------------------------------------------- \n");

  // Prompt for output filename and then create/open the file
 
  fp = fopen("numbers.txt", "w");
  if (fp == NULL)
  {
    printf("ERROR in creating output file (%s) \n", file_name);
    exit(1);
  }

  fpisi = fopen("Rates.txt","w");	
  // Prompt for random number seed and then use it
  printf("Random number seed (greater than 0) ================> ");
  scanf("%s", temp_string);
  rand_val((int) atoi(temp_string));

  // Prompt for rate (lambda)
  printf("Rate in customers per second =======================> ");
  scanf("%s", temp_string);
  lambda = atof(temp_string);
  int runs,m ;
  printf("Number of runs ");
  scanf("%d",&runs);
  for(m=1;m<=runs ; m++){	
  // Prompt for number of values to generate
  printf("Number of values to generate =======================> ");
  scanf("%s", temp_string);
  num_values = atoi(temp_string);

  //Output message and generate interarrival times
  printf("-------------------------------------------------------- \n");
  printf("-  Generating samples to file                          - \n");
  printf("-------------------------------------------------------- \n");

  // Generate and output exponential random variables
//------------------------------------------------------------------------------------------------
// EPSP generation at the location of random input spikes 


float In[1000],y[1000] ; 
for(i=0;i<=1000;i++)
{
	In[i] = 0 ; 
	y[i] = 0 ; 
	}  
int d=2;
int g ;
float f,z; 
FILE *fp2 ; 
fp2 = fopen("EPSP.txt","w");
for (i=0; i<num_values; i++)
  {
    pois_rv = poisson(1.0 / lambda);
    fprintf(fp, "%d \n", pois_rv);
	In[pois_rv] = 100 ;
		for(g=0, f=0 ; f < 10 ; f++ , g++ )  	 
			{
				if(pois_rv+f+d<=1000){
				z = 10*exp(-f/4);
				fprintf(fp2,"%f \t %f \n",z,pois_rv+f+d);
				y[pois_rv+g+d] = y[pois_rv+g+d] + z ; 	
						}
			}
	 
 	 
	}

FILE *fp5;
fp5 = fopen("EPSPfinal.txt","w");
for(i=1;i<=1000;i++)
{
	fprintf(fp5,"%f \t %d \n" , y[i] , i );
	}
fclose(fp5);
//---------------------------------------------------------------------------------------------------
// Calculating the O/P of the neuron to random input spikes and the corresponding post synaptic current 

FILE *fp4,*fp3;
fp3 = fopen("EPSP1.txt","w");
fp4 = fopen("Final OP.txt","w");
float V[1000] , V1[1000] ; 
for(i=1;i<=1000;i++)
	{
		V[i] = 0 ;
		V1[i] = 0 ;	
	}
V[0] = 0 ;
float count = 0 ;
float rate ;
float tmpsum = 0;  
int q,p=05 ;  
float sum = 0 ;
int m = 0 ; 
for(i=1;i<1000;i++)
	{
		//tmpsum = tmpsum + y[i] ;  
		V[i] = V[i-1] + y[i]*0.0002*i;
		q = i ;
		if(V[i] > 10)
		{
			 
			count = i - p ;
			rate = 1/count ;
			if ( count >= 0 && count <= 20 ) {
					fprintf(fpisi,"%f \t %d \n ", rate , m ) ;
				}
			V1[i] = 108;
			V[i] = -8 ; 
			p = i ;
			m++;
			}
		fprintf(fp4,"%f \t  %f \t %f \t %d \n" , V1[i] + V[i] , y[i] , In[i], i );
		
		}
//---------------------------------------------------------------------------------------------
FILE *fp6;
fp6 = fopen("lambdavsV.txt","w");
for(i=1;i<=1000;i++)
{
	fprintf(fp6,"%f \t %f \n" , V[i] , lambda); 
	}
fclose(fp6);
fclose(fp3);
fclose(fp2);
fclose(fp4);

  //Output message and close the output file
  printf("-------------------------------------------------------- \n");
  printf("-  Done! \n");
  printf("-------------------------------------------------------- \n");
  fclose(fp);
}
  fclose(fpisi);
	}

//===========================================================================
//=  Function to generate Poisson distributed random variables              =
//=    - Input:  Mean value of distribution                                 =
//=    - Output: Returns with Poisson distributed random variable           =
//===========================================================================
int poisson(double x)
{
  int    poi_value;             // Computed Poisson value to be returned
  double t_sum;                 // Time sum value

  // Loop to generate Poisson values using exponential distribution
  poi_value = 0;
  t_sum = 0.0;
  while(1)
  {
    t_sum = t_sum + expon(x);
    if (t_sum >= 1.0) break;
    poi_value++;
  }

  return(poi_value);
}

//===========================================================================
//=  Function to generate exponentially distributed random variables        =
//=    - Input:  Mean value of distribution                                 =
//=    - Output: Returns with exponentially distributed random variable     =
//===========================================================================
double expon(double x)
{
  double z;                     // Uniform random number (0 < z < 1)
  double exp_value;             // Computed exponential value to be returned

  // Pull a uniform random number (0 < z < 1)
  do
  {
    z = rand_val(0);
  }
  while ((z == 0) || (z == 1));

  // Compute exponential random variable using inversion method
  exp_value = -x * log(z);

  return(exp_value);
}


//=========================================================================
double rand_val(int seed)
{
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0)
  {
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random value between 0.0 and 1.0
  return((double) x / m);
}
