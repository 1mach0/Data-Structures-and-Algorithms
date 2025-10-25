//
// Created by machi on 10/23/2025.
//
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 // Define the size of the hash table

typedef struct DataItem {
    int key;
}DataItem;


int hash(const int key) {
    return key % SIZE;
}

DataItem* search(DataItem** hashArray, const int key) {
    int hashIndex = hash(key);

    while (hashArray[hashIndex] != NULL) {
        if (hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];

        hashIndex++;
        hashIndex %= SIZE;
    }
    return NULL;
}

void insert(DataItem** hashArray, const int key) {
    int index = hash(key);
    while (hashArray[index] != NULL && hashArray[index]->key != -1) {
        index = (index + 1) % SIZE;
    }

    hashArray[index]->key = key;
}

void delete(DataItem** hashArray, const int key) {
    const int index = hash(key);
    if (hashArray[index]->key == key) {
        hashArray[index] = NULL;
    } else {
        int search = index;
        while (hashArray[index]->key != key) {
            search = (search + 1) % SIZE;
        }

        // fix chain
        while (hashArray[search] != NULL && hashArray[search]->key != -1) {
            if (abs(search - hash(key)) > abs(index - hash(key))) {
                // swap curr key and deleted key
                const int temp = hashArray[search]->key;
                hashArray[search]->key = hashArray[index]->key;
                hashArray[index]->key = temp;
            }
            search = (search + 1) % SIZE;
        }

        hashArray[search] = NULL;
    }
}

int main() {
    DataItem* hashArray[SIZE]; // Define the hash table as an array of DataItem pointers


    const DataItem *result = search(hashArray, 64);
    printf("The element to be searched: %d\n", 64);
    if (result->key == 64) {
        printf("element found\n");
    } else {
        printf("element not found\n");
    }

    return 0;
}