#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mem_alloc.h"
#define SIZE 10

int main(){
	char* arr1 = mem_pull(SIZE);
	//int* arr3 = mem_pull(SIZE*4);		
	//char* arr4 = mem_pull(SIZE);
	//char* arr5 = mem_pull(SIZE);

	char* arr2 = mem_pull(SIZE);

	char* arr3 = mem_pull(SIZE);
	//char* arr4 = mem_pull(SIZE);
	
	mem_push(arr3);
	mem_push(arr2);
	//char* arr5 = mem_pull(SIZE);
	//char* arr6 = mem_pull(SIZE);
	//char* arr7 = mem_pull(SIZE);
	//mem_push(arr6);
	//mem_push(arr7);
	
	read_metadata(arr1);
	read_metadata(arr2);
	read_metadata(arr3);
	//read_metadata(arr4);
	//read_metadata(arr5);
	//read_metadata(arr6);
	//read_metadata(arr7);
}
