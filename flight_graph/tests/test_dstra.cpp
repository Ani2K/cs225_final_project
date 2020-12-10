#include <string>
#include <vector>
#include "../graph.h"

//Catch Files sourced from https://github-dev.cs.illinois.edu/cs225-fa20/rittika2-gcevans-bradsol-xz33
#include "../catch/catch.hpp"

/**
 * For testing Dijkstra's shortest path algorithm.
 */

TEST_CASE("TEST DIJKSTRA SHORTEST PATH, MANUAL SMALL GRAPH") {
    Graph graph = Graph();
    graph.addVertex(Graph::Vertex(1, "AIRPORT 1", "CITY 1", "EMPTY", "COUNTRY 1", 
            "CODE1-1", "CODE1-2", 5, 50) );
    graph.addVertex(Graph::Vertex(2, "AIRPORT 2", "CITY 2", "EMPTY", "COUNTRY 2", 
            "CODE2-1", "CODE2-2", 60, 12) );
    graph.addVertex(Graph::Vertex(3, "AIRPORT 3", "CITY 3", "EMPTY", "COUNTRY 3", 
            "CODE3-1", "CODE3-2", 9, 89) );
    graph.addVertex(Graph::Vertex(4, "AIRPORT 4", "CITY 4", "EMPTY", "COUNTRY 4", 
            "CODE4-1", "CODE4-2", 3, -67) );
    graph.addVertex(Graph::Vertex(5, "AIRPORT 5", "CITY 5", "EMPTY", "COUNTRY 5", 
            "CODE5-1", "CODE5-2", -67, 19) );

    graph.addEdge(Graph::Edge("AIRLINE1", "CODE1-1", 1, 
            "CODE4-1", 4, graph.calcDistance(graph.getVertex(1).lat, graph.getVertex(1).lng, 
            graph.getVertex(4).lat, graph.getVertex(4).lng), 0) );
    graph.addEdge(Graph::Edge("AIRLINE2", "CODE2-1", 2, 
            "CODE5-1", 5, graph.calcDistance(graph.getVertex(2).lat, graph.getVertex(2).lng, 
            graph.getVertex(5).lat, graph.getVertex(5).lng), 0) );
    graph.addEdge(Graph::Edge("AIRLINE3", "CODE3-1", 3, 
            "CODE5-1", 5, graph.calcDistance(graph.getVertex(3).lat, graph.getVertex(3).lng, 
            graph.getVertex(5).lat, graph.getVertex(5).lng), 0) );
    graph.addEdge(Graph::Edge("AIRLINE4", "CODE4-1", 4, 
            "CODE2-1", 2, graph.calcDistance(graph.getVertex(4).lat, graph.getVertex(4).lng, 
            graph.getVertex(2).lat, graph.getVertex(2).lng), 0) );
    graph.addEdge(Graph::Edge("AIRLINE5", "CODE4-1", 4, 
            "CODE3-1", 3, graph.calcDistance(graph.getVertex(4).lat, graph.getVertex(4).lng, 
            graph.getVertex(3).lat, graph.getVertex(3).lng), 0) );
    


    Graph::Vertex start = graph.getVertex("CODE1-1");
    Graph::Vertex end = graph.getVertex("CODE5-1");
    vector<Graph::Vertex> path = graph.dstra(start, end);

    graph.write_dstra(path, "output/dstra_output/dstra_test1.dat");

    REQUIRE(path[0].name == "AIRPORT 1");
    REQUIRE(path[1].name == "AIRPORT 4");
    REQUIRE(path[2].name == "AIRPORT 2");
    REQUIRE(path[3].name == "AIRPORT 5");

    
} 

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
