#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//read array of int
void read_int_arr(struct Array* arr) {
	int a;

	for (int i = 0; i < arr->count; i++){
		scanf("%d", &a);
		set(arr, i, &a);
	}
}

//print array of int
void print_int_arr(struct Array* arr) {
	printf("( ");
	for (int i = 0; i < arr->count; i++) {
		printf("[%d] ", *((int*)(get(arr, i))));
	}
	printf(")\n");
}

