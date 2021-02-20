#define STR_SIZE 256

struct Array{
    void* buffer;
    int count;
    int element_size;
};

void set(struct Array* arr, int index, void* value);

void* get(struct Array* arr, int index);

struct Array* create_arr(int count, int item_size, void* value);

struct Array* copy_arr(struct Array* arr);

struct Array* where(struct Array* arr, int (*f)(void*));

struct Array* concat(struct Array* arr1, struct Array* arr2);

struct Array* map(struct Array* arr, void* (*f)(void*));

void quick_sort(struct Array* arr, int left, int right, int (*cmp)(void*, void*));

