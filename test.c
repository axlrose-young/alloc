#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alloc.h"
#define SIZE 10

int main(){
	char* arr6 = alloc(100);

	char* arr7 = alloc(200);
	read_metadata(arr6);
	read_metadata(arr7);

	unbound(arr6);
	
	/*
	read_metadata(arr1);
	read_metadata(arr2);
	read_metadata(arr3);
	read_metadata(arr4);	
	read_metadata(arr5);	
	
	mem_push(arr2);
	mem_push(arr4);
	mem_push(arr5);

	read_metadata(arr1);

	mem_push(arr3);

	read_metadata(arr2);
	read_metadata(arr3);
	read_metadata(arr4);
	read_metadata(arr5);
	*/
}
