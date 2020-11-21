#include "graph.h"
#include <iostream>

/**
 * For general testing of graph.
 */
int main() 
{
    //TEST 1: BOTH DATASETS SHORT - PASSED 0.009s, PRINT 0.01s
        
        Graph graph = Graph("data/airports_text_short.txt", "data/routes_text_short.txt");

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        graph.printAirportData();
        graph.printRouteData();

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        

    //TEST 2: AIRPORT DATASET LONG - FAILED
        /** NOTE: PROCESSING FULL AIRPORT DATASET THROWS INVALID ARG ERROR DUE TO A PARSE DOUBLE CALL, LIKELY INPUT OF \N */
        /*
        Graph graph = Graph("data/airports_text.txt", 0);

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        graph.printRouteData();

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        */

    //TEST 3: ROUTES DATASET LONG - PASSED 0.2s, PRINT 25.5s
        /*
        Graph graph = Graph("data/routes_text.txt", 1);

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        graph.printRouteData();

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        */

    //TEST 4: BOTH DATASETS LONG - FAILED
        /** NOTE: PROCESSING FULL AIRPORT DATASET THROWS INVALID ARG ERROR DUE TO A PARSE DOUBLE CALL, LIKELY INPUT OF \N */
        /*
        Graph graph = Graph("data/airports_text.txt", "data/routes_text.txt");

        std::cout << "BEGIN DATA PROCESSING TEST" << std::endl;

        graph.printAirportData();
        graph.printRouteData();

        std::cout << "END DATA PROCESSING TEST" << std::endl;
        */



    return 0;
}
