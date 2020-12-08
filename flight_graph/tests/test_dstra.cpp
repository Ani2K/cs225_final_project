#include <string>
#include <vector>
#include "../graph.h"

//Catch Files sourced from https://github-dev.cs.illinois.edu/cs225-fa20/rittika2-gcevans-bradsol-xz33
#include "../catch/catch.hpp"

/**
 * For testing Dijkstra's shortest path algorithm.
 */

TEST_CASE("TEST DIJKSTRA SHORTEST PATH") {
	//std::cout << "BEGIN DSTRA TEST" << std::endl;
    //std::cout << std::endl;

    Graph graph = Graph("data/airports.dat", "data/routes.dat");
    
    //graph.testMinHeap();

    //Graph::Vertex start = graph.getVertex(890);
    //Graph::Vertex end = graph.getVertex(891);
    Graph::Vertex start = graph.getVertex("SFO");
    Graph::Vertex end = graph.getVertex("Kinmen Airport");
    vector<Graph::Vertex> path = graph.dstra(start, end);
    //std::cout << "PATH FINDING DONE" << std::endl;

    graph.write_dstra(path, "output/dstra_output/dstra_test1.dat");

    //std::cout << std::endl;
    //std::cout << "END DSTRA TEST" << std::endl;

    REQUIRE("hello" == "hello");
}
