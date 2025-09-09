#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* hashTable[SIZE] = {NULL};

int hash(int key) {
    return key % SIZE;
}

void insert(int key) {
    int idx = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = key;
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
    printf("%d inserted.\n", key);
}

int search(int key) {
    int idx = hash(key);
    Node* temp = hashTable[idx];
    while (temp) {
        if (temp->data == key)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void delete(int key) {
    int idx = hash(key);
    Node* temp = hashTable[idx];
    Node* prev = NULL;
    while (temp) {
        if (temp->data == key) {
            if (prev)
                prev->next = temp->next;
            else
                hashTable[idx] = temp->next;
            free(temp);
            printf("%d deleted.\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("%d not found.\n", key);
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* temp = hashTable[i];
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, key;
    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(key))
                    printf("%d found.\n", key);
                else
                    printf("%d not found.\n", key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(key);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
   
    }
}