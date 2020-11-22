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
                Vertex(int code_, string name_, string city_, string city2_, string country_, 
                string code_iata_, string code_icao_, long double lat_, long double lng_) 
                {
                    code = code_;
                    name = name_;
                    city = city_;
                    city2 = city2_;
                    country = country_;
                    code_iata = code_iata_;
                    code_icao = code_icao_;
                    lat = lat_;
                    lng = lng_;
                }
                int code;
                string name;
                string city;
                string city2;
                string country;
                string code_iata;
                string code_icao;
                long double lat;
                long double lng;

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
                Edge(string airline_, string sourceCode_letter_, int sourceCode_, 
                string destCode_letter_, int destCode_, long double dist_)
                {
                    airline = airline_;
                    sourceCode_letter = sourceCode_letter_;
                    sourceCode = sourceCode_;
                    destCode_letter = destCode_letter_;
                    destCode = destCode_;
                    dist = dist_;
                }
                string airline;
                string sourceCode_letter;
                int sourceCode;
                string destCode_letter;
                int destCode;
                long double dist;

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

        void writeAirportData(string outputFile);

        void writeRouteData(string outputFile);
        
    private:
        /** Data file processing helper functions */
        void processAirportData(string airportFile);
        void processRouteData(string routeFile);

        /** Graph construction, copy and destruction helper functions */
        void buildGraph();
        void copy(const Graph & other);
        void clear();

        /** Data Structure to store airport vertices and flight route edges */ 
        map<int, Vertex> airports;
        vector<Edge> routes;

        string airportFile;
        string routeFile;
        map<string, int> airportDict;
};
