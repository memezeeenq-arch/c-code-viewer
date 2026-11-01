#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 50
#define NAME_LEN   30

typedef struct Edge {
    int dest;                   /* index of the destination city */
    int cost;                   /* cost of the flight (time / fuel) */
    struct Edge *next;
} Edge;

typedef struct {
    int n;                       /* number of cities */
    char name[MAX_CITIES][NAME_LEN];
    Edge *adj[MAX_CITIES];       /* adjacency list */
} Graph;

int findCity(Graph *g, const char *city) {
    int i;
    for (i = 0; i < g->n; i++)
        if (strcmp(g->name[i], city) == 0)
            return i;
    return -1;
}

void addEdge(Graph *g, int u, int v, int cost) {
    Edge *e = (Edge *)malloc(sizeof(Edge));
    Edge *t;
    if (e == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    e->dest = v;
    e->cost = cost;
    e->next = NULL;
    if (g->adj[u] == NULL)
        g->adj[u] = e;
    else {
        t = g->adj[u];
        while (t->next != NULL)
            t = t->next;
        t->next = e;
    }
}

void addFlight(Graph *g, const char *a, const char *b, int cost) {
    int u = findCity(g, a);
    int v = findCity(g, b);
    if (u == -1 || v == -1) {
        printf("  Invalid city name. Flight not added.\n");
        return;
    }
    if (u == v) {
        printf("  A flight must connect two different cities.\n");
        return;
    }
    addEdge(g, u, v, cost);      /* flights are two-way */
    addEdge(g, v, u, cost);
}

void display(Graph *g) {
    int i;
    Edge *e;
    printf("\n----- Graph (Adjacency List) -----\n");

    for (i = 0; i < g->n; i++) {
        printf("%s -> ", g->name[i]);
        if (g->adj[i] == NULL)
            printf("(no direct flights)");
        for (e = g->adj[i]; e != NULL; e = e->next) {
            printf("[%s, cost=%d]", g->name[e->dest], e->cost);
            if (e->next != NULL)
                printf(" -> ");
        }
        printf("\n");
    }
}

void dfs(Graph *g, int u, int visited[]) {
    Edge *e;
    visited[u] = 1;
    for (e = g->adj[u]; e != NULL; e = e->next)
        if (!visited[e->dest])
            dfs(g, e->dest, visited);
}

int isConnected(Graph *g) {
    int visited[MAX_CITIES] = {0};
    int i, all = 1;
    dfs(g, 0, visited);          /* traverse from the first city */
    printf("\nCities reachable from %s: ", g->name[0]);
    for (i = 0; i < g->n; i++) {
        if (visited[i])
            printf("%s ", g->name[i]);
        else
            all = 0;
    }
    printf("\n");
    if (!all) {
        printf("Unreachable cities: ");
        for (i = 0; i < g->n; i++)
            if (!visited[i])
                printf("%s ", g->name[i]);
        printf("\n");
    }
    return all;
}

void freeGraph(Graph *g) {
    int i;
    Edge *e, *tmp;
    for (i = 0; i < g->n; i++) {
        e = g->adj[i];
        while (e != NULL) {
            tmp = e;
            e = e->next;
            free(tmp);
        }
        g->adj[i] = NULL;
    }
}

int main() {
    Graph g;
    int i, m, cost;
    char a[NAME_LEN], b[NAME_LEN];

    printf("Enter the number of cities: ");
    if (scanf("%d", &g.n) != 1 || g.n < 1 || g.n > MAX_CITIES) {
        printf("Invalid number of cities (1 to %d allowed).\n", MAX_CITIES);
        return 1;
    }
    for (i = 0; i < g.n; i++)
        g.adj[i] = NULL;
    printf("Enter the names of %d cities:\n", g.n);

    for (i = 0; i < g.n; i++) {
        printf("  City %d: ", i + 1);
        scanf("%29s", g.name[i]);
    }
    printf("\nEnter the number of direct flights: ");
    scanf("%d", &m);
    printf("Enter each flight as: <City1> <City2> <Cost>\n");
    for (i = 0; i < m; i++) {
        printf("  Flight %d: ", i + 1);
        scanf("%29s %29s %d", a, b, &cost);
        addFlight(&g, a, b, cost);
    }
    display(&g);
    if (isConnected(&g))
        printf("\nResult: The graph is CONNECTED (every city is reachable from every other city).\n");
    else
        printf("\nResult: The graph is NOT CONNECTED (some cities cannot be reached).\n");
    freeGraph(&g);
    return 0;
}