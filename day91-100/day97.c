#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int cmpStart(const void *a, const void *b) {
    return ((Interval *)a)->start - ((Interval *)b)->start;
}

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void heapifyUp(int heap[], int i) {
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] <= heap[i]) break;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

void heapifyDown(int heap[], int size, int i) {
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, smallest = i;

        if (l < size && heap[l] < heap[smallest]) smallest = l;
        if (r < size && heap[r] < heap[smallest]) smallest = r;

        if (smallest == i) break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
}

int minMeetingRooms(Interval arr[], int n) {
    qsort(arr, n, sizeof(Interval), cmpStart);

    int *heap = (int *)malloc(n * sizeof(int));
    int size = 0;

    heap[size++] = arr[0].end;

    for (int i = 1; i < n; i++) {
        if (heap[0] <= arr[i].start) {
            heap[0] = arr[i].end;
            heapifyDown(heap, size, 0);
        } else {
            heap[size++] = arr[i].end;
            heapifyUp(heap, size - 1);
        }
    }

    int result = size;
    free(heap);
    return result;
}

int main() {
    Interval arr[] = {{0, 30}, {5, 10}, {15, 20}};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", minMeetingRooms(arr, n));
    return 0;
}