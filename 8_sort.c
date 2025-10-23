//
// Created by machi on 10/23/2025.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// merge two sorted halves arr[0, 1, ... m] and [m+1, m+2, ..., r]
void merge(int* a, const int start_ind, const int mid_ind, const int stop_ind) {
    int* new = malloc((stop_ind - start_ind + 1)*sizeof(int));

    int first_ind = start_ind, second_ind = mid_ind + 1, i = 0;
    while (first_ind <= mid_ind && second_ind <= stop_ind) {
        if (a[first_ind] <= a[second_ind]) {
            new[i++] = a[first_ind++];
        } else {
            new[i++] = a[second_ind++];
        }
    }
    while (second_ind <= stop_ind) {
        new[i++] = a[second_ind++];
    }
    while (first_ind <= mid_ind) {
        new[i++] = a[first_ind++];
    }

    for (int j = start_ind; j < stop_ind + 1; j++) {
        a[j] = new[j - start_ind];
    }

    free(new);
}

void mergesort(int* a, const int start, const int stop) {
    if (start >= stop) {
        return;
    }
    // start = 0, stop = len-1
    const int mid = start + (stop - start)/2;
    mergesort(a, start, mid);
    mergesort(a, mid+1, stop);
    merge(a, start, mid, stop);
}


void swap(int* a, int* b) {
    const int temp = *a;
    *a = *b;
    *b = temp;
}


void bubblesort(int* array, const int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j+1], &array[j]);
            }
        }
    }
}

void print(const int* a, const int size) {
    for (int i = 0; i < size; i++) {
        printf("[%d] ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[5] = {3,2,5,4,1};
    int b[5] = {7,9,6,8,10};
    mergesort(a, 0, 4);
    print(a, 5);

    bubblesort(b, 5);
    print(b, 5);

    return 0;
}