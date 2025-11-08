#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;
const ll INF = (ll)1e15;

int **alloc_int_matrix(int n) {
    int **m = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) m[i] = malloc(n * sizeof(int));
    return m;
}

ll **alloc_ll_matrix(int n) {
    ll **m = malloc(n * sizeof(ll*));
    for (int i = 0; i < n; ++i) m[i] = malloc(n * sizeof(ll));
    return m;
}

void free_int_matrix(int **m, int n) {
    for (int i = 0; i < n; ++i) free(m[i]);
    free(m);
}

void free_ll_matrix(ll **m, int n) {
    for (int i = 0; i < n; ++i) free(m[i]);
    free(m);
}

void printPath(int **next, int u, int v) {
    if (next[u][v] == -1) {
        printf("No path");
        return;
    }
    int cur = u;
    printf("%d", cur);
    while (cur != v) {
        cur = next[cur][v];
        printf(" -> %d", cur);
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2) return 0;

    ll **dist = alloc_ll_matrix(V);
    int **next = alloc_int_matrix(V);

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
            next[i][j] = -1;
        }
    }

    printf("Enter edges as: src dest weight (0-based indices, directed)\n");
    for (int i = 0; i < E; ++i) {
        int u, v;
        ll w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) { --i; continue; }
        if (u < 0 || u >= V || v < 0 || v >= V) continue;
        dist[u][v] = w;
        next[u][v] = v;
    }

    // Floyd-Warshall
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < V; ++j) {
                if (dist[k][j] == INF) continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // detect negative cycle
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            printf("Graph contains a negative-weight cycle reachable from vertex %d\n", i);
            free_ll_matrix(dist, V);
            free_int_matrix(next, V);
            return 0;
        }
    }

    // Print distance matrix
    printf("\nAll-pairs shortest path distances:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) printf("INF ");
            else printf("%lld ", dist[i][j]);
        }
        printf("\n");
    }

    // Print paths
    printf("\nShortest paths between every pair:\n");
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i == j) continue;
            printf("%d -> %d : ", i, j);
            if (next[i][j] == -1) printf("No path\n");
            else {
                printPath(next, i, j);
                printf(" (cost = ");
                if (dist[i][j] == INF) printf("INF)\n");
                else printf("%lld)\n", dist[i][j]);
            }
        }
    }

    free_ll_matrix(dist, V);
    free_int_matrix(next, V);
    return 0;
}