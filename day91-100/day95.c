#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    float value;
    struct Node* next;
} Node;

void insertSorted(Node** head, float val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = NULL;

    if (*head == NULL || (*head)->value >= val) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* curr = *head;
    while (curr->next != NULL && curr->next->value < val)
        curr = curr->next;

    newNode->next = curr->next;
    curr->next = newNode;
}

void bucketSort(float arr[], int n) {
    Node** buckets = (Node**)malloc(n * sizeof(Node*));

    for (int i = 0; i < n; i++)
        buckets[i] = NULL;

    for (int i = 0; i < n; i++) {
        int idx = (int)(arr[i] * n);
        insertSorted(&buckets[idx], arr[i]);
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        Node* curr = buckets[i];
        while (curr != NULL) {
            arr[k++] = curr->value;
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(buckets);
}

int main() {
    float arr[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    int n = sizeof(arr) / sizeof(arr[0]);

    bucketSort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%.2f ", arr[i]);

    return 0;
}