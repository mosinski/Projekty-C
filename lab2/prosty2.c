
// ten program mozna uruchomic z argumentami, czyli np. 
// prosty2 -c 1 --help blabla lala zupa

#include <stdio.h>
#include <stdlib.h>

// opcje programu uruchamianego w unix/linux:
// argc = liczba argumentow (zawsze co najmniej 1) (argument count)
// argv = tablica argumentow w postaci napisow     (argument value)
int main( int argc, char** argv ) {

	// wypisanie liczby argumentow - napis zawiera %i, ktore jest zastepowane liczba calkowita
	printf("Liczba argumentow uruchomieniowych: %i\n",argc);
	
	// typowa petla od-do indeksowana od 0 do argc-1 wlacznie, wypisuje z tablicy napisy
	// jezeli podano jakies argumenty programu
	int i;
	for(i=0;i<argc;i++){
		printf("Argument %i: '%s'\n",i,argv[i]);
	}

	return 0;
}


// [c] piotao, 20131007

