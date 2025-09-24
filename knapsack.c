#include<stdio.h>
struct Item {
    int value;
    int weight;
};

void fractionalKnapsack(int n, struct Item items[], int capacity, int mode) {
    float totalValue = 0.0;
    int remaining = capacity;

    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int swap = 0;
            if (mode == 1 && items[j].value > items[i].value) swap = 1; // By value
            if (mode == 2 && items[j].weight < items[i].weight) swap = 1; // By weight
            if (mode == 3 && ((float)items[j].value/items[j].weight) > ((float)items[i].value/items[i].weight)) swap = 1; // By ratio
            if (swap) {
                struct Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }

    printf("Selected items:\n");
    for (int i = 0; i < n && remaining > 0; i++) {
        if (items[i].weight <= remaining) {
            printf("Item %d: value=%d, weight=%d (100%%)\n", i+1, items[i].value, items[i].weight);
            totalValue += items[i].value;
            remaining -= items[i].weight;
        } else {
            float fraction = (float)remaining / items[i].weight;
            printf("Item %d: value=%d, weight=%d (%.2f%%)\n", i+1, items[i].value, items[i].weight, fraction*100);
            totalValue += items[i].value * fraction;
            remaining = 0;
        }
    }
    printf("Total value in knapsack = %.2f\n", totalValue);
}

int main() {
    int n, capacity, mode;
    printf("Enter number of items: ");
    scanf("%d", &n);
    struct Item items[n];
    printf("Enter value and weight of each item:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &items[i].value, &items[i].weight);

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    printf("Choose approach:\n1. By Value\n2. By Weight\n3. By Value/Weight Ratio (Optimal)\nEnter choice: ");
    scanf("%d", &mode);

    fractionalKnapsack(n, items, capacity, mode);

    return 0;
}