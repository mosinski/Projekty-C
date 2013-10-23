/*
Przy rozwiązaniu mpi przy 4 procesach uzyskujemy średni czas 0.014
przy rozwiazaniu sekwencyjnym: 0.004
Widać dużą stratą czasu na komunikacji....
*/

#include <stdio.h>
#include <time.h>
#include "timers.h"

int main(int argc, char **argv){	
	if (argc > 1) {
		int size;
		if (sscanf(argv[1], "%d", &size)) {
			printf("Licze  dla macierzy kwadratowe stopnia n=%d\n", size);
			double gotowe_time;
			int matrix[size][size]; // [wiersz][kolumna]	
			int vector[size]; //definicja wektora
			int result[size]; //definicja wektora wyniku
			int i,j,k;
			pTimer T = newTimer();     // we will measure time in each thread now
		
			srand(time(0));

			// czyszczenie wektora rozwiązania
			for (i = 0; i < size; i++) {
				result[i] = 0;
			}

			// wypełniam macierz randomowe wartości
			for (i = 0; i < size; i++) {
				for (j = 0; j < size; j++){
					matrix[i][j] = (int)(rand() % 10);	
				}
				vector[i] =  (int)(rand() % 10);	
			}

			//właściwe mnożenie macierzy przez wektor
				startTimer(T);           // start timer!
				for (i = 0; i < size; i++) { //przesuwam sie powierszach
					for (j = 0; j < size; j++){  //przesuwam sie po kolumnach
						result[i] += matrix[i][j] * vector[j];
					}
				}
				stopTimer(T);            // store time
				gotowe_time = getTime(T);
				printf("Koniec obliczeń, czas obliczeń = %f\n", gotowe_time);

			//wyświetlanie wyniku
			if (size <= 8) {
				for (i = 0; i < size; i++){
					for (j = 0; j < size; j++){
						printf("%d\t",matrix[i][j]);
					}
					printf("| %d\t|", vector[i]);
					printf("| %d\t|\n", result[i]);
				}
			}
			else {
				printf("Nie mogę wyświetlić tak dużej tablicy w terminalu\n");
			}
		} else {
			printf("Zly paramter wywoałania programu! Musi to być liczba.\n");
		}
	}	else {
		printf("Uruchomienie programu: %s rozmiar macierzy\n",argv[0]);
	}
	
return 0;

}


