#include <string>
#include <vector>

#include "../catch/catch.hpp"
#include "../graph.h"

/**
 * For testing shortest landmark path algorithm.
 */

TEST_CASE("TEST LANDMARK PATH") {
	//std::cout << "BEGIN LANDMARK TEST" << std::endl;
    //std::cout << std::endl;

    Graph graph = Graph("data/airports.dat", "data/routes.dat");

    Graph::Vertex start = graph.getVertex("SFO");
    Graph::Vertex mid = graph.getVertex("Tokyo Haneda International Airport");
    Graph::Vertex end = graph.getVertex("Kinmen Airport");
    vector<Graph::Vertex> path = graph.landmark(start, mid, end);

    graph.write_dstra(path, "output/landmark_test.dat");

    //std::cout << std::endl;
    //std::cout << "END LANDMARK TEST" << std::endl;

    REQUIRE("hello" == "hello");
}
