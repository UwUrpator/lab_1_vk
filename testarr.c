#include "array.h"
#include "cmpint.h"
#include "cmpstr.h"
#include "demofun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_create_arr_int() {
	int default_int = 0;

	struct Array* arr = create_arr(3, sizeof(int), &default_int);
	
	if (*(char*)get(arr, 0) == 0 
	 && *(char*)get(arr, 1) == 0 
	 && *(char*)get(arr, 0) == 0
	) {
		return 1;
	}

	return 0;
}

int test_create_arr_str() {
	char default_str[STR_SIZE] = "0";

	struct Array* arr = create_arr(3, sizeof(int), &default_str);
	
	if (strcmp(get(arr, 0), default_str) == 0 
	 && strcmp(get(arr, 1), default_str) == 0 
	 && strcmp(get(arr, 2), default_str) == 0
	) {
		return 1;
	}

	return 0;
}

int test_copy_arr_int() {
	int default_int = 0;
	int count = 10;

	struct Array* arr = create_arr(count, sizeof(int), &default_int);
	struct Array* copied_arr;	
	
	for (int i = 0; i < count; i++) {
		set(arr, i, &i);
	}

	copied_arr = copy_arr(arr);

	for (int i = 0; i < count; i++) {
		if (*(int*)get(copied_arr, i) != i) {
			return 0;
		}
	}

	return 1;
}

int test_copy_arr_str() {
	char default_str[STR_SIZE] = "0";
	int count = 10;

	struct Array* arr = create_arr(count, sizeof(int), &default_str);
	struct Array* copied_arr;	
	
	for (int i = 0; i < count; i++) {
		set(arr, i, &i);
	}

	copied_arr = copy_arr(arr);

	for (int i = 0; i < count; i++) {
		if (*(int*)get(copied_arr, i) != i) {
			return 0;
		}
	}

	return 1;
}

int test_where_int() {
	int default_int = 0;
	int count = 10;

	struct Array* arr = create_arr(count, sizeof(int), &default_int);
	struct Array* arr_where;
	
	for (int i = 0; i < count; i++) {
		set(arr, i, &i);
	}

	arr_where = where(arr, is_div2);

	for (int i = 0; i < count; i+=2) {
		if (*(int*)get(arr_where, i / 2) != i) {
			return 0;
		}
	}

	return 1;
}

int test_where_str() {
	char default_str[STR_SIZE] = "0";
	char str1[STR_SIZE] = "a";
	char str2[STR_SIZE] = "abc";
	char str3[STR_SIZE] = "abcd";

	struct Array* arr = create_arr(3, sizeof(default_str), &default_str);
	struct Array* arr_where;

	set(arr, 0, &str1);
	set(arr, 1, &str2);
	set(arr, 2, &str3);

	arr_where = where(arr, is_len3);

	if (strcmp(get(arr_where, 0), str2) != 0) {
		return 0;
	}

	return 1;
}

int test_concat_int() {
	int default_int1 = 0;
	int default_int2 = 1;

	struct Array* arr1 = create_arr(1, sizeof(default_int1), &default_int1);
	struct Array* arr2 = create_arr(2, sizeof(default_int2), &default_int2);

	struct Array* arr3 = concat(arr1, arr2);
	
	if (*(int*)get(arr3, 0) == default_int1 
	 && *(int*)get(arr3, 1) == default_int2 
	 && *(int*)get(arr3, 2) == default_int2
	) {
		return 1;
	}

	return 0;
}

int test_concat_str() {
	char default_str1[STR_SIZE] = "0";
	char default_str2[STR_SIZE] = "1";

	struct Array* arr1 = create_arr(1, sizeof(default_str1), &default_str1);
	struct Array* arr2 = create_arr(2, sizeof(default_str2), &default_str2);

	struct Array* arr3 = concat(arr1, arr2);
	
	if (strcmp((char*)get(arr3, 0), default_str1) == 0 
	 && strcmp((char*)get(arr3, 1), default_str2) == 0 
	 && strcmp((char*)get(arr3, 2), default_str2) == 0
	) {
		return 1;
	}

	return 0;
}

int test_map_int() {
	int default_int = 0;
	int count = 10;

	struct Array* arr = create_arr(count, sizeof(int), &default_int);
	struct Array* arr_map;
	
	for (int i = 0; i < count; i++) {
		set(arr, i, &i);
	}

	arr_map = map(arr, mult2);

	for (int i = 0; i < count; i++) {
		if (*(int*)get(arr_map, i) != i * 2) {
			return 0;
		}
	}

	return 1;
}

int test_map_str() {
	char default_str[STR_SIZE] = "0";

	char str1[STR_SIZE] = "a";
	char str2[STR_SIZE] = "abc";
	char str3[STR_SIZE] = "abcd";

	char str1_map[STR_SIZE] = "a!";
	char str2_map[STR_SIZE] = "abc!";
	char str3_map[STR_SIZE] = "abcd!";

	struct Array* arr = create_arr(3, sizeof(default_str), &default_str);
	struct Array* arr_map;

	set(arr, 0, &str1);
	set(arr, 1, &str2);
	set(arr, 2, &str3);

	arr_map = map(arr, add_excl);

	if (strcmp(get(arr_map, 0), str1_map) == 0
	 && strcmp(get(arr_map, 1), str2_map) == 0
	 && strcmp(get(arr_map, 2), str3_map) == 0
	) {
		return 1;
	}

	return 0;
}

int test_sort_int() {
	int default_int = 0;
	int int1 = -2;
	int int2 = -1;
	int int3 = 1;
	

	struct Array* arr = create_arr(4, sizeof(default_int), &default_int);
	set(arr, 3, &int1);
	set(arr, 2, &int2);
	set(arr, 1, &int3);
	set(arr, 0, &int2);
	
	quick_sort(arr, 0, 3, cmp_int);

	if (*(int*)get(arr, 0) == int1 
	 && *(int*)get(arr, 1) == int2 
	 && *(int*)get(arr, 2) == int2 	
	 && *(int*)get(arr, 3) == int3
	) {
		return 1;
	}

	return 0;
}

int test_sort_str() {
	char default_str[STR_SIZE] = "0";
	char str1[STR_SIZE] = "a";
	char str2[STR_SIZE] = "abc";
	char str3[STR_SIZE] = "abcd";
	

	struct Array* arr = create_arr(4, sizeof(default_str), &default_str);
	set(arr, 3, &str1);
	set(arr, 2, &str2);
	set(arr, 1, &str3);
	set(arr, 0, &str2);
	
	quick_sort(arr, 0, 3, cmp_str);

	if (strcmp((char*)get(arr, 0), str1) == 0 
	 && strcmp((char*)get(arr, 1), str2) == 0 
	 && strcmp((char*)get(arr, 2), str2) == 0 	
	 && strcmp((char*)get(arr, 3), str3) == 0
	) {
		return 1;
	}

	return 0;
}

void run_tests() {
	printf("Tests result\n");

	if (test_create_arr_int() == 0) {
		printf("test_create_arr_int - Failed\n");
	}
	if (test_create_arr_str() == 0) {
		printf("test_create_arr_str - Failed\n");
	}
	if (test_copy_arr_int() == 0) {
		printf("test_copy_arr_int - Failed\n");
	}
	if (test_copy_arr_str() == 0) {
		printf("test_copy_arr_str - Failed\n");
	}
	if (test_where_int() == 0) {
		printf("test_where_int - Failed\n");
	}
	if (test_where_str() == 0) {
		printf("test_where_str - Failed\n");
	}
	if (test_map_int() == 0) {
		printf("test_map_int - Failed\n");
	}
	if (test_map_str() == 0) {
		printf("test_map_str - Failed\n");
	}
	if (test_concat_int() == 0) {
		printf("test_concat_int - Failed\n");
	}
	if (test_concat_str() == 0) {
		printf("test_concat_str - Failed\n");
	}
	if (test_sort_int() == 0) {
		printf("test_sort_int - Failed\n");
	}
	if (test_sort_str() == 0) {
		printf("test_sort_str - Failed\n");
	}
	if (test_create_arr_int() * test_create_arr_int() * test_copy_arr_int() 
	  * test_copy_arr_str() * test_where_int() * test_where_str()
	  * test_map_int() * test_map_str() * test_concat_int() * test_concat_str()
	  * test_sort_int() * test_sort_str()) {
		printf("OK\n");
	}
}
