#include <string>
#include <vector>

#include "../catch/catch.hpp"
#include "../graph.h"

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

    graph.write_bfs(traversal, "output/bfs_test.dat");

    //std::cout << std::endl;
    //std::cout << "END BFS TEST" << std::endl;

    REQUIRE("hello" == "hello");
}

TEST_CASE("BFS CROSSCHECK") {
    Graph graph = Graph("data/airports.dat", "data/routes.dat");

    //bool omitUnconnected = false;
    //graph.writeGraph("output/graph_data.dat", omitUnconnected);

    Graph::Vertex start = graph.getVertex("Kasese Airport");
    //Graph::Vertex start = graph.getVertex("Yarram Airport");
    vector<Graph::Vertex> traversal = graph.bfs(start);
    vector<Graph::Vertex> traversal2 = graph.bfs2(start);

    graph.write_bfs(traversal, "output/bfs_test.dat");
    graph.write_bfs(traversal2, "output/bfs_test2.dat");

    //std::cout << std::endl;
    //std::cout << "END BFS TEST" << std::endl;

    REQUIRE(traversal.size() == traversal2.size());
}
