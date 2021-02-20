#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_int(void* v1, void* v2) {
	if (*(int*)v1 < *(int*)v2) {
		return -1;
	} 
	else if (*(int*)v1 > *(int*)v2) {
		return 1;
	}

	return 0;
}

