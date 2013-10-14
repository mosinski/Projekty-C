
/*
 * 20110310 [c]piotao, @maon, 4zonkg
 * simple pthread-oriented implementation for parallel linear reduction
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"
#include "vector.h"
#include "timers.h"

unsigned long int SIZE  = 1000000;  // change it by -size X option
unsigned int      PTHR  = 3;        // number of threads to spawn, -thr X option
unsigned short int LOUD = 1;        // print messages, etc. (disable with -quiet or -q)

// we have to use barrier because all threads really HAVE to finish their work, before we can compute
// total sum from all partial results. So, here we have to declare barrier structure, for barrier control.
pthread_barrier_t barrier;


// this is data set passed to each thread. It contains pointer to all data, start/end and sum values
typedef struct Info {
	Data sum;   // sum calculated from specified data
	pVector V;    // pointer to data vector
	int start;    // starting point (from where to start, inclusive)
	int end;      // end point
	pthread_t id; // thread id, not necessary, only for result from pthread_create
	int nr;       // thread nr, not necessary, only for nice printing
	double time;  // how long thread worked, all have independent time
} Info;
typedef Info* pInfo; // pointer to this structure (we can pass only one arg to reduceVector)


// this function is our reduction function, it will be executed in parallel by threading
// as a multiple threads sharing the same vector, and adding diffrent regions from it
// data here is a pointer to struct Info with all necessary fields, like vector itself,
// start and end of region to calculate and sum. There are also some other less important things.
void* reduceVector(void* data){
	int i;
	pTimer T = newTimer();     // we will measure time in each thread now
	pInfo info = (pInfo) data; // copy data structure
	info->time = 0.0;          // time is zero at start
	if(info->V){               // if we have anything
		startTimer(T);           // start timer!
		for(i=info->start; i<info->end; i++){
			(info->sum) += (info->V->data[i]);      // add all values to the sum
		}
		stopTimer(T);            // store time
		info->time = getTime(T); // get time as a double precision value
		if(LOUD) printf("[i] thread %i, sum=%f, time=%1.4e\n",info->nr,info->sum,info->time);
	}
	freeTimer(T);

	// wait for all other threads to finish.
	int rc = pthread_barrier_wait(&barrier);
	if(rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD){
		fprintf(stderr,"[E] Could not wait on barrier for some reason, code=%i\n",rc);
		exit(-1);
	}
	pthread_exit(NULL); // exit nicely
}

// parsing options just changes some global variables
void parseOptions(int argc, char** argv){
	int i = 0;
	while(i < argc){
		if(!strcmp(argv[i],"-size")) SIZE = atoi(argv[++i]);  // size of the vector
		if(!strcmp(argv[i],"-thr"))  PTHR = atoi(argv[++i]);  // number of threads spawned by fork
		if(!strcmp(argv[i],"-quiet"))LOUD = 0; 								// disable messages (usable for very many threads)
		if(!strcmp(argv[i],"-q"))    LOUD = 0; 								// disable messages (usable for very many threads)
		i++;
	}
}


// now main program, as usual, with some options parsing, etc.
int main(int argc, char** argv){

	int i;
	pTimer T = newTimer(); startTimer(T); // let's measure execution time of the whole program.
	// options parsing, configuration and reporting variables
	parseOptions(argc,argv);
	printf("[i] vector size is:    %li\n",SIZE);
	printf("[i] threads requested: %i\n", PTHR);
	printf("[i] total mem for data: %1.2f MB\n",SIZE*sizeof(Data)/1024.0/1024.0);
	if(PTHR<=0){printf("Too few threads, exiting...\n");exit(0);}
	printf("\n");

	// preparing data for calculations
	pVector V = newVector(SIZE); setVector(V,1.0);

	// preparing barrier for all threads involved in calculations
	if(pthread_barrier_init( &barrier, NULL, PTHR)){
		fprintf(stderr,"[E] could not create barrier!\n");
		exit(-1);
	}

	// preparing threads for calculations
	Info threads[PTHR];
	for(i=0;i<PTHR;i++){
		threads[i].nr = i;
		threads[i].V = V;
		threads[i].sum = 0.0;
		threads[i].start = (i  )*SIZE/PTHR;
		threads[i].end   = (i+1)*SIZE/PTHR;
		int rc = pthread_create(&threads[i].id,NULL,reduceVector,(void*) &threads[i]);
		if(rc){
			fprintf(stderr,"[E] thread creation error, code returned: %i\n",rc);
			exit(-1);
		}
		else{
			if(LOUD) printf("[i] thread %i: start=%i, end=%i\n",i,threads[i].start,threads[i].end);
		}
	}

	for(i=0;i<PTHR;i++){
		if(pthread_join(threads[i].id,NULL)){
			fprintf(stderr,"[e] Can't join thread id=%li, nr=%i\n",threads[i].id,threads[i].nr);
			return -1;
		}
	}
	// at the end we have to collect all data from threads
	double sum = 0.0;
	double time = 0.0;
	for(i=0;i<PTHR;i++){
		sum += threads[i].sum;
		time+= threads[i].time;
	}
	stopTimer(T);
	printf("Main sum is %1.2f, avg thread time: %-1.12f s, TOTAL time: %1.12f\n",sum,time/PTHR,getTime(T));
	freeTimer(T);
}

