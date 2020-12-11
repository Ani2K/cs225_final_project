#include "graph.h"
#include <iostream>
#include <iomanip>

/**
 * For general testing of graph.
 */
int main() 
{
    //BFS RUNTIME COMPARISON
    Graph graph = Graph("data/airports.dat", "data/routes.dat");
    Graph::Vertex start = graph.getVertex("Kasese Airport");
    vector<Graph::Vertex> traversal = graph.bfs(start);

    graph.write_bfs(traversal, "output/bfs_output/bfs_run1.dat");

    return 0;
}
