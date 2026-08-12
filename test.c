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
	for(int i = 0; i < SIZE*2; i++){
		arr2[i] = 'i';
	}
	for(int i = 0; i < SIZE; i++){
		arr3[i] = 6;
	}	
	char* arr4 = mem_pull(SIZE);

	read_metadata(arr1);
	read_metadata(arr2);
	read_metadata(arr3);
	read_metadata(arr4);	

	mem_push(arr2);
	mem_push(arr3);
	mem_push(arr1);

	read_metadata(arr1);
	read_metadata(arr2);
	read_metadata(arr3);
	read_metadata(arr4);
	
}
