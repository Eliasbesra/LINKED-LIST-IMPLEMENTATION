#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertAtBeginning(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

void insertAtEnd(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void insertAtPosition(LinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) return;
    
    if (position == 0) {
        insertAtBeginning(list, data);
        return;
    }
    
    if (position == list->size) {
        insertAtEnd(list, data);
        return;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    list->size++;
}

int deleteFromBeginning(LinkedList* list) {
    if (list->head == NULL) return -1;
    
    Node* temp = list->head;
    int data = temp->data;
    list->head = list->head->next;
    free(temp);
    list->size--;
    return data;
}

int deleteFromEnd(LinkedList* list) {
    if (list->head == NULL) return -1;
    
    if (list->head->next == NULL) {
        return deleteFromBeginning(list);
    }
    
    Node* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    Node* temp = current->next;
    int data = temp->data;
    current->next = NULL;
    free(temp);
    list->size--;
    return data;
}

int deleteFromPosition(LinkedList* list, int position) {
    if (position < 0 || position >= list->size) return -1;
    
    if (position == 0) {
        return deleteFromBeginning(list);
    }
    
    if (position == list->size - 1) {
        return deleteFromEnd(list);
    }
    
    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    Node* temp = current->next;
    int data = temp->data;
    current->next = temp->next;
    free(temp);
    list->size--;
    return data;
}

void traverse(LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    Node* current = list->head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    printf("Size: %d\n", list->size);
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* list = createLinkedList();
    
    insertAtEnd(list, 10);
    insertAtBeginning(list, 5);
    insertAtEnd(list, 20);
    insertAtPosition(list, 15, 2);
    traverse(list);
    
    printf("Deleted from beginning: %d\n", deleteFromBeginning(list));
    printf("Deleted from end: %d\n", deleteFromEnd(list));
    traverse(list);
    
    insertAtPosition(list, 25, 1);
    insertAtPosition(list, 30, 0);
    traverse(list);
    
    printf("Deleted from position 2: %d\n", deleteFromPosition(list, 2));
    traverse(list);
    
    freeLinkedList(list);
    return 0;
}