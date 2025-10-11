#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

int compareEdges(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int findSet(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = findSet(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int xroot = findSet(subsets, x);
    int yroot = findSet(subsets, y);
    if (xroot == yroot) return;
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2) return 0;

    Edge *edges = malloc(E * sizeof(Edge));
    if (!edges) return 0;

    printf("Enter each edge as: src dest weight (vertices numbered 0 to %d)\n", V-1);
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    qsort(edges, E, sizeof(Edge), compareEdges);

    Subset *subsets = malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge *mst = malloc((V - 1) * sizeof(Edge));
    int e = 0; // count of edges included in MST
    int i = 0; // index for sorted edges

    while (e < V - 1 && i < E) {
        Edge next = edges[i++];
        int x = findSet(subsets, next.src);
        int y = findSet(subsets, next.dest);
        if (x != y) {
            mst[e++] = next;
            unionSets(subsets, x, y);
        }
    }

    if (e != V - 1) {
        printf("MST not possible (graph may be disconnected).\n");
    } else {
        int totalWeight = 0;
        printf("Edges in MST:\n");
        for (int j = 0; j < e; j++) {
            printf("%d -- %d == %d\n", mst[j].src, mst[j].dest, mst[j].weight);
            totalWeight += mst[j].weight;
        }
        printf("Total weight of MST = %d\n", totalWeight);
    }

    free(edges);
    free(subsets);
    free(mst);
    return 0;
}