#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_str(void* v1, void* v2) {
	if (strcmp((char*)v1, (char*)v2) < 0) {
		return -1;
	}
	else if (strcmp((char*)v1, (char*)v2) > 0) {
		return 1;
	}
	return 0;
}

