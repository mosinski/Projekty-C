/*
Wnioski: Program działa wolniej od sekwencyjnego im więcej podamy procesorów tym dłużej będzie obliczał ponieważ na więcej części musi podzielić wektory
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include "timers.h"

#define N 1000

int main(int argc, char **argv){
	int size, rank;
	int vectorX[N];
	int vectorY[N];
	int result = 0;
	int subresult = 0;
	
	pTimer T = newTimer();
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	int podzial = N/size;
	int subvectorX[podzial];
	int subvectorY[podzial];

	int i;
	if(rank == 0){
	  srand(time(0));
	  startTimer(T);
	  for(i=0;i<N;i++){
		vectorX[i] = rand() % 10;
		vectorY[i] = rand() % 10;
		//printf("%d\t%d\n",vectorX[i],vectorY[i]);
	  }
	}

	MPI_Scatter(vectorX, podzial, MPI_INT, subvectorX, podzial, MPI_INT, 0, MPI_COMM_WORLD);//dziele i rozsyłam wektor nr 1
	MPI_Scatter(vectorY, podzial, MPI_INT, subvectorY, podzial, MPI_INT, 0, MPI_COMM_WORLD);//dziele i rozsyłam wektor nr 2
	
	for(i = 0; i<podzial; i++){
		subresult += subvectorX[i] * subvectorY[i];
		//printf("RANK[%d]: subresult: %d\n",rank,subresult);
	}
	
	MPI_Reduce(&subresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);	
	
	if(rank == 0){
		printf("Wynik: %d\n",result);
		stopTimer(T);
		printf("Czas obliczen: %f\n", getTime(T));	
	}
	
	MPI_Finalize();
	return 0;
}
