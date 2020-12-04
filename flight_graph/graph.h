#pragma once
#include <vector>
#include <string>
#include <map>
#include <list>
#include <unordered_map>
#include <iostream>
#include <ostream>
#include <fstream>
#include <limits>

using std::vector;
using std::string;
using std::map;
using std::list;
using std::unordered_map;
using std::ostream;
using std::ofstream;
using std::numeric_limits;

/** 
 * OpenFlights dataset graph implementation
 */
class Graph 
{
    public:
        /**
         * Interior struct representing flight route (edge)
         * Stores airline IATA or ICAO code, source airport IATA or ICAO code and openflights code, 
         * destination airport IATA or ICAO code and openflights code, distance between the two, and number of stops
         */
        struct Edge
        {
            public:
                Edge(){}
                Edge(string airline_, string sourceCode_letter_, int sourceCode_, 
                string destCode_letter_, int destCode_, long double dist_, int stops_)
                {
                    airline = airline_;
                    sourceCode_letter = sourceCode_letter_;
                    sourceCode = sourceCode_;
                    destCode_letter = destCode_letter_;
                    destCode = destCode_;
                    dist = dist_;
                    stops = stops_;
                }
                /** For sorting of vertex adjlist */
                bool operator<(const Edge & rhs)
                {
                    return this->dist <= rhs.dist;
                }
                /** For removal from vertex adjlist */
                bool operator==(const Edge & rhs)
                {
                    return this->airline == rhs.airline && this->sourceCode == rhs.sourceCode 
                    && this->destCode == rhs.destCode && this->dist == rhs.dist && this->stops == rhs.stops;
                }
                void printInfo()
                {
                    std::cout << "Airline: " << airline << ", from " << sourceCode_letter 
                    << " to " << destCode_letter << ", distance: " << dist << std::endl; 
                }
                void writeInfo(ofstream & fileWriter)
                {
                    fileWriter << "Airline: " << airline << ", from " << sourceCode_letter 
                    << " to " << destCode_letter << ", distance: " << dist << std::endl; 
                }
                string airline = "EMPTY";
                string sourceCode_letter = "EMPTY";
                int sourceCode = -1;
                string destCode_letter = "EMPTY";
                int destCode = -1;
                long double dist = -2;
                int stops = -3;

            private:

        };
        
        /**
         * Interior struct representing airport (vertex).
         * Stores airport openflights code, name, city, second city (if it has one), 
         * country, IATA code (if it has one), ICAO code (if it has one), latitude, longitude.
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
                /** For max priority queue */
                /*
                bool operator<(const Vertex & rhs) const
                {
                    if (this->tentDist == -3) {
                        return false;
                    }
                    if (rhs.tentDist == -3) {
                        return true;
                    }
                    return this->tentDist <= rhs.tentDist;
                }
                */
                /** For min priority queue */
                bool operator>(const Vertex & rhs) const
                {
                    if (this->tentDist == -3) {
                        return true;
                    }
                    if (rhs.tentDist == -3) {
                        return false;
                    }
                    return this->tentDist > rhs.tentDist;
                }
                void printInfo()
                {
                    if (code_iata != "EMPTY") {
                        std::cout << code << ", " << code_iata << ", " << name << ", " 
                        << city << ", " << country << ", " << lat << ", " << lng << std::endl;
                    } else {
                        std::cout << code << ", " << code_icao << ", " << name << ", " 
                        << city << ", " << country << ", " << lat << ", " << lng << std::endl;
                    }
                }
                void writeInfo(ofstream & fileWriter)
                {
                    if (code_iata != "EMPTY") {
                        fileWriter << code << ", " << code_iata << ", " << name << ", " 
                        << city << ", " << country << ", " << lat << ", " << lng << std::endl;
                    } else {
                        fileWriter << code << ", " << code_icao << ", " << name << ", " 
                        << city << ", " << country << ", " << lat << ", " << lng << std::endl;
                    }
                }
                void printName()
                {
                    if (code_iata != "EMPTY") {
                        std::cout << code_iata << ", " << name;
                    } else {
                        std::cout << code_icao << ", " << name;
                    }
                }
                void writeName(ofstream & fileWriter)
                {
                    if (code_iata != "EMPTY") {
                        fileWriter << code_iata << ", " << name;
                    } else {
                        fileWriter << code_icao << ", " << name;
                    }
                }
                int code = -1;
                string name = "EMPTY";
                string city = "EMPTY";
                string city2 = "EMPTY";
                string country = "EMPTY";
                string code_iata = "EMPTY";
                string code_icao = "EMPTY";
                long double lat = -2;
                long double lng = -2;
                long double tentDist = -3;

                /** List to store outgoing flight routes (edges). Sorted in ascending distance order. 
                 * For each unique route, only 1 Edge with lowest number of stops is stored */
                list<Edge> adjList;

                /**Hashmap to keep track of existing outgoing routes */
                unordered_map<int, Edge> flightTable;

            private:

        };

        /** Flight graph default ctor */
        Graph();

        /** Flight graph ctor using airport and route data files */
        Graph(string airportFile_, string routeFile_);

        /** Flight graph ctor using either airport or route data file
         * @param choice int to select whether airport or route data file is being used. 0 = airport, 1 = route
         */
        Graph(string dataFile, int choice);

        /** Flight graph dtor */
        ~Graph();

        /** Flight graph copy ctor */
        Graph(const Graph & other);

        /** Flight graph assignment operator */
        Graph const & operator=(const Graph & rhs);

        /** Breadth first traversal of the flight graph */
        vector<Vertex> bfs(Vertex start);

        void print_bfs(vector<Vertex> traversal);

        void write_bfs(vector<Vertex> traversal, string outputFile);

        /** Method for calculating shortest path between two airports using Dijkstra's algorithm */
        vector<Vertex> dstra(Vertex start, Vertex end);

        void print_dstra(vector<Vertex> path);

        void write_dstra(vector<Vertex> path, string outputFile);

        /** Test Vertex minheap */
        //void testMinHeap();

        /** Method for calculating shortest landmark path between two airports */
        vector<Vertex> landmark(Vertex start, Vertex mid, Vertex end);

        /** Adds vertex to graph structure */
        void addVertex(Vertex vertex);

        /** Fetches vertex object from graph structure
         * @param code_ airport's openflights code to search for
         */
        Vertex getVertex(int code_);

        /** Fetches vertex object from graph structure
         * @param code_ airport's name or IATA/ICAO code to search for
         */
        Vertex getVertex(string code_);
        
        /** Adds Edge to graph structure */
        void addEdge(Edge edge);

        /** Creates and adds Edge from two vertex objects */
        void addEdge(Vertex source, Vertex dest, string airline_, int stops_);

        /** Creates and adds Edge from source and destination airport openflights codes */
        void addEdge(int sourceCode_, int destCode_, string airline_, int stops_);

        /** Creates and adds Edge from source and destination airport names or IATA/ICAO codes */
        void addEdge(string sourceCode_, string destCode_, string airline_, int stops_);

        /** Fetches edge object from graph structure
         * @param sourceCode_ source airport's openflights code to search for
         * @param destCode_ destination airport's openflights code to search for
         */
        Edge getEdge(int sourceCode_, int destCode_);

        /** Fetches edge object from graph structure
         * @param sourceCode_ source airport's name or IATA/ICAO code to search for
         * @param destCode_ destination airport's name or IATA/ICAO code to search for
         */
        Edge getEdge(string sourceCode_, string destCode_);

        /** Fetches edge object from graph structure
         * @param source source airport vertex object
         * @param dest destination airport vertex object
         */
        Edge getEdge(Vertex source, Vertex dest);

        // Need to think of good way to implement these
        //void removeVertex(Vertex vertex);

        //void removeVertex(int code_);

        //void removeVertex(string code_);

        /** Removes Edge from graph structure */
        void removeEdge(Edge edge);

        /** Removes Edge based on source and dest Vertices */
        void removeEdge(Vertex source, Vertex dest, string airline_, int stops_);
        
        /** Removes Edge based on source and dest airport openflights codes */
        void removeEdge(int sourceCode_, int destCode_, string airline_, int stops_);

        /** Removes Edge based on source and dest airport names or IATA/ICAO codes */
        void removeEdge(string sourceCode_, string destCode_, string airline_, int stops_);

        /** Converts an airport's name or IATA/ICAO code to its openflights code 
         *  @return valid code if lookup string is valid, otherwise returns -1
        */
        int convertToCode(string code_);
        
        /** Calculates distance between two lat, lng coordinates
         * Formula sourced from https://www.movable-type.co.uk/scripts/latlong.html
         */
        long double calcDistance(long double lat1, long double lng1, long double lat2, long double lng2);

        long double calcPathDistance(vector<Vertex> path);

        /** Updates data filenames and reprocesses data */
        void updateData(string airportFile_, string routeFile_);

        /** Writes the graph structure's data to an output file
         * @param omitUnconnected bool to select whether to omit airports with no outgoing flights. true = omit, false = keep
         */
        void writeGraph(string outputFile, bool omitUnconnected);
        
        /** Prints airport data to console */
        void printAirportData();

        /** Prints route data to console 
         *  @param validOnly bool to select whether to omit routes with nonexistant source or dest airports. true = omit, false = keep
        */
        void printRouteData(bool validOnly);

        /** Writes airport data to an output file */
        void writeAirportData(string outputFile);

        /** Writes route data to an output file 
         * @param validOnly bool to select whether to omit routes with nonexistant source or dest airports. true = omit, false = keep
        */
        void writeRouteData(string outputFile, bool validOnly);
        
    private:
        /** Processes airport data file into graph structure and airport code dictionary
         *  String trimming code sourced from http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
         *                                    https://www.tutorialspoint.com/how-to-remove-certain-characters-from-a-string-in-cplusplus
         */
        void processAirportData();

        /** Processes route data file into graph structure and route list 
         *  String trimming code sourced from http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
         *                                    https://www.tutorialspoint.com/how-to-remove-certain-characters-from-a-string-in-cplusplus
        */
        void processRouteData();

        /** Graph construction, copy and destruction helper functions */
        void buildGraph();
        void copy(const Graph & other);
        void clear();

        /** Hashmap to store airport vertices, mapped by openflights codes. Each airport maintains list of outgoing flights */ 
        unordered_map<int, Vertex> graph;

        /** Hashmap to store airport openflights codes, mapped by their IATA code, ICAO code, and airport name */
        unordered_map<string, int> airportCodeDict;

        /** List of all routes from route data file */
        vector<Edge> allRoutes;

        /** List of valid (source and dest airport exist) routes from route data file */
        vector<Edge> validRoutes;

        /** List of invalid (nonexistant source or dest airport) routes from route data file */
        vector<Edge> invalidRoutes;

        /** string to store airport data filename */
        string airportFile;

        /** string to store route data filename */
        string routeFile;
};