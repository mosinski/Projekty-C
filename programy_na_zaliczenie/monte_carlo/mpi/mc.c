#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mpi.h"

#include "timers.h"


int main(int argc, char **argv){	
	long int n = 10000000;
	long int in_circle = 0;
	double gotowe_time;
	double pi,x,y;
	int i, rank,np; 
	
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	pTimer T = newTimer();     // we will measure time in each thread now

	long int local_in_circle = 0;

	srand(time(0)+rank);

	if (argc > 1) {
		if (!sscanf(argv[1], "%ld", &n)) {
			if (rank == 0) {		
		 		printf("Zły paramter! Musi być liczbą całkowitą\n");
		 	}
		 	
		 	MPI_Finalize();
		 	return 0;
					
		}
		if (n % np != 0) {
			if (rank == 0) {
		   		printf("Nie mogę podzielić po równo!\n");
		   	}
	
		   	MPI_Finalize();
		   	return 0;
		}
	
	}	
	
	long int local_n = (long int) n/np;		

	if (rank == 0) {
	startTimer(T);           // czas start
	}

	for (i = 0; i < local_n; i++) {           
  	  x = ((double)rand() / (RAND_MAX))*2 - 1;
    	  y = ((double)rand() / (RAND_MAX))*2 - 1;
    	  
    	  if(x*x + y*y <= 1) {
    		local_in_circle++;
    	  }
  	}
   	printf("rank[%d]->Mój local_in_circle to %ld\n",rank,local_in_circle);

	MPI_Reduce(&local_in_circle, &in_circle, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);	
	
	if (rank == 0) {
		pi = 	4 * (double)in_circle / n;
	        stopTimer(T);  // czas stop
	        gotowe_time = getTime(T); //podstawiam czas
	        
		printf("\nDla liczby punktów w kole: %ld \n", n);
		printf("Z math.h \tPI = %.40lf\n", M_PI);
		printf("Wyliczone\tPI = %.40lf\n", pi);
		printf("Czas obliczeń = %f\n", gotowe_time);
	}
	
	MPI_Finalize();
	return 0;
}
