#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int cmp(const void *a, const void *b) {
    return ((Interval *)a)->start - ((Interval *)b)->start;
}

void mergeIntervals(Interval arr[], int n) {
    if (n == 0) return;

    qsort(arr, n, sizeof(Interval), cmp);

    Interval *res = (Interval *)malloc(n * sizeof(Interval));
    int idx = 0;

    res[idx] = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i].start <= res[idx].end) {
            if (arr[i].end > res[idx].end)
                res[idx].end = arr[i].end;
        } else {
            res[++idx] = arr[i];
        }
    }

    for (int i = 0; i <= idx; i++)
        printf("[%d, %d] ", res[i].start, res[i].end);

    free(res);
}

int main() {
    Interval arr[] = {{1,3}, {2,6}, {8,10}, {15,18}};
    int n = sizeof(arr) / sizeof(arr[0]);

    mergeIntervals(arr, n);
    return 0;
}