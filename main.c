#include <stdio.h>
#include "Graph.h"

int main()
{
    Graph *g = createGraph();

    printf("Adding vertices:\n");
    addVertex(g, 10);
    addVertex(g, 5);
    addVertex(g, 20);
    addVertex(g, 15);

    printVertices(g);
    printf("\n");

    printf("Adding edges: \n");
    addEdge(g, 10, 20, 1);
    addEdge(g, 10, 15, 2);
    addEdge(g, 5, 10, 3);
    addEdge(g, 20, 5, 4);

    printGraph(g);

    printf("\nTesting 'searchVertex(15)': %d\n", searchVertex(g, 15));
    printf("Testing 'lastVertex()': %d\n\n", lastVertex(g));

    printf("Adjacent vertices from 10:\n");
    printAdjacentVertices(g, 10);

    printf("Testing getAdjacentByPosition(g, 10, 2): %d\n",
           getAdjacentByPosition(g, 10, 2));

    printf("\nRemoving vertex 10...\n");
    removeVertex(g, 10);
    printGraph(g);

    freeGraph(g);
    return 0;
}
