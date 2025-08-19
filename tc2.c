#include <stdio.h>
#include <math.h>

int main() {
    int n, x;
    long long sum;

    printf("Enter value of X: ");
    scanf("%d", &x);
    printf("Enter value of n: ");
    scanf("%d", &n);

    if(x == 1)
        sum = n + 1;
    else
        sum = (long long)(pow(x, n + 1) - 1) / (x - 1);

    printf("Sum of series (O(1)): %lld\n", sum);
    return 0;
}