//
// Created by machi on 10/19/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* insert_last(Node* head, const int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    return head;
}

Node* insert_first(Node* head, const int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    if (head == NULL) {
        newNode->next = NULL;
        head = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
    }

    return head;
}

Node* search(Node* head, const int data) {
    Node* current = head;
    if (current == NULL) {
        return NULL;
    }
    while (current->next != NULL) {
        if (current->next->data == data) {
            return current;
        }
        current = current->next;
    }
    return (current->data == data)? current : NULL;
}

Node* delete_data(Node* head, const int data) {
    Node* found = search(head, data);
    if (found == NULL) {
        return head;
    }
    printf("found data = %d\n", found->data);
    if (found->data == data) {
        head = NULL;
    } else if ( found->data != data) {
        Node* temp = found->next;
        found->next = temp->next;
        free(temp);
    }
    return head;
}

Node* delete_first(Node* head) {
    if (head == NULL) {
        return NULL;
    } else {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return head;
}

Node* delete_last(Node* head) {
    if (head == NULL) {
        return NULL;
    } else {
        Node* current = head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = NULL;
        free(temp);
    }
    return head;
}

Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    if (current == NULL) {
        return NULL;
    }
    Node* next = current->next;
    while (next != NULL) {
        current->next = prev;

        prev = current;
        current = next;
        next = next->next;
    }
    current->next = prev;

    return current;
}

void print(Node* head) {
    Node* current = head;
    if (current == NULL) {
        printf("Empty List\n");
        return;
    }
    while (current->next != NULL) {
        printf("[%d] -> ", current->data);
        current = current->next;
    }
    printf("[%d]\n", current->data);
}

int main() {
    Node* HEAD = NULL;
    HEAD = insert_last(HEAD, 1);
    HEAD = insert_last(HEAD, 2);
    HEAD = insert_last(HEAD, 3);
    HEAD = insert_last(HEAD, 4);
    print(HEAD);
    HEAD = insert_first(HEAD, 0);
    HEAD = insert_first(HEAD, -1);
    print(HEAD);

    HEAD = delete_first(HEAD);
    print(HEAD);
    HEAD = delete_last(HEAD);
    print(HEAD);
    HEAD = delete_data(HEAD, 1);
    print(HEAD);

    HEAD = insert_last(HEAD, 5);
    HEAD = insert_last(HEAD, 6);
    HEAD = insert_last(HEAD, 7);
    print(HEAD);

    HEAD = reverse(HEAD);
    print(HEAD);

    return 0;
}

