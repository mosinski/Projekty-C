/*
 * vector.h
 *
 *  Created on: Apr 22, 2010
 *      Author: piotao
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>   // for calloc
#include <string.h>   // for memset
#include "defs.h"


// simple data vector to keep them all like in an array
typedef struct Vector {
	int size;			// maximum length of data buffer
	pData data;			// data buffer by itself
} Vector;

// pointer to Vector data buffer
typedef Vector* pVector;

// create new instance of vector data
pVector newVector(int size){
	pVector V = (pVector) malloc(sizeof(Vector));
	memset(V,0,sizeof(Vector));
	V->data = (pData) calloc(size,sizeof(Data));
	memset(V->data,0,sizeof(Data)*size);
	V->size = size;
	return V;
}
// make new container, but don't initialize internal data buffer
pVector newNoVector(int size){
	pVector V = (pVector) malloc(sizeof(Vector));
	memset(V,0,sizeof(Vector));
	V->size = size;
	return V;
}

// delete vector and remove its data from memory
void freeVector(pVector V){
	if(V){
		if(V->data) free(V->data);
		free(V);
	}
}
// free container only, but do not touch
void freeNoVector(pVector V){
	if(V)	free(V);
}

void setVector(pVector V, Data x){
	if(V){
		int i;
		for(i=0;i<V->size;i++) V->data[i] = (Data) x;
	}
}

void randomizeVector(pVector V){
	if(V){
		int i;
		for(i=0;i<V->size;i++) V->data[i] = (Data) drand48();
	}
}

void printV(pVector V,int count){
	if(V){
		if(count<0){
			if(-count>V->size) count = -V->size;
			int i;
			for(i=V->size+count;i<V->size;i++){
				printf("%.2f ",V->data[i]);
			}
		}
		else{
			if(count > V->size) count = V->size;
			int i;
			for(i=0;i<count;i++){
				printf("%.2f ",V->data[i]);
			}
		}
	}
}

void printVln(pVector V,int count){
	printV(V,count);
	printf("\n");
}

void printmsgVln(char* text, pVector V, int count){
	if(strlen(text)<1) printf("first [%i]: ",count);
	else printf(text,count);
	printVln(V,count);
}

#endif /* VECTOR_H_ */
