#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define True 0
#define False 1

/// @brief Allocates a graph in memory
/// @return A pointer to an allocated graph
Graph *createGraph()
{
    Graph *newGraph = malloc(sizeof(Graph));
    if (newGraph == NULL)
        return NULL;

    newGraph->adjacency = NULL;
    newGraph->vertexCount = 0;

    return newGraph;
}


/// @brief Recursive binary search helper to find a vertex
static int searchV(Graph *graph, int vertex, int start, int end)
{
    if (start > end)
        return -1;

    int pos = (start + end) / 2;

    int current = graph->adjacency[pos].id_vertex;

    if (current == vertex)
        return pos;

    if (current > vertex)
        return searchV(graph, vertex, start, pos - 1);

    return searchV(graph, vertex, pos + 1, end);
}


/// @brief Clean binary search function for a vertex
int searchVertex(Graph *graph, int vertex)
{
    if (graph == NULL)
        return -2;

    if (graph->vertexCount == 0)
        return -1;

    return searchV(graph, vertex, 0, graph->vertexCount - 1);
}


/// @brief Adds a vertex into the graph adjacency vector
void addVertex(Graph *graph, int vertex)
{
    if (graph == NULL)
        return;

    // Increase adjacency list size
    graph->adjacency = realloc(graph->adjacency, sizeof(List) * (graph->vertexCount + 1));

    // Case for the first element
    if (graph->vertexCount == 0)
    {
        graph->adjacency[0].id_vertex = vertex;
        graph->adjacency[0].first = NULL;
        graph->vertexCount = 1;
        return;
    }

    // Ordered insertion (insertion sort)
    int i = graph->vertexCount - 1;

    // Move larger elements forward
    while (i >= 0 && graph->adjacency[i].id_vertex > vertex)
    {
        graph->adjacency[i + 1] = graph->adjacency[i];
        i--;
    }

    // Insert new vertex
    graph->adjacency[i + 1].id_vertex = vertex;
    graph->adjacency[i + 1].first = NULL;

    graph->vertexCount++;
}


/// @brief Prints all vertices of the graph
void printVertices(Graph *graph)
{
    if (graph == NULL)
        return;

    for (int i = 0; i < graph->vertexCount; i++)
        printf("[ %d ]\n", graph->adjacency[i].id_vertex);
}


/// @brief Inserts a node into a linked list in ascending order
void insertIntoList(List *list, Node *node)
{
    if (list == NULL)
        return;

    node->next = NULL;  // IMPORTANT!

    // Insert at the beginning
    if (list->first == NULL || list->first->info.vertex > node->info.vertex)
    {
        node->next = list->first;
        list->first = node;
        return;
    }

    Node *aux = list->first;

    // Traverse until correct position is found
    while (aux->next != NULL && aux->next->info.vertex < node->info.vertex)
        aux = aux->next;

    node->next = aux->next;
    aux->next = node;
}


/// @brief Adds an edge to a given vertex's adjacency list
int addEdge(Graph *graph, int initialVertex, int finalVertex, int weight)
{
    if (graph == NULL)
        return False;

    int pos = searchVertex(graph, initialVertex);
    if (pos < 0)
        return False;

    Node *node = malloc(sizeof(Node));
    node->info.vertex = finalVertex;
    node->info.weight = weight;
    node->next = NULL;

    insertIntoList(&graph->adjacency[pos], node);

    return True;
}


/// @brief Prints all vertices and edges of the graph
void printGraph(Graph *graph)
{
    if (graph == NULL)
        return;

    for (int i = 0; i < graph->vertexCount; i++)
    {
        printf("\n%d: ", graph->adjacency[i].id_vertex);
        for (Node *aux = graph->adjacency[i].first; aux != NULL; aux = aux->next)
            printf("[ %d ] ", aux->info.vertex);
    }
    printf("\n");
}


/// @brief Checks if an edge already exists
/// @return 1 if exists, 0 if not, -1 if vertex not found
int edgeExists(Graph *graph, int initialVertex, int finalVertex)
{
    int pos = searchVertex(graph, initialVertex);
    if (pos == -1)
        return -1;

    for (Node *aux = graph->adjacency[pos].first; aux != NULL; aux = aux->next)
    {
        if (aux->info.vertex == finalVertex)
            return 1;
    }

    return 0;
}


/// @brief Frees all nodes in a list
void freeList(List *list)
{
    Node *node = NULL;

    while (list->first != NULL)
    {
        node = list->first;
        list->first = list->first->next;
        free(node);
    }
}


/// @brief Removes a vertex and shifts adjacency vector
int removeVertex(Graph *graph, int vertex)
{
    if (graph == NULL)
        return -2;

    int pos = searchVertex(graph, vertex);
    if (pos == -1)
        return 1;

    freeList(&graph->adjacency[pos]);

    // Shift arrays backwards
    for (int i = pos; i < graph->vertexCount - 1; i++)
        graph->adjacency[i] = graph->adjacency[i + 1];

    graph->vertexCount--;

    graph->adjacency = realloc(graph->adjacency, sizeof(List) * graph->vertexCount);

    return 0;
}


/// @brief Prints all adjacent vertices from a given vertex
int printAdjacentVertices(Graph *graph, int vertex)
{
    if (graph == NULL || graph->vertexCount == 0)
    {
        printf("Empty Graph\n");
        return -1;
    }

    int pos = searchVertex(graph, vertex);
    if (pos == -1)
        return -1;

    if (graph->adjacency[pos].first == NULL)
        return 0;

    Node *aux = graph->adjacency[pos].first;
    int count = 0;

    while (aux != NULL)
    {
        count++;
        printf("%d: Vertex [ %d ]\n", count, aux->info.vertex);
        aux = aux->next;
    }

    printf("\n");
    return count;
}


/// @brief Returns the last vertex in the graph
int lastVertex(Graph *graph)
{
    if (graph == NULL || graph->vertexCount == 0)
        return -1;

    return graph->adjacency[graph->vertexCount - 1].id_vertex;
}


/// @brief Returns the first adjacent vertex of a given vertex
int nextAdj(Graph *graph, int vertex)
{
    if (graph == NULL || graph->vertexCount == 0)
    {
        printf("Empty Graph\n");
        return -1;
    }

    int pos = searchVertex(graph, vertex);

    if (pos == -1)
        return -1;

    if (graph->adjacency[pos].first == NULL)
        return -1;

    return graph->adjacency[pos].first->info.vertex;
}


/// @brief Returns an adjacent vertex at a specific list position
int getAdjacentByPosition(Graph *graph, int vertex, int listPosition)
{
    if (graph == NULL || graph->vertexCount == 0)
        return -1;

    int pos = searchVertex(graph, vertex);
    if (pos == -1)
        return -1;

    Node *aux = graph->adjacency[pos].first;

    for (int i = 1; aux != NULL && i < listPosition; i++)
        aux = aux->next;

    return (aux == NULL) ? -1 : aux->info.vertex;
}


/// @brief Frees the entire graph
void freeGraph(Graph *graph)
{
    if (graph == NULL)
        return;

    for (int i = 0; i < graph->vertexCount; i++)
        freeList(&graph->adjacency[i]);

    free(graph->adjacency);
    free(graph);
}
