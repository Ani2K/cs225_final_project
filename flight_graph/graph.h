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
    public:
        /**
         * Interior class representing airport.
         * Stores airport name, city, latitude, and longitude.
         */
        struct Vertex
        {
            public:
                Vertex() {}
                Vertex(string name_, string code_, string city_, string country_, double lat_, double lng_) 
                {
                    name = name_;
                    code = code_;
                    city = city_;
                    country = country_;
                    lat = lat_;
                    lng = lng_;
                }
                string name;
                string code;
                string city;
                string country;
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
                Edge(){}
                Edge(string sourceCode_, string destCode_, string airline_, double dist_)
                {
                    sourceCode = sourceCode_;
                    destCode = destCode_;
                    dist = dist_;
                    airline = airline_;
                }
                string sourceCode;
                string destCode;
                string airline;
                double dist;

            private:

        };

        Graph();

        /** Flight graph ctors using data files */
        Graph(string airportFile, string routeFile);
        Graph(string dataFile, int choice);

        /** Flight graph dtor */
        ~Graph();

        /** Flight graph copy ctor */
        Graph(const Graph & other);

        /** Flight graph assignment operator */
        Graph const & operator=(const Graph & rhs);

        /** Breadth first traversal of the flight graph */
        //vector<Vertex> bfs();

        /** Method for calculating shortest path between two airports using Dijkstra's algorithm */
        //vector<Vertex> dstra(Vertex start, Vertex end);

        /** Method for calculating shortest landmark path between two airports */
        //vector<Vertex> landmark(Vertex start, Vertex mid, Vertex end);

        void printAirportData();

        void printRouteData();
        
    private:
        /** Data file processing helper functions */
        void processAirportData(string airportFile);
        void processRouteData(string routeFile);

        /** Graph construction, copy and destruction helper functions */
        void buildGraph();
        void copy(const Graph & other);
        void clear();

        /** Data Structure to store airport vertices and flight route edges */ 
        map<string, Vertex> airports;
        vector<Edge> routes;
        string airportFile;
        string routeFile;
};