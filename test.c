#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alloc.h"
#define SIZE 10

int main(){
	char* arr6 = alloc(100);

	char* arr7 = alloc(200);

	unbound(arr7);
	read_metadata(arr7);

	char* arr8 = alloc(50);
	read_metadata(arr6);
	read_metadata(arr8);	
}
