#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "timers.h"

int main(int argc, char **argv){	
	long int n = 10000000;
	long int in_circle = 0;
	double gotowe_time;
	double pi,x,y;
	int i; 
	pTimer T = newTimer();     // we will measure time in each thread now
	
	if (argc > 1) {
		if (!sscanf(argv[1], "%ld", &n)) {
			printf("Zły paramter! Musi być liczbą całkowitą\n");		
		}
	}		
	
	srand(time(0));
	startTimer(T);           // start timer!
	for (i = 0; i < n; i++) {           
         x = ((double)rand() / (RAND_MAX))*2 - 1; //losowanie pozycji x z zakresu od -1 do 1
         y = ((double)rand() / (RAND_MAX))*2 - 1; //losowanie pozycji y z zakresu od -1 do 1
         
         if(x*x + y*y <= 1) {
             in_circle++;
         }
  	}
		
	pi = 	4 * (double)in_circle / n;
	stopTimer(T);            // store time
	gotowe_time = getTime(T);

	printf("Dla liczby punktów w kole: %ld \n", n);
	printf("Z math.h \tPI = %.40lf\n", M_PI);
	printf("Wyliczone\tPI = %.40lf\n", pi);
	printf("Czas obliczeń = %f\n", gotowe_time);
	

	return 0;
}
