#include <stdio.h>

void findMinMax(int arr[], int low, int high, int *min, int *max) {
    if (low == high) {
        // Only one element
        *min = *max = arr[low];
    } else if (high == low + 1) {
        // Two elements
        if (arr[low] < arr[high]) {
            *min = arr[low];
            *max = arr[high];
        } else {
            *min = arr[high];
            *max = arr[low];
        }
    } else {
        int mid = (low + high) / 2;
        int min1, max1, min2, max2;
        findMinMax(arr, low, mid, &min1, &max1);
        findMinMax(arr, mid + 1, high, &min2, &max2);

        *min = (min1 < min2) ? min1 : min2;
        *max = (max1 > max2) ? max1 : max2;
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int min, max;
    findMinMax(arr, 0, n - 1, &min, &max);

    printf("Minimum element is %d\n", min);
    printf("Maximum element is %d\n", max);

    return 0;
}