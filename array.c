//
// Created by machi on 10/17/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// californya gurls we're unforgettable
char* array1;
char* array2;
char* array3;

void ways_to_make_arrays() {
    array1 = malloc(5*sizeof(char)); // malloc shit into memory heap
    if (array1 == NULL) {
        fprintf(stderr, "Initial malloc failed\n");
        exit(1);
    }

    array1[0] = 'A';
    printf("%p\n", array1);

    char* temp = realloc(array1, 10*sizeof(char));
    if (temp == NULL) { // realloc failed
        free(array1);
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    array1 = temp; // do it after success

    printf("%p\n", array1);
    array1[0] = 'A';
    array1[1] = 'B';
    array1[2] = 'C';
    array1[3] = 'D';
    array1[4] = '\0';
    printf("%s\n", array1);
    free(array1);

    array2 = malloc(30*sizeof(char)); // heap allocated
    strcpy(array2, "Hello World");
    printf("%s\n", array2);
    free(array2);

    array3  = "Helloo World"; // static (read-only) allocated
    printf("%s\n", array3);
    // "Helloo World" is a statically allocated constant — it exists for the entire lifetime of your program,
    // and it’s not owned by you (you didn’t malloc it).
    //
    // When you write:
    // char *array3 = "Helloo World";
    // you’re not creating an array at runtime.
    // You’re making array3 (a pointer) refer to a string literal, and that
    // literal’s characters live in the read-only data section (often called .rodata) of your program’s memory layout.
    //
    // That’s part of your program’s static storage area,
    // which the OS sets up once when the executable is loaded.

    char string[] = "Hello World"; // stack allocated
    printf("%s\n", string);
}

void insert_into_arrays() {
    int arr[] = {1,2,3,4,5};
    printf("Array before inserting");
    for (int i = 0; i < 5; i++) {
        printf("[%d]", arr[i]);
    }
    printf("\n");

    int number;
    printf("Enter a number: ");
    scanf("%d",&number);
    int position;
    printf("Enter position of number: ");
    scanf("%d",&position);

    int temp = number;
    for (int i = position; i < 5; i++) {
        arr[i++] = temp;
        temp = arr[i];
    }
    arr[4] = temp;

    printf("Array after inserting");
    for (int i = 0; i < 5; i++) {
        printf("[%d]",arr[i]);
    }
}

int main() {
    insert_into_arrays();
}

