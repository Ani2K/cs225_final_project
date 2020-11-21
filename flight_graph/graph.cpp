#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include "graph.h"

using std::vector;
using std::string;
using std::map;
using std::ifstream;
using std::stringstream;

Graph::Graph()
{

}

Graph::Graph(string airportFile_, string routeFile_)
{
    airportFile = airportFile_;
    routeFile = routeFile_;
    processAirportData(airportFile);
    processRouteData(routeFile);
}

Graph::Graph(string dataFile, int choice)
{
    if (choice == 0) {
        airportFile = dataFile;
        processAirportData(airportFile);
    } else if (choice == 1) {
        routeFile = dataFile;
        processRouteData(routeFile);
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

/*
vector<Vertex> Graph::bfs()
{

}

vector<Vertex> Graph::dstra(Vertex start, Vertex end)
{

}

vector<Vertex> Graph::landmark(Vertex start, Vertex mid, Vertex end)
{

}
*/

void Graph::processAirportData(string airportFile)
{
    ifstream airportFileReader(airportFile);
    string airportLine;
    if (airportFileReader.is_open()) {
        while (getline(airportFileReader, airportLine)) {
            //std::cout << "ENTRY LINE START" << std::endl;
            //std::cout << std::endl;

            stringstream lineRead(airportLine);
            string data;
            int dataCount = 0;
            string name_ = ""; string code_ = ""; string city_ = ""; string country_ = ""; double lat_ = 0; double lng_ = 0;
            while (getline(lineRead, data, ',')) {
                switch (dataCount)
                {
                    case 1:
                        name_ = data.substr(1, data.length() - 2);
                        //std::cout << "NAME [" << name_ << "]" << std::endl;
                        break;
                    
                    case 2:
                        city_ = data.substr(1, data.length() - 2);
                        //std::cout << "CITY [" << city_ << "]" << std::endl;
                        break;

                    case 3:
                        country_ = data.substr(1, data.length() - 2);
                        //std::cout << "COUNTRY [" << country_ << "]" << std::endl;
                        break;

                    case 4:
                        code_ = data.substr(1, data.length() - 2);
                        //std::cout << "CODE [" << code_ << "]" << std::endl;
                        break;

                    case 6:
                        lat_ = std::stod(data);
                        //std::cout << "LAT [" << lat_ << "]" << std::endl;
                        break;

                    case 7:
                        lng_ = std::stod(data);
                        //std::cout << "LNG [" << lng_ << "]" << std::endl;
                        break;

                    case 0:
                        /** Open Flights Airport Code */
                        break;
                    
                    case 5:
                        /** 4 Letter ICAO Airport Code */
                        break;
                    
                    case 8:
                        /** Altitude */
                        break;
                    
                    case 9:
                        /** Timezone (Hours offset from UTC) */
                        break;
                    
                    case 10:
                        /** Daylight Savings Time */
                        break;
                    
                    case 11:
                        /** Timezone (tz format) */
                        break;
                    
                    case 12:
                        /** Port Type */
                        break;
                    
                    case 13:
                        /** Data Source */
                        break;
                    
                }
                
                dataCount++;
            }

            Vertex currAirport = Vertex();
            currAirport.name = name_; currAirport.code = code_; currAirport.city = city_; currAirport.country = country_;
            currAirport.lat = lat_; currAirport.lng = lng_;

            airports[code_] = currAirport;

            //std::cout << "ENTRY LINE END" << std::endl;
            //std::cout << std::endl;
        }
    } else {
        std::cout << "NO AIRPORT DATA" << std::endl;
    }
    airportFileReader.close();
}

void Graph::processRouteData(string routeFile)
{
    ifstream routeFileReader(routeFile);
    string routeLine;
    if (routeFileReader.is_open()) {
        while (getline(routeFileReader, routeLine)) {
            //std::cout << "ENTRY LINE START" << std::endl;
            //std::cout << std::endl;

            stringstream lineRead(routeLine);
            string data;
            int dataCount = 0;
            string sourceCode_ = ""; string destCode_ = ""; string airline_ = ""; double dist_ = 0;
            while (getline(lineRead, data, ',')) {
                switch (dataCount)
                {
                    case 2:
                        sourceCode_ = data;
                        //std::cout << "SOURCE [" << sourceCode_ << "]" << std::endl;
                        break;
                    
                    case 4:
                        destCode_ = data;
                        //std::cout << "DEST [" << destCode_ << "]" << std::endl;
                        break;

                    case 0:
                        airline_ = data;
                        //std::cout << "AIRLINE [" << airline_ << "]" << std::endl;
                        break;

                    case 1:
                        /** Open Flights Airline Code */
                        break;

                    case 3:
                        /** Open Flights Source Airport Code */
                        break;

                    case 5:
                        /** Open Flights Dest Airport Code */
                        break;

                    case 6:
                        /** Codeshare or Not */
                        break;
                    
                    case 7:
                        /** Number of Stops */
                        break;
                    
                    case 8:
                        /** Plane Types Used on Flight */
                        break;
                    
                }
                
                dataCount++;
            }

            /** NOTE: NEED TO CALC DIST AS A FUNCTION OF SOURCE (LAT, LNG) AND DEST (LAT, LNG) */
            Edge currEdge = Edge();
            currEdge.sourceCode = sourceCode_; currEdge.destCode = destCode_; currEdge.airline = airline_; 
            currEdge.dist = dist_;

            routes.emplace_back(currEdge);

            //std::cout << "ENTRY LINE END" << std::endl;
            //std::cout << std::endl;
        }
    } else {
        std::cout << "NO ROUTE DATA" << std::endl;
    }
    routeFileReader.close();
}

void Graph::printAirportData()
{
    for (std::pair<string, Vertex> curr : airports) {
        //std::cout << "----------AIRPORT ENTRY: " << curr.first << "----------" << std::endl;
        std::cout << std::endl;
        std::cout << "------------AIRPORT ENTRY------------" << std::endl;
        std::cout << std::endl;

        std::cout << "NAME [" << curr.second.name << "]" << std::endl;
        std::cout << "CITY [" << curr.second.city << "]" << std::endl;
        std::cout << "COUNTRY [" << curr.second.country << "]" << std::endl;
        std::cout << "CODE [" << curr.second.code << "]" << std::endl;
        std::cout << "LAT [" << curr.second.lat << "]" << std::endl;
        std::cout << "LNG [" << curr.second.lng << "]" << std::endl;

        std::cout << std::endl;
        std::cout << "----------END AIRPORT ENTRY----------" << std::endl;
        std::cout << std::endl;
    }
}

void Graph::printRouteData()
{
    for (Edge edge : routes) {
        //std::cout << "----------ROUTE ENTRY: " << edge.sourceCode << "----------" << std::endl;
        std::cout << std::endl;
        std::cout << "-------------ROUTE ENTRY-------------" << std::endl;
        std::cout << std::endl;

        std::cout << "SOURCE [" << edge.sourceCode << "]" << std::endl;
        std::cout << "DEST [" << edge.destCode << "]" << std::endl;
        std::cout << "AIRLINE [" << edge.airline << "]" << std::endl;
        std::cout << "DIST [" << edge.dist << "]" << std::endl;

        std::cout << std::endl;
        std::cout << "-----------END ROUTE ENTRY-----------" << std::endl;
        std::cout << std::endl;
    }
}

void Graph::buildGraph()
{

}

void Graph::copy(const Graph & other)
{

}

void Graph::clear()
{

}
