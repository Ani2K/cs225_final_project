#include "graph.h"
#include <iostream>
#include <iomanip>

/**
 * For general testing of graph.
 */
int main() 
{
    //TEST 1: DATA PROCESSING - BOTH DATASETS SHORT - PASSED 0.009s, PRINT 0.01s
        /*
        Graph graph = Graph("data/airports_text_short.txt", "data/routes_text_short.txt");

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        bool validOnly = false;
        graph.writeAirportData("output/processed_airport_data.txt");
        graph.writeRouteData("output/processed_route_data.txt", validOnly);

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        */

    //TEST 2: DATA PROCESSING - AIRPORT DATASET LONG - PASSED 0.096s, PRINT 3.125s
        /** NOTE: PROCESSING FULL AIRPORT DATASET THROWS INVALID ARG ERROR DUE TO A PARSE DOUBLE CALL, LIKELY INPUT OF \N */
        /*
        Graph graph = Graph("data/airports_text.txt", 0);

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        graph.writeAirportData("output/processed_airport_data.txt");

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        */

    //TEST 3: DATA PROCESSING - ROUTES DATASET LONG - PASSED 0.2s, PRINT 25.5s
        /*
        Graph graph = Graph("data/routes_text.txt", 1);

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        bool validOnly = false;
        graph.writeRouteData("output/processed_route_data.txt", validOnly);

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        */

    //TEST 4: DATA PROCESSING - BOTH DATASETS LONG - PASSED 0.273s, WRITE 2.571s
        /** NOTE: PROCESSING FULL AIRPORT DATASET THROWS INVALID ARG ERROR DUE TO A PARSE DOUBLE CALL, LIKELY INPUT OF \N */
        /** NOTE: THERE ARE PROBLEMATIC ENTRIES WITH 2 CITY NAMES, EXTRA COMMAS.
         *        EDITED THESE ENTRIES MANUALLY, SAVED THIS AND PROBLEM ENTRIES AS SEPARATE FILES.
         */
        /*
        Graph graph = Graph("data/airports_text.txt", "data/routes_text.txt");

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        bool validOnly = false;
        graph.writeAirportData("output/processed_airport_data.txt");
        graph.writeRouteData("output/processed_route_data.txt", validOnly);

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        */

    //TEST 5: GRAPH STRUCTURE - BOTH DATASETS - PASSED, WRITE 1.8s
        /*
        std::cout << "BEGIN GRAPH STRUCTURE TEST" << std::endl;
        Graph graph = Graph("data/airports.dat", "data/routes.dat");

        bool omitUnconnected = false;
        graph.writeGraph("output/graph_data.dat", omitUnconnected);
        //graph.writeGraph("output/graph_data.txt", omitUnconnected);

        //graph.updateData("data/airports_text_short.txt", "data/routes.dat");
        //graph.writeGraph("output/graph_data_short.dat", omitUnconnected);

        std::cout << "END GRAPH STRUCTURE TEST" << std::endl;
        */

    //TEST 6: GRAPH STRUCTURE - INFO RETRIEVAL AND MANUAL ADDITIONS - PASSED
        /*
        std::cout << "BEGIN GRAPH STRUCTURE TEST" << std::endl;
        std::cout << std::endl;

        Graph graph = Graph("data/airports.dat", "data/routes.dat");

        bool omitUnconnected = false;
        graph.writeGraph("output/graph_data.dat", omitUnconnected);

        Graph::Vertex v1 = graph.getVertex("Chicago O'Hare International Airport");
        Graph::Vertex v2 = graph.getVertex("SFO");
        Graph::Vertex v3 = graph.getVertex(9239);

        Graph::Edge e1 = graph.getEdge("ORD", "SFO");
        Graph::Edge e2 = graph.getEdge(9239, 3830);

        v1.printInfo();
        v2.printInfo();
        v3.printInfo();
        e1.printInfo();
        e2.printInfo();

        graph.addEdge(v1, v3, "FAKE PLANE", 0);
        e2 = graph.getEdge("ORD", "CND4");
        e2.printInfo();
        e2 = graph.getEdge(v3, v1);
        e2.printInfo();

        graph.addEdge(v3, v1, "FAKER PLANE", 0);
        e2 = graph.getEdge(v3, v1);
        e2.printInfo();

        graph.addEdge("FAKEAIRPORT", "CND4", "FAKEST PLANE", 0);
        Graph::Edge e3 = graph.getEdge("FAKEAIRPORT", "CND4");
        e3.printInfo();

        graph.addEdge("SFO", "CND4", "FAKEST PLANE", 0);
        e3 = graph.getEdge("SFO", "CND4");
        e3.printInfo();
        graph.removeEdge("SFO", "CND4", "FAKEST PLANE", 0);
        e3 = graph.getEdge("SFO", "CND4");
        e3.printInfo();

        std::cout << std::endl;
        std::cout << "END GRAPH STRUCTURE TEST" << std::endl;
        */

    //TEST 7: MANUAL DATA ENTRY -> GRAPH STRUCTURE - PASSED
        /*
        std::cout << "BEGIN MANUAL ENTRY GRAPH TEST" << std::endl;

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
        graph.writeGraph("output/graph_data_manual.dat", omitUnconnected);

        std::cout << "BEGIN MANUAL ENTRY GRAPH TEST" << std::endl;
        */
    
    //TEST 8: BFS TEST - PASSED INITIAL TESTING
        /*
        std::cout << "BEGIN BFS TEST" << std::endl;
        std::cout << std::endl;

        Graph graph = Graph("data/airports.dat", "data/routes.dat");

        bool omitUnconnected = false;
        graph.writeGraph("output/graph_data.dat", omitUnconnected);

        Graph::Vertex start = graph.getVertex("Kasese Airport");
        //Graph::Vertex start = graph.getVertex("Yarram Airport");
        vector<Graph::Vertex> traversal = graph.bfs(start);

        graph.write_bfs(traversal, "output/bfs_test.dat");

        std::cout << std::endl;
        std::cout << "END BFS TEST" << std::endl;
        */

    //TEST 9: DTSRA TEST - PASSED INITIAL TESTING
        
        std::cout << "BEGIN DSTRA TEST" << std::endl;
        std::cout << std::endl;

        Graph graph = Graph("data/airports.dat", "data/routes.dat");

        //bool omitUnconnected = false;
        //graph.writeGraph("output/graph_data.dat", omitUnconnected);
        
        //graph.testMinHeap();

        //Graph::Vertex start = graph.getVertex(890);
        //Graph::Vertex end = graph.getVertex(891);
        Graph::Vertex start = graph.getVertex("SFO");
        Graph::Vertex end = graph.getVertex("Kinmen Airport");
        vector<Graph::Vertex> path = graph.dstra(start, end);
        //std::cout << "PATH FINDING DONE" << std::endl;

        graph.write_dstra(path, "output/dstra_test.dat");

        std::cout << std::endl;
        std::cout << "END DSTRA TEST" << std::endl;
        

    return 0;
}
