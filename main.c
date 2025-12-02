#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


double* full_elements(double* ptr_array, int size);
int delete_k(double* ptr_arr, int size, int k);
double* insert_random_position(double* ptr_arr, int* size, double value);
int put_elements(double* ptr_array, int size);

int main() {
    setlocale(LC_CTYPE, "");
    double* ptr_array = NULL;
    int size;
    int k;
    srand(time(NULL));

    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Ошибка: размер должен быть положительным\n");
        return -1;
    }

    ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        printf("Ошибка выделения памяти\n");
        return -1;
    }

    ptr_array = full_elements(ptr_array, size);

    printf("Исходный массив:\n");
    put_elements(ptr_array, size);

    // 2.1 
    printf("\n--- 2.1 Удаление элемента с заданным номером ---\n");
    printf("Введите номер элемента для удаления (от 0 до %d): ", size - 1);
    scanf("%d", &k);

    if (k < 0 || k >= size) {
        printf("Ошибка: некорректный номер элемента\n");
    }
    else {
        int new_size = delete_k(ptr_array, size, k);
        size = new_size;

        printf("Массив после удаления элемента с номером %d:\n", k);
        put_elements(ptr_array, size);
    }

    // 2.2 
    printf("\n--- 2.2 Вставка -999 в случайную позицию ---\n");
    double insert_value = -999.0;
    ptr_array = insert_random_position(ptr_array, &size, insert_value);

    if (ptr_array != NULL) {
        printf("Массив после вставки -999 в случайную позицию:\n");
        put_elements(ptr_array, size);
    }

    free(ptr_array);

    return 0;
}

double* full_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        ptr_array[i] = (rand() % 2001) / 1000.0 - 1.0;
    }
    return ptr_array;
}

int delete_k(double* ptr_arr, int size, int k) {
    for (int i = k; i < (size - 1); i++) {
        ptr_arr[i] = ptr_arr[i + 1];
    }
    // Сдвигаее элементы на одну позицию влево, начиная с k
    return size - 1;
}

double* insert_random_position(double* ptr_arr, int* size, double value) {
    int old_size = *size;
    int new_size = old_size + 1;

    double* ptr_arr_new = (double*)realloc(ptr_arr, new_size * sizeof(double));
    if (ptr_arr_new == NULL) {
        printf("Ошибка перераспределения памяти\n");
        return ptr_arr;
    }

    ptr_arr = ptr_arr_new;

    int random_pos = rand() % (old_size + 1);

    printf("Вставляем значение %.2f в позицию %d\n", value, random_pos);

    for (int i = new_size - 1; i > random_pos; i--) {
        ptr_arr[i] = ptr_arr[i - 1];
    }

    ptr_arr[random_pos] = value;

    *size = new_size;

    return ptr_arr;
}

int put_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        printf("Элемент [%d] = %10.6f\n", i, ptr_array[i]);
    }
    return 0;
}