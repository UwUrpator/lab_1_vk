#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//read array of strings
void read_str_arr(struct Array* arr) {
	char str[STR_SIZE];
	
	for (int i = 0; i < arr->count; i++){
		fgets(str, sizeof(str), stdin);

		while (strcmp(str, "\n") == 0) {
			fgets(str, sizeof(str), stdin);
		}
		if (str[strlen(str) - 1] == '\n') {
			str[strlen(str) - 1] = '\0';
		}
		set(arr, i, &str);
	}
}

//print array of string
void print_str_arr(struct Array* arr) {
	printf("( ");
	for (int i = 0; i < arr->count; i++) {
		printf("[\"%s\"] ", ((char*)(get(arr, i))));
	}
	printf(")\n");
}

