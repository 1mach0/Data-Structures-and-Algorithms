//
// Created by machi on 10/23/2025.
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

typedef struct Queue {
    Node* head;
    int maxCapacity;
}Q;

bool isEmpty(const Q given) {
    return given.head == NULL;
}

bool isFull(const Q given) {
    const Node* temp = given.head;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count >= given.maxCapacity;
}

Node* delete_first(Node* head, int* data) {
    *data = head->data;
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

Node* insert_last(Node* head, const int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    Node* curr = head;
    if (curr == NULL) {
        return newNode;
    }
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
    return head;
}

Q enq(Q given, const int data) {
    if (isFull(given)) {
        printf("Queue is full\n");
    } else {
        given.head = insert_last(given.head, data);
    }
    return given;
}

int deq(Q* given) {
    int data;
    if (isEmpty(*given)) {
        printf("Queue is empty\n");
    } else {
        given->head = delete_first(given->head, &data);
    }
    return data;
}

void peek(Q given) {
    printf("First in line of queue -> %d\n", given.head->data);
}

void printQ(Q given) {
    const Node* curr = given.head;
    while (curr->next != NULL) {
        printf("[%d] -> ", curr->data);
        curr = curr->next;
    }
    printf("[%d]\n", curr->data);
}

int main() {
    Q pp = {NULL, 10};
    pp = enq(pp, 1);
    pp = enq(pp, 2);
    pp = enq(pp, 3);
    printQ(pp);

    printf("First in queue -> %d\n", deq(&pp));
    printQ(pp);

    peek(pp);

    pp = enq(pp, 5);
    pp = enq(pp, 6);
    printQ(pp);

    deq(&pp);
    printQ(pp);


    return 0;
}