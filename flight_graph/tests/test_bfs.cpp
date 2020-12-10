#include <string>
#include <vector>
#include "../graph.h"

//Catch Files sourced from https://github-dev.cs.illinois.edu/cs225-fa20/rittika2-gcevans-bradsol-xz33
#include "../catch/catch.hpp"

/**
 * For testing graph traversal.
 */

TEST_CASE("TEST BFS TRAVERSAL") {
	//std::cout << "BEGIN BFS TEST" << std::endl;
    //std::cout << std::endl;

    Graph graph = Graph("data/airports.dat", "data/routes.dat");

    //bool omitUnconnected = false;
    //graph.writeGraph("output/graph_data.dat", omitUnconnected);

    Graph::Vertex start = graph.getVertex("Kasese Airport");
    //Graph::Vertex start = graph.getVertex("Yarram Airport");
    vector<Graph::Vertex> traversal = graph.bfs(start);

    graph.write_bfs(traversal, "output/bfs_output/bfs_test1.dat");

    //std::cout << std::endl;
    //std::cout << "END BFS TEST" << std::endl;

    REQUIRE("hello" == "hello");
}
/*
TEST_CASE("BFS CROSSCHECK") {
    Graph graph = Graph("data/airports.dat", "data/routes.dat");

    //bool omitUnconnected = false;
    //graph.writeGraph("output/graph_data.dat", omitUnconnected);

    Graph::Vertex start = graph.getVertex("Kasese Airport");
    //Graph::Vertex start = graph.getVertex("Yarram Airport");
    vector<Graph::Vertex> traversal = graph.bfs(start);
    vector<Graph::Vertex> traversal2 = graph.bfs2(start);

    graph.write_bfs(traversal, "output/bfs_output/bfs_comparison1.dat");
    graph.write_bfs(traversal2, "output/bfs_output/bfs_comparison2.dat");

    //std::cout << std::endl;
    //std::cout << "END BFS TEST" << std::endl;

    REQUIRE(traversal.size() == traversal2.size());
}
*/
/**
 * BFS Traversal, small graph
 */
TEST_CASE("Small Traversal") {
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
    graph.addEdge(Graph::Edge("AIRLINE5", "CODE5-1", 5, 
            "CODE4-1", 4, graph.calcDistance(graph.getVertex(5).lat, graph.getVertex(5).lng, 
            graph.getVertex(4).lat, graph.getVertex(4).lng), 0) );

    Graph::Vertex start = graph.getVertex(1);
    vector<Graph::Vertex> testTraversal = graph.bfs(start);
    //vector<Graph::Vertex> testTraversal2 = graph.bfs2(start);
    vector<int> correctCodeOrder = {1, 4, 2, 3, 5};
    
    for (unsigned i = 0; i < testTraversal.size(); i++) {
        REQUIRE(testTraversal[i].code == correctCodeOrder[i]);
    }
    /*
    for (unsigned i = 0; i < testTraversal.size(); i++) {
        REQUIRE(testTraversal2[i].code == correctCodeOrder[i]);
    }
    */
}

