//
// Created by machi on 10/19/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Stack {
    int* array;
    int maxCapacity;
    int popPtr;
}Stack;

bool isFull(const Stack given) {
    return given.popPtr == given.maxCapacity;
}

bool isEmpty(const Stack given) {
    return given.popPtr == -1;
}

Stack push(Stack given, const int data) {
    if (isFull(given)) {
        printf("Stack is full, cannot push");
    } else {
        given.array[++given.popPtr] = data;
    }
    return given;
}

int pop(Stack* given) {
    if (isEmpty(*given)) {
        printf("Stack is empty, cannot pop");
    } else {
        given->popPtr -= 1;
        return given->array[given->popPtr+1];
    }
}


void peek(Stack given) {
    printf("Here is the element on the top --> {%d}", given.array[given.popPtr]);
}

void printStack(Stack given) {
    printf("Printing from last to first\n");
    while (given.popPtr != 0) {
        printf("[%d] -> ", given.array[given.popPtr--]);
    }
    printf("[%d]\n", given.array[given.popPtr]);
}

int main() {
    Stack stack1;
    stack1.maxCapacity = 10;
    stack1.array = malloc(stack1.maxCapacity * sizeof(int));
    stack1.popPtr = -1;

    stack1 = push(stack1, 1);
    stack1 = push(stack1, 2);
    stack1 = push(stack1, 3);
    printStack(stack1);

    printf("Popping stack1 --> {%d}\n", pop(&stack1));
    printf("popPtr = %d\n", stack1.popPtr);
    printStack(stack1);

    stack1 = push(stack1, 4);
    stack1 = push(stack1, 5);
    stack1 = push(stack1, 6);
    printStack(stack1);

    peek(stack1);

    return 0;
}