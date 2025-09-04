#include <stdio.h>

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int max_elem = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_elem)
            max_elem = arr[i];
    }

    printf("Maximum element is %d\n", max_elem);
    return 0;
}