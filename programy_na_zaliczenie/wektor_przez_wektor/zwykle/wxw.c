/* 
Wnioski: 
   Program działa bardzo szybko jedyne obciązenie to wielkośc wektorów i przez to ilość obrotów w pętli for
   średni czas to: 0.000060
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timers.h"

#define N 1000

int main(int argc, char **argv){

 int vectorX[N];
 int vectorY[N];
 int result;
 pTimer T = newTimer();
 startTimer(T);
 srand(time(0));
 int i;
 
 for(i=0;i<N;i++){
    vectorX[i] = rand() % 10;
    vectorY[i] = rand() % 10;
    result += vectorX[i] * vectorY[i];
    //printf("%d\t%d\n",vectorX[i],vectorY[i]);
 }
 
 stopTimer(T);
 printf("Wynik: %d \nCzas obliczen: %f\n",result,getTime(T));
 return 0;
}
