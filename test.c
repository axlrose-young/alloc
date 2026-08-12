#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mem_alloc.h"
#define SIZE 10

int main(){
	char* arr1 = mem_pull(SIZE);
	char* arr2 = mem_pull(SIZE*2);
	int* arr3 = mem_pull(SIZE*4);

	for(int i = 0; i < SIZE; i++){
		arr1[i] = 'c';
	}

	for(int i = 0; i < SIZE; i++){
		printf("array %d: %c\n",i+1,arr1[i]);
	}

	for(int i = 0; i < SIZE*2; i++){
		arr2[i] = 'i';
	}

	for(int i = 0; i < SIZE*2; i++){
		printf("array %d: %c\n",i+1,arr2[i]);
	}

	for(int i = 0; i < SIZE; i++){
		arr3[i] = 6;
	}

	for(int i = 0; i < SIZE; i++){
		printf("array %d: %d\n",i+1,arr3[i]);
	}

	read_metadata(arr1);
	read_metadata(arr2);
	read_metadata(arr3);
}
