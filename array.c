#include <stdlib.h>
#include <string.h>

#define STR_SIZE 256

struct Array{
    void* buffer;
    int count;
    int element_size;
};

//set element of array
void set(struct Array* arr, int index, void* value) {
    void* p = (char*)arr->buffer + index * arr->element_size;

    memcpy(p, value, arr->element_size);
}

//get element of array
void* get(struct Array* arr, int index) {
    void* value = (char*)arr->buffer + index * arr->element_size;

    return value;
}

//create_arr array of 'count' size filled with 'value' items of 'item_size' size
struct Array* create_arr(int count, int item_size, void* value) {
    struct Array* arr = malloc(sizeof(struct Array));
    arr->count = count;
    arr->element_size = item_size;
    arr->buffer = malloc(count * item_size);
	
    for (int i = 0; i < arr->count; i++) {
        set(arr, i, value);
    }
	
	return arr;
}

//return copied array
struct Array* copy_arr(struct Array* arr) {
	struct Array* arr_copy_arr = create_arr(arr->count, arr->element_size, get(arr, 0));

	for (int i = 0; i < arr->count; i++) {
		set(arr_copy_arr, i, get(arr, i));
	}

	return arr_copy_arr;
}

//returns new array consisting of filtired elements of source array
struct Array* where(struct Array* arr, int (*f)(void*)) {
	struct Array* arr_where = create_arr(arr->count, arr->element_size, get(arr, 0));
	int count_where = 0;
	
	for (int i = 0; i < arr->count; i++) {
		if (f(get(arr, i)) == 1) {
			set(arr_where, count_where, get(arr, i));
			count_where++;
		}	
	}

	arr_where->count = count_where;

	return arr_where;
}

//concatination of two arrays
struct Array* concat(struct Array* arr1, struct Array* arr2) {
	struct Array* arr = malloc(sizeof(struct Array));
	arr->count = arr1->count + arr2->count;
    arr->element_size = arr1->element_size;
    arr->buffer = malloc(arr->count * arr->element_size);

    for (int i = 0; i < arr1->count; i++) {
        set(arr, i, get(arr1, i));
    }
	for (int i = arr1->count; i < arr->count; i++) {
        set(arr, i, get(arr2, i-arr1->count));
    }

	return arr;

}

//function map
struct Array* map(struct Array* arr, void* (*f)(void*)) {
	struct Array* arr_map = copy_arr(arr);

	for (int i = 0; i < arr->count; i++) {
		set(arr_map, i, f(get(arr, i)));
	}
	
	return arr_map;
}

//swap v1 and v2
void swap(void* v1, void* v2, struct Array* arr) {
	void* buffer_p = malloc(arr->element_size);

	memcpy(buffer_p, v1, arr->element_size);

	memcpy(v1, v2, arr->element_size);
	memcpy(v2, buffer_p, arr->element_size);	
}

int partition(struct Array* arr, int left, int right, int (*cmp)(void*, void*)) {
	void* pivot = get(arr, right);
	int save_index = left - 1;

	for (int i = left; i < right; i++) {
		if (cmp(get(arr, i), pivot) == -1) {
			save_index++;
			swap(get(arr, save_index), get(arr, i), arr);
		}
	}

	swap(get(arr, save_index + 1), pivot, arr);

	return (save_index + 1);
}

void quick_sort(struct Array* arr, int left, int right, int (*cmp)(void*, void*)) {
	if (left < right) {
		int partition_index = partition(arr, left, right, cmp);

		quick_sort(arr, left, partition_index - 1, cmp);
		quick_sort(arr, partition_index + 1, right, cmp);
	}
}

