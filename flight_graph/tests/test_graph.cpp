#include <string>
#include <vector>
#include <cmath>
#include "../graph.h"

//Catch Files sourced from https://github-dev.cs.illinois.edu/cs225-fa20/rittika2-gcevans-bradsol-xz33
#include "../catch/catch.hpp"

/**
 * For testing data processing and graph structure.
 */
TEST_CASE("TEST DATA PROCESSING SHORT") {
    Graph graph = Graph("data/airports_text_short.txt", "data/routes.dat");

    bool omitUnconnected = false;
    graph.writeGraph("output/graph_output/graph_data_short.dat", omitUnconnected);

    Graph::Vertex v1 = graph.getVertex("Kangerlussuaq Airport");
        REQUIRE(v1.adjList.size() == 2);
}

TEST_CASE("TEST DATA PROCESSING & UPDATING LONG") {
    Graph graph = Graph("data/airports.dat", "data/routes.dat");

    bool omitUnconnected = false;
    graph.writeGraph("output/graph_output/graph_data.dat", omitUnconnected);

    Graph::Vertex v1 = graph.getVertex("Kangerlussuaq Airport");
        REQUIRE(v1.adjList.size() == 7);

    graph.updateData("data/airports_text_short.txt", "data/routes.dat");

    v1 = graph.getVertex("Kangerlussuaq Airport");
        REQUIRE(v1.adjList.size() == 2);
}

TEST_CASE("TEST GRAPH STRUCTURE MANUAL ENTRY") {
    Graph graph = Graph();
    graph.addVertex(Graph::Vertex(1, "AIRPORT 1", "CITY 1", "EMPTY", "COUNTRY 1", 
            "CODE1-1", "CODE1-2", -51.231243214, 1.1231242134) );
    graph.addVertex(Graph::Vertex(2, "AIRPORT 2", "CITY 2", "EMPTY", "COUNTRY 2", 
            "CODE2-1", "CODE2-2", 10.2312312, -3.32423513) );
    graph.addVertex(Graph::Vertex(3, "AIRPORT 3", "CITY 3", "EMPTY", "COUNTRY 3", 
            "CODE3-1", "CODE3-2", 15.242134, 34.2313253215) );
    graph.addVertex(Graph::Vertex(4, "AIRPORT 4", "CITY 4", "EMPTY", "COUNTRY 4", 
            "CODE4-1", "CODE4-2", 51.231243214, -1.1231242134) );
    graph.addVertex(Graph::Vertex(5, "AIRPORT 5", "CITY 5", "EMPTY", "COUNTRY 5", 
            "CODE5-1", "CODE5-2", 90.2141235, -15.34213532) );

    graph.addEdge(Graph::Edge("AIRLINE1", "CODE1-1", 1, 
            "CODE4-2", 4, graph.calcDistance(graph.getVertex(1).lat, graph.getVertex(1).lng, 
            graph.getVertex(4).lat, graph.getVertex(4).lng), 0) );
    graph.addEdge(Graph::Edge("AIRLINE2", "CODE2-1", 2, 
            "CODE4-2", 4, graph.calcDistance(graph.getVertex(2).lat, graph.getVertex(2).lng, 
            graph.getVertex(4).lat, graph.getVertex(4).lng), 0) );
    graph.addEdge(Graph::Edge("AIRLINE3", "CODE3-1", 3, 
            "CODE5-2", 5, graph.calcDistance(graph.getVertex(3).lat, graph.getVertex(3).lng, 
            graph.getVertex(5).lat, graph.getVertex(5).lng), 0) );

    bool omitUnconnected = false;
    graph.writeGraph("output/graph_output/graph_data_manual1.dat", omitUnconnected);
    
    graph.removeVertex(4);

    graph.writeGraph("output/graph_output/graph_data_manual2.dat", omitUnconnected);

    Graph::Vertex v1 = graph.getVertex("AIRPORT 1");
        REQUIRE(v1.name == "AIRPORT 1");
    Graph::Vertex v2 = graph.getVertex("AIRPORT 2");
        REQUIRE(v2.name == "AIRPORT 2");
    Graph::Vertex v3 = graph.getVertex("AIRPORT 3");
        REQUIRE(v3.name == "AIRPORT 3");
    Graph::Vertex v4 = graph.getVertex("AIRPORT 4");
        REQUIRE(v4.name == "EMPTY");
    Graph::Vertex v5 = graph.getVertex("AIRPORT 5");
        REQUIRE(v5.name == "AIRPORT 5");

    Graph::Edge e1 = graph.getEdge("AIRPORT 1", "AIRPORT 4");
        REQUIRE(e1.sourceCode_letter == "EMPTY");
        REQUIRE(e1.destCode_letter == "EMPTY");
    Graph::Edge e2 = graph.getEdge("AIRPORT 2", "AIRPORT 4");
        REQUIRE(e2.sourceCode_letter == "EMPTY");
        REQUIRE(e2.destCode_letter == "EMPTY");
    Graph::Edge e3 = graph.getEdge("AIRPORT 3", "AIRPORT 5");
        REQUIRE(e3.sourceCode_letter == "CODE3-1");
        REQUIRE(e3.destCode_letter == "CODE5-2");
}

TEST_CASE("TEST GRAPH STRUCTURE RETRIEVAL & MANIPULATION") {
    Graph graph = Graph("data/airports.dat", "data/routes.dat");

    //bool omitUnconnected = false;
    //graph.writeGraph("output/graph_output/graph_data.dat", omitUnconnected);

    Graph::Vertex v1 = graph.getVertex("Chicago O'Hare International Airport");
        REQUIRE(v1.code == 3830);
        REQUIRE(v1.name == "Chicago O'Hare International Airport");
        REQUIRE(v1.city == "Chicago");
        REQUIRE(v1.city2 == "EMPTY");
        REQUIRE(v1.country == "United States");
        REQUIRE(v1.code_iata == "ORD");
        REQUIRE(v1.code_icao == "KORD");
        REQUIRE(std::abs(v1.lat - 41.9786) <= 0.01);
        REQUIRE(std::abs(v1.lng - -87.9048) <= 0.01);
    Graph::Vertex v2 = graph.getVertex("SFO");
        REQUIRE(v2.code == 3469);
        REQUIRE(v2.name == "San Francisco International Airport");
        REQUIRE(v2.city == "San Francisco");
        REQUIRE(v2.city2 == "EMPTY");
        REQUIRE(v2.country == "United States");
        REQUIRE(v2.code_iata == "SFO");
        REQUIRE(v2.code_icao == "KSFO");
        REQUIRE(std::abs(v2.lat - 37.61899948120117) <= 0.01);
        REQUIRE(std::abs(v2.lng - -122.375) <= 0.01);
    Graph::Vertex v3 = graph.getVertex(9239);
        REQUIRE(v3.code == 9239);
        REQUIRE(v3.name == "Stanhope Municipal Airport");
        REQUIRE(v3.city == "Haliburton");
        REQUIRE(v3.city2 == "EMPTY");
        REQUIRE(v3.country == "Canada");
        REQUIRE(v3.code_iata == "EMPTY");
        REQUIRE(v3.code_icao == "CND4");
        REQUIRE(std::abs(v3.lat - 45.1108333333) <= 0.01);
        REQUIRE(std::abs(v3.lng - -78.64) <= 0.01);

    Graph::Edge e1 = graph.getEdge("ORD", "SFO");
        REQUIRE(e1.airline == "AA");
        REQUIRE(e1.sourceCode_letter == "ORD");
        REQUIRE(e1.sourceCode == 3830);
        REQUIRE(e1.destCode_letter == "SFO");
        REQUIRE(e1.destCode == 3469);
        REQUIRE(std::abs(e1.dist - 2963.96) <= 1);
        REQUIRE(e1.stops == 0);
    Graph::Edge e2 = graph.getEdge(9239, 3830);
        REQUIRE(e2.airline == "EMPTY");
        REQUIRE(e2.sourceCode_letter == "EMPTY");
        REQUIRE(e2.sourceCode == -1);
        REQUIRE(e2.destCode_letter == "EMPTY");
        REQUIRE(e2.destCode == -1);
        REQUIRE(e2.dist == -2);
        REQUIRE(e2.stops == -3);

    graph.addEdge(v1, v3, "FAKE PLANE", 0);
    e2 = graph.getEdge("ORD", "CND4");
        REQUIRE(e2.sourceCode_letter == "ORD");
        REQUIRE(e2.destCode_letter == "CND4");
        REQUIRE(std::abs(e2.dist - 823.294) <= 1);
    e2 = graph.getEdge(v3, v1);
        REQUIRE(e2.sourceCode_letter == "EMPTY");
        REQUIRE(e2.destCode_letter == "EMPTY");
        REQUIRE(e2.dist == -2);
    graph.addEdge(v3, v1, "FAKER PLANE", 0);
    e2 = graph.getEdge(v3, v1);
        REQUIRE(e2.sourceCode_letter == "CND4");
        REQUIRE(e2.destCode_letter == "ORD");
        REQUIRE(std::abs(e2.dist - 823.294) <= 1);
    graph.addEdge("FAKEAIRPORT", "CND4", "FAKEST PLANE", 0);
    Graph::Edge e3 = graph.getEdge("FAKEAIRPORT", "CND4");
        REQUIRE(e3.sourceCode_letter == "EMPTY");
        REQUIRE(e3.destCode_letter == "EMPTY");
        REQUIRE(e3.dist == -2);
    graph.addEdge("SFO", "CND4", "FAKEST PLANE", 0);
    e3 = graph.getEdge("SFO", "CND4");
        REQUIRE(e3.sourceCode_letter == "SFO");
        REQUIRE(e3.destCode_letter == "CND4");
        REQUIRE(std::abs(e3.dist -  3696.32) <= 1);
    graph.removeEdge("SFO", "CND4", "FAKEST PLANE", 0);
    e3 = graph.getEdge("SFO", "CND4");
        REQUIRE(e3.sourceCode_letter == "EMPTY");
        REQUIRE(e3.destCode_letter == "EMPTY");
        REQUIRE(e3.dist == -2);
}
