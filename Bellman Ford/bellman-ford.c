#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
struct Edge
{
    int source, destination, weight;
};
 

struct Graph
{
    int V, E;
    struct Edge* edge;
};
 
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph));
    graph->V = V; 
    graph->E = E;
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
    return graph;
}
 
void Print(int dist[], int n)
{
    int i;
    for (i = 0; i < n; ++i){
	printf("%d:%d ", i, dist[i]);
    }
    printf("\n");
}
 
void BellmanFord(struct Graph* graph, int source)
{
    int V = graph->V;
    int E = graph->E;
    int StoreDistance[V]; 
    int i,j;

    for (i = 0; i < V; i++)
        StoreDistance[i] = INT_MAX;
 
    StoreDistance[source] = 0;

    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = graph->edge[j].source;
            int v = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            if (StoreDistance[u] + weight < StoreDistance[v])
                StoreDistance[v] = StoreDistance[u] + weight;
        }
    }
    for (i = 0; i < E; i++)
    {
        int u = graph->edge[i].source;
        int v = graph->edge[i].destination;
        int weight = graph->edge[i].weight;
        if (StoreDistance[u] + weight < StoreDistance[v])
            printf("Este gráfico contém ciclo de arestas negativo;\n");
    }
    Print(StoreDistance, V);
    return;
}
 
int main()
{
    int V,E; 
    scanf("%d %d",&V, &E);
 
    struct Graph* graph = createGraph(V, E);
 
    int i;
    for(i=0;i<E;i++){
        scanf("%d",&graph->edge[i].source);
        scanf("%d",&graph->edge[i].destination);
        scanf("%d",&graph->edge[i].weight);
    }
 
    BellmanFord(graph, 0);
 
    return 0;
}
