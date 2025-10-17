//
// Created by machi on 10/17/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number1;
int* ptrnumber1;

float number2;
float* ptrnumber2;

double number3;
double* ptrnumber3;

char character1;
char* ptrcharacter1;

char* array1;
char* array2;
char* array3;
char* array4;

int main() {
    number1 = 0;
    ptrnumber1 = &number1;
    printf("%p\n", ptrnumber1);
    printf("%d\n", *ptrnumber1);
    printf("%p\n", &number1);

    number2 = 1.23456789;
    ptrnumber2 = &number2;
    printf("%p\n", ptrnumber2);
    printf("%f\n", *ptrnumber2);
    printf("%p\n", &number2);

    number3 = 1.23456789;
    ptrnumber3 = &number3;
    printf("%p\n", ptrnumber3);
    printf("%f\n", *ptrnumber3);
    printf("%p\n", &number3);

    character1 = 'A';
    ptrcharacter1 = &character1;
    printf("%p\n", ptrcharacter1);
    printf("%c\n", *ptrcharacter1);
    printf("%p\n", &character1);

    array1 = malloc(5*sizeof(char));
    if (array1 == NULL) {
        fprintf(stderr, "Initial malloc failed\n");
        exit(1);
    }

    array1[0] = character1;
    printf("%p\n", array1);

    char* temp = realloc(array1, 10*sizeof(char));
    if (temp == NULL) { // realloc failed
        free(array1);
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    array1 = temp; // do it after success

    printf("%p\n", array1);
    array1[0] = character1;
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

    return 0;
}
