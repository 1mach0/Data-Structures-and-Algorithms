//
// Created by machi on 10/19/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;

typedef struct Stack {
    Node* headPtr;
    int maxCapacity;
}Stack;

Node* insert_first(Node* head, const int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

Node* deleteFirst(Node* head, int* data) {
    Node* temp = head;
    *data = temp->data;
    head = head->next;
    free(temp);
    return head;
}

bool isEmpty(const Stack given) {
    return given.headPtr == NULL;
}

bool isFull(const Stack given) {
    int count = 0;
    Node* temp = given.headPtr;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count >= given.maxCapacity;
}

Stack push(Stack given, int data) {
    if (isFull(given)) {
        printf("Stack is full, cannot push");
        return given;
    }
    given.headPtr = insert_first(given.headPtr, data);
    return given;
}

int pop(Stack* given) {
    int data;
    if (isEmpty(*given)) {
        printf("Stack is empty, cannot pop");
    } else {
        given->headPtr = deleteFirst(given->headPtr, &data);
    }
    return data;
}

void peek(const Stack given) {
    if (isEmpty(given)) {
        printf("Stack is empty");
        return;
    }
    printf("Top of the stack --> {%d}\n", given.headPtr->data);
}

void printStack(const Stack given) {
    const Node* temp = given.headPtr;
    while (temp->next != NULL) {
        printf("[%d] -> ", temp->data);
        temp = temp->next;
    }
    printf("[%d]\n", temp->data);
}

int main() {
    Stack stack1 = {NULL, 10};
    stack1 = push(stack1, 1);
    stack1 = push(stack1, 2);
    stack1 = push(stack1, 3);
    printStack(stack1);

    printf("Popping the stack -> %d\n", pop(&stack1));

    peek(stack1);
    printStack(stack1);

    return 0;
}