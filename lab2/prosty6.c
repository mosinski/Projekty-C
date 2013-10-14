
// wczytanie liczb rzeczywistych z pliku o formacie:
// pierwsza linia - komentarz
// druga linia - jedna liczba z liczba nastepnych wierszy do wczytania
// nastepne linie - wiersze do wczytania

// taki program musi:
// 1. otworzyc plik
// 2. wczytac pierwsza linie i ja zapomniec
// 3. wczytac druga linie jako liczbe wierszy do wczytania
// 4. zrobic pamiec dla liczb wczytywanych
// 5. wczytywac do pamieci liczby az sie zakoncza

#include <stdio.h>     // obsluga IO, takze funkcja perror
#include <stdlib.h>    // dodaje exit
#include <string.h>    // ze wzgledu na strlen

// opcje: 
//   nazwa pliku do wczytania

// zmienne globalne
int   SIZE  = 0;   // wielkosc danych do wczytania

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
		printf("plik '%s' otwarto!\n",nazwa);
		char linia[256];                // zmienna napisowa o dlugosci max 256 znakow na bufor
		fgets(linia,256,file);          // wczytanie pierwszej linii
		printf("wczytano: %s",linia);
		fscanf(file,"%i\n",&SIZE);      // wczytanie drugiej linii z rozmiarem danych
		printf("Wczytano: %i - rozmiar danych\n",SIZE);

		double DANE[SIZE];
		int licznik = 0;
		while(licznik<SIZE && !feof(file)){
			fscanf(file,"%lf\n",&DANE[licznik]);
			printf("wczytano: %f jako liczbe %i\n",DANE[licznik],licznik);
			licznik++;
		}
		fclose(file);
		printf("plik zamknieto, teraz wypisywanie danych:\nwczytano:\n");
		int i;
		for(i=0;i<SIZE;i++) printf("wiersz %i: %lf\n",i,DANE[i]);
	}
	else{
		printf("niestety, pliku '%s' nie dalo sie otworzyc\n",nazwa);
		perror("przyczyna");
	}
	
	return 0; // ten return mozna pominac - kompilator doda sam.
}

// [c] piotao, 20131007

