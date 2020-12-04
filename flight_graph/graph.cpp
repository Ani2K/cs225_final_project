#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <queue>
#include "graph.h"

using std::vector;
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::unordered_map;
using std::queue;
using std::priority_queue;
using std::pair;

Graph::Graph()
{

}

Graph::Graph(string airportFile_, string routeFile_)
{
    airportFile = airportFile_;
    routeFile = routeFile_;
    processAirportData();
    processRouteData();
}

Graph::Graph(string dataFile, int choice)
{
    if (choice == 0) {
        airportFile = dataFile;
        processAirportData();
    } else if (choice == 1) {
        routeFile = dataFile;
        processRouteData();
    }
}

Graph::~Graph()
{
    clear();
}

Graph::Graph(const Graph & other)
{
    copy(other);
}

const Graph & Graph::operator=(const Graph & rhs)
{
    clear();
    copy(rhs);
    return *this;
}

vector<Graph::Vertex> Graph::bfs(Vertex start)
{
    vector<Vertex> traversal;
    queue<Vertex> neighbors;
    unordered_map<int, bool> visited; //might want to replace with set of some sort?
    
    neighbors.push(start);
    while (!neighbors.empty()) {
        Vertex curr = neighbors.front();
        neighbors.pop();

        while (visited.find(curr.code) != visited.end() && !neighbors.empty()) {
            curr = neighbors.front();
            neighbors.pop();
        }
        if (visited.find(curr.code) == visited.end()) {
            for (Edge edge : curr.adjList) {
                if (visited.find(edge.destCode) == visited.end()) {
                    neighbors.push(graph[edge.destCode]);
                }
            }
            visited[curr.code] = true;
            traversal.push_back(curr);
        }
    }
    return traversal;
}

void Graph::print_bfs(vector<Graph::Vertex> traversal)
{
    std::cout << "---BFS TRAVERSAL OF GRAPH STARTING FROM [";
    traversal[0].printName();
    std::cout << "]---" << std::endl;
    std::cout << std::endl;

    for (Vertex vertex : traversal) {
        vertex.printInfo();
    }

    std::cout << std::endl;
    std::cout << "---END OF TRAVERSAL---";
}

void Graph::write_bfs(vector<Graph::Vertex> traversal, string outputFile)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);
    fileWriter << "---BFS TRAVERSAL OF GRAPH STARTING FROM [";
    traversal[0].writeName(fileWriter);
    fileWriter << "]---" << std::endl;
    fileWriter << std::endl;

    for (Vertex vertex : traversal) {
        vertex.writeInfo(fileWriter);
    }

    fileWriter << std::endl;
    fileWriter << "---END OF TRAVERSAL---";
    fileWriter.close();
}


vector<Graph::Vertex> Graph::dstra(Vertex start, Vertex end)
{
    vector<Vertex> path;
    int startCode = start.code;
    int endCode = end.code;

    if (graph.find(startCode) == graph.end() || graph.find(endCode) == graph.end()) {
        return path;
    }
    
    for (pair<int, Vertex> p : graph) {
        p.second.tentDist = -3;
    }
    
    graph[startCode].tentDist = 0;
    unordered_map<int, int> prev;  // initialize a map that maps current node -> its previous node
    priority_queue<Vertex, vector<Vertex>, std::greater<Vertex>> priority;   // initialize the priority queue, minheap
    unordered_map<int, bool> visited; //might want to replace with set of some sort?

    /** Writes traversal for debugging */
    //ofstream fileWriter;
    //fileWriter.open("output/dstra_debug.dat");

    priority.push(graph[startCode]);
    while (!priority.empty()) {
        if (priority.top().code == endCode) {
            break;
        }
        Vertex curr = priority.top();
        priority.pop();
        //fileWriter << "CURR " << curr.name << ", " << curr.tentDist << std::endl;
        for (Edge edge: curr.adjList) {
            if (visited.find(edge.destCode) == visited.end()) {
                if (graph[edge.destCode].tentDist != -3) {
                    if (graph[edge.destCode].tentDist < (edge.dist + curr.tentDist)) {
                        //fileWriter << "NEIGHBOR NO UPDATE " << graph[edge.destCode].name << ", " << graph[edge.destCode].tentDist << std::endl;
                    } else {
                        graph[edge.destCode].tentDist = edge.dist + curr.tentDist;
                        priority.push(graph[edge.destCode]);
                        prev[edge.destCode] = curr.code;
                        //fileWriter << "NEIGHBOR UPDATE " << graph[edge.destCode].name << ", " << graph[edge.destCode].tentDist << std::endl;
                    }
                } else {
                    graph[edge.destCode].tentDist = edge.dist + curr.tentDist;
                    priority.push(graph[edge.destCode]);
                    prev[edge.destCode] = curr.code;
                    //fileWriter << "NEIGHBOR UPDATE " << graph[edge.destCode].name << ", " << graph[edge.destCode].tentDist << std::endl;
                }
            }
        }
        visited[curr.code] =  true;
    }
    //fileWriter.close();

    if (!priority.empty()) {
        Vertex curr = priority.top();
        while (true) {
            path.push_back(curr);
            if (curr.code != startCode) {
                curr = graph[prev.find(curr.code)->second];
            } else {
                break;
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    } else {
        std::cout << "NO PATH" << std::endl;
        return path;
    }
}

void Graph::print_dstra(vector<Vertex> path)
{
    if (path.size() < 2){
        std::cout << "NOT A VIABLE PATH" << std::endl;
        return;
    }
    
    std::cout << "SHORTEST PATH BETWEEN ["; 
    path[0].printName();
    std::cout << "] AND [";
    path[path.size() - 1].printName();
    std::cout << "]" << std::endl;
    std::cout << std::endl;
    for (Vertex v : path) {
        v.printInfo();
    }
    std::cout << std::endl;
    //std::cout << "TOTAL DISTANCE: " << path[path.size() - 1].tentDist << "km" << std::endl;
    std::cout << "TOTAL DISTANCE: " << calcPathDistance(path) << "km" << std::endl;
}

void Graph::write_dstra(vector<Vertex> path, string outputFile)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);

    if (path.size() < 2){
        fileWriter << "NOT A VIABLE PATH" << std::endl;
        return;
    }

    fileWriter << "SHORTEST PATH BETWEEN ["; 
    path[0].writeName(fileWriter);
    fileWriter << "] AND [";
    path[path.size() - 1].writeName(fileWriter);
    fileWriter << "]" << std::endl;
    fileWriter << std::endl;
    for (Vertex v : path) {
        v.writeInfo(fileWriter);
    }
    fileWriter << std::endl;
    fileWriter << "TOTAL DISTANCE: " << calcPathDistance(path) << "km" << std::endl;
    fileWriter.close();
}

/*
void Graph::testMinHeap()
{
    Vertex v1 = Vertex();
    v1.name = "AIR1";
    v1.tentDist = 10;
    Vertex v2 = Vertex();
    v2.name = "AIR2";
    v2.tentDist = 1;
    Vertex v3 = Vertex();
    v3.name = "AIR3";
    //v3.tentDist = 30;
    Vertex v4 = Vertex();
    v4.name = "AIR4";
    //v4.tentDist = 40;
    priority_queue<Vertex, vector<Vertex>, std::greater<Vertex>> pq;
    //priority_queue<Vertex> pq;
    pq.push(v1);
    pq.push(v2);
    pq.push(v3);
    pq.push(v4);
 
    // One by one extract items from min heap
    while (pq.empty() == false)
    {
        std::cout << "[" << pq.top().name << ", " << pq.top().tentDist << "] ";
        pq.pop();
    }
    std::cout << std::endl;
}
*/

vector<Graph::Vertex> Graph::landmark(Vertex start, Vertex mid, Vertex end)
{
    /** to supress warnings */
    start.code = start.code;
    mid.code = mid.code;
    end.code = end.code;
    vector<Vertex> path;
    return path;
}

void Graph::processAirportData()
{
    ifstream airportFileReader(airportFile);
    string airportLine;
    if (airportFileReader.is_open()) {
        while (getline(airportFileReader, airportLine)) {

            stringstream lineRead(airportLine);
            string data;
            int code_ = -1; string name_ = "EMPTY"; string city_ = "EMPTY"; string city2_ = "EMPTY"; string country_ = "EMPTY"; 
            string code_iata_ = "EMPTY"; string code_icao_ = "EMPTY"; long double lat_ = -2; long double lng_ = -2;
            
            vector<string> entries;
            while (getline(lineRead, data, ',')) {
                entries.push_back(data);
            }

            int size = entries.size();
            bool anomalyEntry = false;
            for (int i = 0; i < size; i++) {
                data = entries[i];
                data.erase(remove(data.begin(), data.end(), '"'), data.end());
                
                /** Refer to data/unused_data/data_entry_pattern.txt for data entry pattern */
                if (size > 14) {
                    if (i == 0 || i > 4) {
                        data.erase(remove(data.begin(), data.end(), ' '), data.end());
                    } else if (i > 0 && i < 5) {
                        data.erase(0, data.find_first_not_of(' '));
                        data.erase(data.find_last_not_of(' ') + 1);
                    }
                } else {
                    if (i == 0 || i > 3) {
                        data.erase(remove(data.begin(), data.end(), ' '), data.end());
                    } else if (i > 0 && i < 4) {
                        data.erase(0, data.find_first_not_of(' '));
                        data.erase(data.find_last_not_of(' ') + 1);
                    }
                }

                switch (i) {
                    case 0:
                        code_ = std::stoi(data);
                        break;
                    case 1:
                        name_ = data;
                        break;
                    case 2:
                        if (name_ != "Paloich Airport") {
                            city_ = data;
                        } else {
                            anomalyEntry = true;
                            name_ += ", ";
                            name_ += data;
                        }
                        break;
                    case 3:
                        if (size > 14) {
                            if (anomalyEntry) {
                                city_ = data;
                            } else {
                                city2_ = data;
                            }
                        } else {
                            country_ = data;
                        }
                        break;
                    case 4:
                        if (size > 14) {
                            country_ = data;
                        } else {
                            code_iata_ = data;
                        }
                        break;
                    case 5:
                        if (size > 14) {
                            code_iata_ = data;
                        } else {
                            code_icao_ = data;
                        }
                        break;
                    case 6:
                        if (size > 14) {
                            code_icao_ = data;
                        } else {
                            lat_ = std::stold(data);
                        }
                        break;
                    case 7:
                        if (size > 14) {
                            lat_ = std::stold(data);
                        } else {
                            lng_ = std::stold(data);
                        }
                        break;
                    case 8:
                        if (size > 14) {
                            lng_ = std::stold(data);
                        }
                        break;
                }
            }

            if (code_iata_.length() != 3) {
                code_iata_ = "EMPTY";
            }
            if (code_icao_.length() != 4) {
                code_icao_ = "EMPTY";
            }

            Vertex currAirport = Vertex();
            currAirport.code = code_; currAirport.name = name_; currAirport.city = city_; currAirport.city2 = city2_; 
            currAirport.country = country_; currAirport.code_iata = code_iata_; currAirport.code_icao = code_icao_;
            currAirport.lat = lat_; currAirport.lng = lng_;

            addVertex(currAirport);
        }
    } else {
        std::cout << "NO AIRPORT DATA" << std::endl;
    }
    airportFileReader.close();
}

void Graph::processRouteData()
{
    ifstream routeFileReader(routeFile);
    string routeLine;
    if (routeFileReader.is_open()) {
        while (getline(routeFileReader, routeLine)) {

            stringstream lineRead(routeLine);
            string data;
            int dataCount = 0;
            string airline_ = "EMPTY"; string sourceCode_letter_ = "EMPTY"; int sourceCode_ = -1; 
            string destCode_letter_ = "EMPTY"; int destCode_ = -1; long double dist_ = -2; int stops_ = -3;
            
            while (getline(lineRead, data, ',')) {

                /** Refer to data/unused_data/data_entry_pattern.txt for data entry pattern */
                switch (dataCount) {
                    data.erase(remove(data.begin(), data.end(), '"'), data.end());
                    data.erase(remove(data.begin(), data.end(), ' '), data.end());
                    case 0:
                        airline_ = data;
                        break;
                    case 2:
                        sourceCode_letter_ = data;
                        break;
                    case 3:
                        try
                        {
                            sourceCode_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            sourceCode_ = convertToCode(sourceCode_letter_);
                        }
                        break;
                    case 4:
                        destCode_letter_ = data;
                        break;
                    case 5:
                        try
                        {
                            destCode_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            destCode_ = convertToCode(destCode_letter_);
                        }
                        break;
                    case 7:
                        try
                        {
                            stops_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e) {}
                        break;
                }
                dataCount++;
            }

            Edge currEdge = Edge();
            currEdge.airline = airline_; currEdge.sourceCode_letter = sourceCode_letter_; currEdge.sourceCode = sourceCode_; 
            currEdge.destCode_letter = destCode_letter_; currEdge.destCode = destCode_; currEdge.dist = dist_; currEdge.stops = stops_;

            unordered_map<int, Vertex>::iterator lookupSource = graph.find(sourceCode_);
            unordered_map<int, Vertex>::iterator lookupDest = graph.find(destCode_);

            if (lookupSource != graph.end() && lookupDest != graph.end()) {
                long double lat1 = lookupSource->second.lat;
                long double lng1 = lookupSource->second.lng;
                long double lat2 = lookupDest->second.lat;
                long double lng2 = lookupDest->second.lng;

                dist_ = calcDistance(lat1, lng1, lat2, lng2);
                currEdge.dist = dist_;
                addEdge(currEdge);
            } else {
                invalidRoutes.emplace_back(currEdge);
                allRoutes.emplace_back(currEdge);
            }
        }
    } else {
        std::cout << "NO ROUTE DATA" << std::endl;
    }
    routeFileReader.close();
}

void Graph::updateData(string airportFile_, string routeFile_)
{
    airportFile = airportFile_;
    routeFile = routeFile_;
    graph.clear();
    airportCodeDict.clear();
    allRoutes.clear();
    validRoutes.clear();
    invalidRoutes.clear();
    processAirportData();
    processRouteData();
}

void Graph::addVertex(Vertex vertex)
{
    if (vertex.code_iata != "EMPTY") {
        airportCodeDict[vertex.code_iata] = vertex.code;
    }
    if (vertex.code_icao != "EMPTY") {
        airportCodeDict[vertex.code_icao] = vertex.code;
    }
    if (vertex.name != "EMPTY") {
        airportCodeDict[vertex.name] = vertex.code;
    }
    graph[vertex.code] = vertex;
}

Graph::Vertex Graph::getVertex(int code_)
{
    if (graph.find(code_) != graph.end()) {
        return graph.find(code_)->second;
    }
    return Vertex();
}

Graph::Vertex Graph::getVertex(string code_)
{
    return getVertex(convertToCode(code_));
}

void Graph::addEdge(Edge edge)
{
    unordered_map<int, Vertex>::iterator lookupSource = graph.find(edge.sourceCode);
    unordered_map<int, Vertex>::iterator lookupDest = graph.find(edge.destCode);
    if (lookupSource != graph.end() && lookupDest != graph.end()) {
        unordered_map<int, Edge>::iterator lookupEdge = lookupSource->second.flightTable.find(edge.destCode);
        if (lookupEdge != lookupSource->second.flightTable.end()) {
            if (edge.stops < lookupEdge->second.stops) {
                /** NOTE: comment this block and the table mapping in the else if u want every route to be added */
                lookupSource->second.adjList.remove(lookupEdge->second);
                lookupSource->second.adjList.emplace_front(edge);
                lookupSource->second.adjList.sort();
                lookupSource->second.flightTable[edge.destCode] = edge;
                
            }
        } else {
            lookupSource->second.flightTable[edge.destCode] = edge;
            lookupSource->second.adjList.emplace_front(edge);
            lookupSource->second.adjList.sort();
        }
    }
    allRoutes.emplace_back(edge);
    validRoutes.emplace_back(edge);
}

void Graph::addEdge(Vertex source, Vertex dest, string airline_, int stops_)
{
    Edge currEdge = Edge();

    string sourceCode_letter_; 
    if (source.code_iata != "EMPTY") {
        sourceCode_letter_ = source.code_iata;
    } else {
        sourceCode_letter_ = source.code_icao;
    }
    int sourceCode_ = source.code;
    string destCode_letter_;
    if (dest.code_iata != "EMPTY") {
        destCode_letter_ = dest.code_iata;
    } else {
        destCode_letter_ = dest.code_icao;
    }
    int destCode_ = dest.code;
    long double dist_ = calcDistance(source.lat, source.lng, dest.lat, dest.lng);

    currEdge.airline = airline_; currEdge.sourceCode_letter = sourceCode_letter_; currEdge.sourceCode = sourceCode_; 
    currEdge.destCode_letter = destCode_letter_; currEdge.destCode = destCode_; currEdge.dist = dist_; currEdge.stops = stops_;

    addEdge(currEdge);
}

void Graph::addEdge(int sourceCode_, int destCode_, string airline_, int stops_)
{
    unordered_map<int, Vertex>::iterator lookupSource = graph.find(sourceCode_);
    unordered_map<int, Vertex>::iterator lookupDest = graph.find(destCode_);
    if (lookupSource != graph.end() && lookupDest != graph.end()) {
        addEdge(lookupSource->second, lookupDest->second, airline_, stops_);
    }
}


void Graph::addEdge(string sourceCode_, string destCode_, string airline_, int stops_)
{
    addEdge(convertToCode(sourceCode_), convertToCode(destCode_), airline_, stops_);
}

Graph::Edge Graph::getEdge(int sourceCode_, int destCode_)
{
    if (graph.find(sourceCode_) == graph.end()) {
        return Edge();
    }
    unordered_map<int, Edge> table = graph.find(sourceCode_)->second.flightTable;
    if (table.find(destCode_) != table.end()) {
        return table.find(destCode_)->second;
    }
    return Edge();
}

Graph::Edge Graph::getEdge(string sourceCode_, string destCode_)
{
    return getEdge(convertToCode(sourceCode_), convertToCode(destCode_));
}

Graph::Edge Graph::getEdge(Vertex source, Vertex dest)
{
    return getEdge(source.code, dest.code);
}

void Graph::removeEdge(Edge edge)
{
    int sourceCode_ = edge.sourceCode;
    int destCode_ = edge.destCode;
    unordered_map<int, Vertex>::iterator lookupSource = graph.find(sourceCode_);
    if (lookupSource == graph.end()) {
        return;
    }
    if (lookupSource->second.flightTable.find(destCode_) != lookupSource->second.flightTable.end()) {
        lookupSource->second.adjList.remove(lookupSource->second.flightTable.find(destCode_)->second);
        lookupSource->second.flightTable.erase(lookupSource->second.flightTable.find(destCode_));
    }
}

void Graph::removeEdge(Vertex source, Vertex dest, string airline_, int stops_)
{
    Edge currEdge = Edge();

    string sourceCode_letter_; 
    if (source.code_iata != "EMPTY") {
        sourceCode_letter_ = source.code_iata;
    } else {
        sourceCode_letter_ = source.code_icao;
    }
    int sourceCode_ = source.code;
    string destCode_letter_;
    if (dest.code_iata != "EMPTY") {
        destCode_letter_ = dest.code_iata;
    } else {
        destCode_letter_ = dest.code_icao;
    }
    int destCode_ = dest.code;
    long double dist_ = calcDistance(source.lat, source.lng, dest.lat, dest.lng);

    currEdge.airline = airline_; currEdge.sourceCode_letter = sourceCode_letter_; currEdge.sourceCode = sourceCode_; 
    currEdge.destCode_letter = destCode_letter_; currEdge.destCode = destCode_; currEdge.dist = dist_; currEdge.stops = stops_;

    removeEdge(currEdge);
}

void Graph::removeEdge(int sourceCode_, int destCode_, string airline_, int stops_)
{
    unordered_map<int, Vertex>::iterator lookupSource = graph.find(sourceCode_);
    unordered_map<int, Vertex>::iterator lookupDest = graph.find(destCode_);
    if (lookupSource != graph.end() && lookupDest != graph.end()) {
        removeEdge(lookupSource->second, lookupDest->second, airline_, stops_);
    }
}

void Graph::removeEdge(string sourceCode_, string destCode_, string airline_, int stops_)
{
    removeEdge(convertToCode(sourceCode_), convertToCode(destCode_), airline_, stops_);
}

int Graph::convertToCode(string code_)
{
    unordered_map<string, int>::iterator lookupCode = airportCodeDict.find(code_);
    if (lookupCode != airportCodeDict.end()) {
        return lookupCode->second;
    }
    return -1;
}

long double Graph::calcDistance(long double lat1, long double lng1, long double lat2, long double lng2)
{
    long double R = 6371 * pow(10.0, 3.0); // meters
    long double phi1 = lat1 * M_PI / 180; // φ, λ in radians
    long double phi2 = lat2 * M_PI / 180;
    long double deltaPhi = (lat2 - lat1) * M_PI / 180;
    long double deltaLambda = (lng2 - lng1) * M_PI / 180;

    long double a = sin(deltaPhi / 2) * sin(deltaPhi/2) +
            cos(phi1) * cos(phi2) *
            sin(deltaLambda / 2) * sin(deltaLambda / 2);
    long double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    long double dist = R * c; // in meters
    dist /= 1000; //in kilometers
    return dist;
}

long double Graph::calcPathDistance(vector<Vertex> path)
{
    int size = path.size();
    long double dist = 0;
    for (int i = 0; i < size - 1; i++) {
        dist += getEdge(path[i], path[i + 1]).dist;
    }
    return dist;
}

void Graph::writeGraph(string outputFile, bool omitUnconnected)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);
    int portcount = 0;
    int flightlesscount = 0;
    int totalflights = 0;
    int maxflights = 0;
    string max = "";
    for (std::pair<int, Vertex> curr : graph) {
        portcount++;
        if (curr.second.adjList.size() == 0) {
            flightlesscount++;
            if (omitUnconnected) {
                continue;
            }
        }
        fileWriter << std::endl;
        fileWriter << "------------AIRPORT ENTRY------------" << std::endl;
        fileWriter << std::endl;

        fileWriter << "CODE [" << curr.second.code << "]" << std::endl;
        fileWriter << "NAME [" << curr.second.name << "]" << std::endl;
        fileWriter << "CITY [" << curr.second.city << "]" << std::endl;
        fileWriter << "CITY2 [" << curr.second.city2 << "]" << std::endl;
        fileWriter << "COUNTRY [" << curr.second.country << "]" << std::endl;
        fileWriter << "IATA CODE [" << curr.second.code_iata << "]" << std::endl;
        fileWriter << "ICAO CODE [" << curr.second.code_icao << "]" << std::endl;
        fileWriter << "LAT [" << curr.second.lat << "]" << std::endl;
        fileWriter << "LNG [" << curr.second.lng << "]" << std::endl;

        fileWriter << std::endl;
        fileWriter << "----------FLIGHTS----------" << std::endl;

        for (Edge edge : curr.second.adjList) {
            fileWriter << "AIRLINE [" << edge.airline << "] - ";
            fileWriter << "SOURCE CODE [" << edge.sourceCode << "] - ";
            fileWriter << "DEST CODE [" << edge.destCode << "] - ";
            fileWriter << "DIST [" << edge.dist << "] - ";
            if (edge.stops > 0) {
                fileWriter << "STOPS [" << edge.stops << "]" << std::endl;
            } else {
                fileWriter << "DIRECT" << std::endl;
            }
        }
        int flightcount = curr.second.adjList.size();
        totalflights += curr.second.adjList.size();
        if (flightcount > maxflights) {
            max = curr.second.name;
            maxflights = flightcount;
        }

        fileWriter << std::endl;
        fileWriter << "----------END AIRPORT ENTRY----------" << std::endl;
        fileWriter << std::endl;
    }
    fileWriter << "AIRPORT COUNT [" << portcount << "] - NO OUTGOING AIRPORT COUNT [" << flightlesscount << "]" << std::endl; 
    fileWriter << "TOTAL FLIGHTS [" << totalflights << "]" << std::endl;
    fileWriter << "LARGEST AIRPORT [" << max << "]" << std::endl;
    fileWriter.close();
}

void Graph::printAirportData()
{
    for (std::pair<int, Vertex> curr : graph) {
        std::cout << std::endl;
        std::cout << "------------AIRPORT ENTRY------------" << std::endl;
        std::cout << std::endl;

        std::cout << "CODE [" << curr.second.code << "]" << std::endl;
        std::cout << "NAME [" << curr.second.name << "]" << std::endl;
        std::cout << "CITY [" << curr.second.city << "]" << std::endl;
        std::cout << "CITY2 [" << curr.second.city2 << "]" << std::endl;
        std::cout << "COUNTRY [" << curr.second.country << "]" << std::endl;
        std::cout << "IATA CODE [" << curr.second.code_iata << "]" << std::endl;
        std::cout << "ICAO CODE [" << curr.second.code_icao << "]" << std::endl;
        std::cout << "LAT [" << curr.second.lat << "]" << std::endl;
        std::cout << "LNG [" << curr.second.lng << "]" << std::endl;

        std::cout << std::endl;
        std::cout << "----------END AIRPORT ENTRY----------" << std::endl;
        std::cout << std::endl;
    }
}

void Graph::printRouteData(bool validOnly)
{
    for (Edge edge : allRoutes) {
        if (validOnly) {
            if (edge.dist == -2) {
                continue;
            }
        }

        std::cout << std::endl;
        std::cout << "-------------ROUTE ENTRY-------------" << std::endl;
        std::cout << std::endl;

        std::cout << "AIRLINE [" << edge.airline << "]" << std::endl;
        std::cout << "SOURCE CODE LETTER [" << edge.sourceCode_letter << "]" << std::endl;
        std::cout << "SOURCE CODE [" << edge.sourceCode << "]" << std::endl;
        std::cout << "DEST CODE LETTER [" << edge.destCode_letter << "]" << std::endl;
        std::cout << "DEST CODE [" << edge.destCode << "]" << std::endl;
        std::cout << "DIST [" << edge.dist << "]" << std::endl;
        if (edge.stops != 0) {
            std::cout << "STOPS [" << edge.stops << "]" << std::endl;
        } else {
            std::cout << "DIRECT" << std::endl;
        }

        std::cout << std::endl;
        std::cout << "-----------END ROUTE ENTRY-----------" << std::endl;
        std::cout << std::endl;
    }
}

void Graph::writeAirportData(string outputFile)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);
    for (std::pair<int, Vertex> curr : graph) {
        fileWriter << std::endl;
        fileWriter << "------------AIRPORT ENTRY------------" << std::endl;
        fileWriter << std::endl;

        fileWriter << "CODE [" << curr.second.code << "]" << std::endl;
        fileWriter << "NAME [" << curr.second.name << "]" << std::endl;
        fileWriter << "CITY [" << curr.second.city << "]" << std::endl;
        fileWriter << "CITY2 [" << curr.second.city2 << "]" << std::endl;
        fileWriter << "COUNTRY [" << curr.second.country << "]" << std::endl;
        fileWriter << "IATA CODE [" << curr.second.code_iata << "]" << std::endl;
        fileWriter << "ICAO CODE [" << curr.second.code_icao << "]" << std::endl;
        fileWriter << "LAT [" << curr.second.lat << "]" << std::endl;
        fileWriter << "LNG [" << curr.second.lng << "]" << std::endl;

        fileWriter << std::endl;
        fileWriter << "----------END AIRPORT ENTRY----------" << std::endl;
        fileWriter << std::endl;
    }
    fileWriter.close();
}

void Graph::writeRouteData(string outputFile, bool validOnly)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);
    for (Edge edge : allRoutes) {
        if (validOnly) {
            if (edge.dist == -2) {
                continue;
            }
        }

        fileWriter << std::endl;
        fileWriter << "-------------ROUTE ENTRY-------------" << std::endl;
        fileWriter << std::endl;

        fileWriter << "AIRLINE [" << edge.airline << "]" << std::endl;
        fileWriter << "SOURCE CODE LETTER [" << edge.sourceCode_letter << "]" << std::endl;
        fileWriter << "SOURCE CODE [" << edge.sourceCode << "]" << std::endl;
        fileWriter << "DEST CODE LETTER [" << edge.destCode_letter << "]" << std::endl;
        fileWriter << "DEST CODE [" << edge.destCode << "]" << std::endl;
        fileWriter << "DIST [" << edge.dist << "]" << std::endl;
        if (edge.stops != 0) {
            fileWriter << "STOPS [" << edge.stops << "]" << std::endl;
        } else {
            fileWriter << "DIRECT" << std::endl;
        }

        fileWriter << std::endl;
        fileWriter << "-----------END ROUTE ENTRY-----------" << std::endl;
        fileWriter << std::endl;
    }
    fileWriter.close();
}

void Graph::buildGraph()
{

}

void Graph::copy(const Graph & other)
{
    *this = other;
}

void Graph::clear()
{

}