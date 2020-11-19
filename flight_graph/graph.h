#pragma once
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::map;

/** 
 * OpenFlights dataset graph implementation
 */
class Graph 
{
    private:
        /**
         * Interior class representing airport.
         * Stores airport name, city, latitude, and longitude.
         */
        struct Vertex
        {
            public:
                string name;
                string city;
                double lat;
                double lng;

            private:

        };

        /**
         * Interior class representing flight route.
         * Stores source and destination airports as well as distance between.
         */
        struct Edge
        {
            public:
                Vertex source;
                Vertex dest;
                double dist;

            private:

        };

    public:
        /** Flight graph ctor using data file */
        Graph(string fileName);

        /** Flight graph dtor */
        ~Graph();

        /** Flight graph copy ctor */
        Graph(const Graph & other);

        /** Flight graph assignment operator */
        Graph const & operator=(const Graph & rhs);

        /** Breadth first traversal of the flight graph */
        vector<Vertex> bfs();

        /** Method for calculating shortest path between two airports using Dijkstra's algorithm */
        vector<Vertex> dstra(Vertex start, Vertex end);

        /** Method for calculating shortest landmark path between two airports */
        vector<Vertex> landmark(Vertex start, Vertex mid, Vertex end);

    private:
        /** Data file processing helper function */
        void processData(string aiportFile, string flightFile);

        /** Graph construction, copy and destruction helper functions */
        void buildGraph();
        void copy(const Graph & other);
        void clear();

        /** Data Structure to store airport vertices and flight route edges */ 
        map<string, Vertex> airports;
        vector<Edge> routes;
};
