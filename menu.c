#include "array.h"
#include "cmpint.h"
#include "cmpstr.h"
#include "intio.h"
#include "strio.h"
#include "demofun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Array* create_menu(int arr_type) {
	struct Array* arr;
	int arr_count = -1;

	int default_int = 0;
	char default_str[STR_SIZE] = "0";

	void (*read_arr)(struct Array*);

	while (arr_count < 0) {
		printf("How much items do you want to see in your array? [Enter the number]: ");
		scanf("%d", &arr_count);
	}

	switch (arr_type) {
		case 1:
			arr	= create_arr(arr_count, sizeof(default_int), &default_int);
			read_arr = read_int_arr;
			break;
		case 2:
			arr	= create_arr(arr_count, sizeof(default_str), &default_str);
			read_arr = read_str_arr;
			break;
	}
	
	printf("Enter %d items of array:\n", arr_count);
	read_arr(arr);

	return arr;
}

void show_menu() {
	int arr_type = 0;
	struct Array* arr1;
	struct Array* arr2;
	struct Array* arr3;

	int (*cmp)(void*, void*);
	void (*print_arr)(struct Array*);

	while (arr_type != 1 &&  arr_type != 2) {
		printf("\nDo you want to create arrays of integers or arrays of strings? [1/2]: ");
		scanf("%d", &arr_type);
	}

	printf("\nDefinition of 1st array\n");
	arr1 = create_menu(arr_type);

	printf("\nDefinition of 2nd array\n");
	arr2 = create_menu(arr_type);
	
	switch (arr_type) {
		case 1:
			cmp = cmp_int;
			print_arr = print_int_arr;
			break;
		case 2:
			cmp = cmp_str;
			print_arr = print_str_arr;
			break;
	}
	
	printf("\n1st array:\n");
	print_arr(arr1);
	
	printf("\n2nd array:\n");
	print_arr(arr2);

	printf("\nConcatinated array:\n");
	arr3 = concat(arr1, arr2);
	print_arr(arr3);
	
	printf("\n1st array (sorted):\n");
	quick_sort(arr1, 0, arr1->count-1, cmp);
	print_arr(arr1);
	
	printf("\n2nd array (sorted):\n");
	quick_sort(arr2, 0, arr2->count-1, cmp);
	print_arr(arr2);

	printf("\nConcatinated array (sorted):\n");
	quick_sort(arr3, 0, arr3->count-1, cmp);
	print_arr(arr3);

	switch (arr_type) {
		case 1:
			printf("\nMultiply on 2 every item in concatinated array (map demonstration):\n");
			print_arr(map(arr3, mult2));

			printf("\nNew array of items of concatinated array devided by 2 (where demonstration):\n");
			print_arr(where(arr3, is_div2));
			break;
		case 2:
			printf("\nAdd exclamation mark to every string in concatinated array (map demonstration):\n");
			print_arr(map(arr3, add_excl));

			printf("\nNew array of items of concatinated array which length is 3 (where demonstration):\n");
			print_arr(where(arr3, is_len3));
			break;
	}
}

