#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* mult2(void* a) {
	int* res_p = malloc(sizeof(a));
	int res = *(int*)a * 2;

	memcpy(res_p, &res, sizeof(&a));

	return res_p;
}

void* add_excl(void* a) {
	char* res_p = malloc(sizeof(a));
	char res[STR_SIZE];

	strcpy(res, a);
	strcat(res, "!");

	memcpy(res_p, &res, sizeof(res));

	return res_p;
}

int is_div2(void* a) {
	if (*(int*)a % 2 == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int is_len3(void* a) {
	if (strlen(a) == 3) {
		return 1;
	}
	else {
		return 0;
	}
}

