//
// Created by machi on 10/23/2025.
//
#include <stdio.h>
#include <stdbool.h>

bool found(const int* array, const int start, const int stop, const int data) {
    if (start == stop) {
        return true;
    }
    if (stop < start) {
        return false;
    }
    const int mid = start + (stop - start)/2;
    if (array[mid] < data) {
        return found(array, mid+1, stop, data);
    } else if (array[mid] > data) {
        return found(array, start, mid-1, data);
    } else {
        return true;
    }
}

// if the array is sorted but rotated by some K
bool rotated_found(const int* array, const int start, const int stop, const int data) {
    if (start == stop) {
        return true;
    }
    if (stop < start) {
        return false;
    }
    const int mid = start + (stop - start)/2;
    if (array[mid] == data) {
        return true;
    }
    if (array[mid] > data && array[start] > data) {
        return rotated_found(array, mid+1, stop, data);
    } else if (array[mid] < data && array[start] < data) {
        return rotated_found(array, start, mid-1, data);
    }
}

void print(const bool val) {
    if (val) {
        printf("Value found!\n");
    } else {
        printf("Value not found.\n");
    }
}

int main() {
    const int array[10] = {1,2,3,5,6,7,8,9,10};
    const int rarray[10] = {6,7,8,9,10,1,2,3,4,5};

    print(found(array,0, 9, 3));
    print(rotated_found(rarray, 0, 9, 3));

    return 0;
}