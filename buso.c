#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(int arr[], int n) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    int bucketCount = (max - min) / BUCKET_SIZE + 1;
    int **buckets = (int **)malloc(bucketCount * sizeof(int *));
    int *bucketSizes = (int *)calloc(bucketCount, sizeof(int));

    for (int i = 0; i < bucketCount; i++)
        buckets[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int idx = (arr[i] - min) / BUCKET_SIZE;
        buckets[idx][bucketSizes[idx]++] = arr[i];
    }

    int k = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            insertionSort(buckets[i], bucketSizes[i]);
            for (int j = 0; j < bucketSizes[i]; j++)
                arr[k++] = buckets[i][j];
        }
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    bucketSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}

