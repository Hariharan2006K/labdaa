#include <stdio.h>
#include <stdlib.h>

/* 0/1 Knapsack - dynamic programming implementation
   Input format:
   n capacity
   values (n integers)
   weights (n integers)
*/
int main() {
    int n, W;
    if (scanf("%d %d", &n, &W) != 2) return 0;

    int *val = malloc(n * sizeof(int));
    int *wt  = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) scanf("%d", &val[i]);
    for (int i = 0; i < n; ++i) scanf("%d", &wt[i]);

    // DP table (n+1) x (W+1)
    int **dp = malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; ++i) {
        dp[i] = calloc(W + 1, sizeof(int));
    }

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (wt[i-1] <= w) {
                int incl = val[i-1] + dp[i-1][w - wt[i-1]];
                int excl = dp[i-1][w];
                dp[i][w] = (incl > excl) ? incl : excl;
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    int maxValue = dp[n][W];
    printf("Maximum value = %d\n", maxValue);

    // Backtrack to find which items were chosen
    int w = W;
    printf("Selected items (index value weight):\n");
    for (int i = n; i > 0 && w >= 0; --i) {
        if (dp[i][w] != dp[i-1][w]) {
            printf("%d %d %d\n", i-1, val[i-1], wt[i-1]);
            w -= wt[i-1];
        }
    }

    for (int i = 0; i <= n; ++i) free(dp[i]);
    free(dp);
    free(val);
    free(wt);
    return 0;
}