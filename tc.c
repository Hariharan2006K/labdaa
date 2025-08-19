#include <stdio.h>
#include <math.h>

int main() {
    int n, x;
    long long sum = 0, term = 1;

    printf("Enter value of X: ");
    scanf("%d", &x);
    printf("Enter value of n: ");
    scanf("%d", &n);

    for(int i = 0; i <= n; i++) {
        if(i == 0)
            term = 1;
        else
            term = term * x;
        sum += term;
    }

    printf("Sum of series (O(n)): %lld\n", sum);
    return 0;
}