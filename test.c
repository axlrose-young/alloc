#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alloc.h"
#define SIZE 10

int main(){
	char* arr6 = alloc(100);
	char* arr7 = alloc(200);
	char* arr8 = alloc(50);

	unbound(arr7);

	char* arr9 = alloc(150);

	read_metadata(arr6);
	read_metadata(arr9);
	read_metadata(arr8);
}
