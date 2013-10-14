
// nazwa pliku podana w opcjach musi byc bezpiecznie skopiowana do zmiennej testowej
// dopiero potem mozna ja wstawic do funkcji fopen

#include <stdio.h>     // obsluga IO, takze funkcja perror
#include <stdlib.h>    // dodaje exit
#include <string.h>    // ze wzgledu na strlen

// opcje: 
//   nazwa pliku do wczytania

// zmienne globalne

int main( int argc, char** argv ){

	// gdy nie podano nazwy pliku - konczymy program (czyli gdy liczba argumentow jest 1)
	if(argc!=2){
		printf("podaj nazwe pliku, ziom.\n");
		exit(1);   // zakonczenie z kodem wyjscia 1 - czyli zwykle jakis blad
	             // program konczony z kodem 0 oznacza ze bylo wszystko OK.
	}

	int len = strlen(argv[1])+1;  // dlugosc nazwy pliku podanego w opcjach
	char nazwa[len];              // rezerwacja zmiennej na nazwe pliku

	// przepisanie nazwy pliku z tablicy argv do zmiennej (aby fopen to przyjal)
	// niestety, nie mozna przepisac napisu tak: nazwa = argv[1]
	// - to sa tablice znakow, wiec tak nie dziala
	snprintf(nazwa,len,"%s",argv[1]);

	FILE *file = fopen(nazwa,"r");  // otwieranie pliku o nazwie argv[1] w trybie 'read'
	                                  // jezeli sie udalo, file NIE jest zerem, wiec if dziala
	if(file){
		printf("plik '%s' otwarto! No i sie cieszymy.\n",nazwa);
		fclose(file);
	}
	else{
		printf("niestety, pliku '%s' nie dalo sie otworzyc\n",nazwa);
		perror("przyczyna");
	}
	
}



// [c] piotao, 20131007

