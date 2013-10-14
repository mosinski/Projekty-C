
/*
 * 20110308 [c]piotao,@venona, 4zonkg
 * simple implementation of parallel linear reduction done by forking
 */

#include <stdio.h>        // printf, etc.
#include <stdlib.h>       // memory allocation
#include <math.h>         // log, abs, etc.
#include <unistd.h>       // fork
#include <sys/wait.h>     // wait
#include "defs.h"         // my own datatypes
#include "timers.h"       // time measurements
#include "vector.h"       // simplified vector handling

#define EXT "out"

unsigned long int SIZE  = 1000000;   // -size 10 option for change size
unsigned int      FORK  = 3;         // three threads to run at once
unsigned int      LOUD  = 1;

// reduction is calculated as simple sum of linear vector, between given boundaries
// from vector[start] to vector[end-1] inclusive  (-1 is because of i<end, not i<=end)
Data reduceVector(register pVector vector, register int start, register int end){
	register int i;
	register Data sum = 0.0;
	if(vector){
		for(i=start;i<end;i++){
			sum += *(vector->data+i);
		}
	}
	return sum;
}

// write partial result to file with name of '10.out', etc.
void writeOutputFile( int nr, Data sum ){
	FILE *f;
	char* name = (char*) malloc((int) (log(abs(nr))+2));  // allocate ram for filename
	sprintf(name,"%i.%s",nr,EXT);
	f = fopen( name, "w" );
	if(f){
		fprintf(f,"%1.10e\n", sum);
		fclose(f);
	}
	free(name);
}

// read single line from file given as a number with extension
Data readLineFromFile( int nr ){
	FILE *f;
	double value = -1.0;
	char* name = (char*) malloc((int) (log(abs(nr))+2)); // ram for filename
	sprintf(name,"%i.%s",nr,EXT);
	f = fopen( name, "r" );
	if(f){
		fscanf(f,"%lf\n",&value);
		fclose(f);
	}
	free(name);
	return value;
}

// parsing options just changes some global variables
void parseOptions(int argc, char** argv){
	int i = 0;
	while(i < argc){
		if(!strcmp(argv[i],"-size")) SIZE = atoi(argv[++i]);  // size of the vector
		if(!strcmp(argv[i],"-fork")) FORK = atoi(argv[++i]);  // number of threads spawned by fork
		if(!strcmp(argv[i],"-q"))    LOUD = 0;
		if(!strcmp(argv[i],"-quiet")) LOUD = 0;
		i++;
	}
}

// main prog: can be called with option: number of elements in vector
int main( int argc, char** argv ){

	Data sum = 0.0;

	parseOptions(argc,argv);
	printf("[i] vector size is:  %li\n",SIZE);
	printf("[i] forks requested: %i\n", FORK);
	printf("[i] total mem for data: %1.2f MB\n",SIZE*sizeof(Data)/1024.0/1024.0);
	printf("\n");

	pVector V = newVector(SIZE);
	setVector(V,1.0);

	int pid;        // temporary variable for storing pid of child
	int forked = 0; // how many childs we created
	int master = 0;
	int i;

	do{
		if( (pid = fork()) ){ // master, we have pid of child
			if(LOUD) printf("[i] master: fork %i with pid %i spawned\n",forked,pid);
			forked++;  // on master forked is child count
			master = 1;
		}
		else{
			master = 0;// force write to ensure each child has it's own copy and it is 0
			forked++;  // forked is fork number in child
			if(LOUD)printf("[i] fork nr %i is reducing from %li to %li\n",forked,(forked-1)*SIZE/FORK,forked*SIZE/FORK);
			pTimer T = newTimer();
			startTimer(T);
			sum = reduceVector( V, (forked-1)*SIZE/FORK, forked*SIZE/FORK );
			stopTimer(T);
			printf("fork nr %i, sum=%f, time = %f\n",forked,sum,getTime(T));
			freeTimer(T);
			writeOutputFile( forked, sum );
		}
	} while( forked < FORK && pid != 0 );   // we ensure ONLY master will continue loop
	
	int status;
	if(master){
		printf("on master, ensure all finished\n");
		i = forked;
		while(i){
			pid = wait(&status);
			if(pid>0){
				if(LOUD)printf("[i] fork with pid %i finished with status %i\n",pid,status);
				i--;
			}
		}
		printf("after all, let's collect data from files\n");
		sum = 0.0;
		for(i=1;i<=forked;i++){
			Data value = readLineFromFile(i);
			if(LOUD)printf("[o] read result from %i fork: %f\n",i,value);
			sum += value;
		}
		printf("[O] total value of reduction is %f\n",sum);
	}

	freeVector(V);
	return 0;
}


