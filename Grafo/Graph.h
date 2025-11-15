//
// Created by victo on 15/11/2025.
//

#ifndef GRAFO_GRAPH_H
#define GRAFO_GRAPH_H

#define True 0
#define False 1

typedef struct info
{
    int vertex;
    int weight;
} Info;

typedef struct node
{
    Info info;
    struct node *next;
} Node;

typedef struct list
{
    int id_vertex;
    Node *first;
} List;

typedef struct Graph
{
    List *adjacency;
    int vertexCount;
} Graph;

Graph *createGraph();
void freeGraph(Graph *graph);

int searchVertex(Graph *graph, int vertex);
void addVertex(Graph *graph, int vertex);
int removeVertex(Graph *graph, int vertex);
int lastVertex(Graph *graph);

int addEdge(Graph *graph, int initialVertex, int finalVertex, int weight);
int edgeExists(Graph *graph, int initialVertex, int finalVertex);
int nextAdj(Graph *graph, int vertex);
int getAdjacentByPosition(Graph *graph, int vertex, int listPosition);

void insertIntoList(List *list, Node *node);
void freeList(List *list);

void printVertices(Graph *graph);
void printGraph(Graph *graph);
int printAdjacentVertices(Graph *graph, int vertex);

#endif //GRAFO_GRAPH_H