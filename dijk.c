#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

/* Adjacency list node */
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

/* Graph: array of adjacency lists */
typedef struct {
    int V;
    AdjListNode** array;
} Graph;

AdjListNode* newAdjNode(int dest, int weight) {
    AdjListNode* node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjListNode**)malloc(V * sizeof(AdjListNode*));
    for (int i = 0; i < V; ++i) graph->array[i] = NULL;
    return graph;
}

/* add directed edge u->v with weight */
void addEdge(Graph* graph, int u, int v, int w) {
    AdjListNode* node = newAdjNode(v, w);
    node->next = graph->array[u];
    graph->array[u] = node;
}

/* Min-heap node */
typedef struct {
    int v;
    int dist;
} MinHeapNode;

/* Min-heap structure */
typedef struct {
    int size;
    int capacity;
    int *pos; /* position of vertex in heap */
    MinHeapNode **array;
} MinHeap;

MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->v = v;
    node->dist = dist;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return heap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

/* Heapify at idx */
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left < heap->size && heap->array[left]->dist < heap->array[smallest]->dist)
        smallest = left;
    if (right < heap->size && heap->array[right]->dist < heap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        /* swap positions */
        MinHeapNode *smallestNode = heap->array[smallest];
        MinHeapNode *idxNode = heap->array[idx];

        heap->pos[smallestNode->v] = idx;
        heap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

MinHeapNode* extractMin(MinHeap* heap) {
    if (isEmpty(heap)) return NULL;
    MinHeapNode* root = heap->array[0];
    MinHeapNode* lastNode = heap->array[heap->size - 1];
    heap->array[0] = lastNode;

    heap->pos[root->v] = heap->size - 1;
    heap->pos[lastNode->v] = 0;

    --heap->size;
    minHeapify(heap, 0);
    return root;
}

/* decrease dist value of vertex v */
void decreaseKey(MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->array[i]->dist = dist;

    while (i && heap->array[i]->dist < heap->array[(i - 1) / 2]->dist) {
        heap->pos[ heap->array[i]->v ] = (i-1)/2;
        heap->pos[ heap->array[(i-1)/2]->v ] = i;
        swapMinHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *heap, int v) {
    if (heap->pos[v] < heap->size) return 1;
    return 0;
}

/* Print shortest path using parent array */
void printPath(int parent[], int j) {
    if (parent[j] == -1) { printf("%d", j); return; }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}

/* Dijkstra's algorithm */
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int *dist = (int*)malloc(V * sizeof(int));
    int *parent = (int*)malloc(V * sizeof(int));

    MinHeap* heap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INF;
        parent[v] = -1;
        heap->array[v] = newMinHeapNode(v, dist[v]);
        heap->pos[v] = v;
    }

    heap->array[src]->dist = 0;
    dist[src] = 0;
    decreaseKey(heap, src, 0);
    heap->size = V;

    while (!isEmpty(heap)) {
        MinHeapNode* minNode = extractMin(heap);
        int u = minNode->v;
        free(minNode);

        AdjListNode* pCrawl = graph->array[u];
        while (pCrawl != NULL) {
            int v = pCrawl->dest;
            if (isInMinHeap(heap, v) && dist[u] != INF &&
                pCrawl->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + pCrawl->weight;
                parent[v] = u;
                decreaseKey(heap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    printf("Vertex\tDistance\tPath\n");
    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF)
            printf("%d\tINF\t\t-\n", i);
        else {
            printf("%d\t%d\t\t", i, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }

    /* cleanup */
    for (int i = 0; i < heap->capacity; ++i) free(heap->array[i]);
    free(heap->array);
    free(heap->pos);
    free(heap);
    free(dist);
    free(parent);
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2) return 0;

    Graph* graph = createGraph(V);

    printf("Enter each edge as: src dest weight (directed). Use 0-based vertex indices.\n");
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) { --i; continue; }
        if (u < 0 || u >= V || v < 0 || v >= V) continue;
        addEdge(graph, u, v, w);
    }

    int src;
    printf("Enter source vertex: ");
    if (scanf("%d", &src) != 1) return 0;
    if (src < 0 || src >= V) return 0;

    dijkstra(graph, src);

    /* free graph */
    for (int i = 0; i < V; ++i) {
        AdjListNode* p = graph->array[i];
        while (p) {
            AdjListNode* tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}