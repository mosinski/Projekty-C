#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#include "timers.h"

int main(int argc, char **argv) {
	int np, rank;
	int size = atoi(argv[1]);
	int matrix[size][size]; //[wiersz][kolumna]
	int vector[size];
	
	int result[size];

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	int partition = size / np;
	int subresult[partition];
	int submatrix[size*partition];
	pTimer T = newTimer(); //deklaruje czas T
	double gotowe_time; //zmienna pod która bedę podstawiał czas do wyświetlenia

	int i, j;
	
	/* Walidacja równego podziału na macierzy na procesy */
	if ((size <= 0) || ((size % np) != 0)){
	   if (rank == 0){
	      printf("Nie mogę tego równo podzielić! Koniec.\n");
	   }
	   MPI_Finalize();
	   return 0;
	}
	
	if(rank == 0) {
		srand(time(0));
		for(i = 0; i < size; i++) {
			for(j = 0; j < size; j++) {
				matrix[i][j] = (int)(rand() % 10);
			}
		}
		for(i = 0; i < size; i++){
		   vector[i] = (int)(rand() % 10);
		} 
	}
	
	/*
		czyszczenie wszystkich zmiennych żeby nie było cudów
	*/
		for(i = 0; i < size; i++) {
		   result[i] = 0;
		}
		for(i=0; i < size*partition; i++) {
		   submatrix[i]=0;
		}
		for(i=0; i < partition; i++) {
		  subresult[i]=0;
		}
		
	startTimer(T);           // czas start
	
	/*
	   	Dziel na wiersze i wysyłam do procesów
	*/
	
	MPI_Scatter(matrix, size*partition, MPI_INT, submatrix, size*partition, MPI_INT, 0, MPI_COMM_WORLD);
		
	/*
		Broadcast wysyłam vektor do każdego procesu
	*/
	MPI_Bcast(vector, size, MPI_INT, 0, MPI_COMM_WORLD);

	/*     
		Każdy proces liczy swój wiersz
	*/
	for(i=0; i<partition; i++){
	   for(j=0; j<size; j++){
	      subresult[i]+= submatrix[j+size*i] * vector[j]; //size*i żeby przeskoczył do następnego wiersza jeśli otrzyma ich kilka
	   }
	}
	
	/*
		Proces zbiera wyniki i skleja je do result
	*/
	MPI_Gather(subresult, partition, MPI_INT, result, partition, MPI_INT, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
	     stopTimer(T);  // czas stop
	     gotowe_time = getTime(T); //podstawiam czas
	     printf("Koniec obliczeń, czas obliczeń = %f\n", gotowe_time);
	     if(size<8){
		     for(i = 0; i < size; i++) {
			   for(j=0; j < size; j++){
			     printf("%d\t",matrix[i][j]);
			   }
			   printf("|%d\t| %d\t\n", vector[i],result[i]);
		     }
	    }
	    else {
	         printf("Nie wyświetle w terminalu poprawnie tak dużej macierzy\n");
	    }
	}
	
	MPI_Finalize();
	
	return 0;
}
