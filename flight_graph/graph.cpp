#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "graph.h"

using std::vector;
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
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

            stringstream lineRead(airportLine);
            string data;
            int code_ = -1; string name_ = "EMPTY"; string city_ = "EMPTY"; string city2_ = "EMPTY"; string country_ = "EMPTY"; 
            string code_iata_ = "EMPTY"; string code_icao_ = "EMPTY"; long double lat_ = -1; long double lng_ = -1;
            
            vector<string> entries;
            while (getline(lineRead, data, ',')) {
                entries.push_back(data);
            }

            int size = entries.size();
            bool anomalyEntry = false;
            for (int i = 0; i < size; i++) {
                data = entries[i];
                data.erase(remove(data.begin(), data.end(), '"'), data.end());
                
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

                switch (i)
                {
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

            if (code_iata_.length() == 3) {
                airportDict[code_iata_] = code_;
            } else {
                code_iata_ = "EMPTY";
            }
            if (code_icao_.length() == 4) {
                airportDict[code_icao_] = code_;
            } else {
                code_icao_ = "EMPTY";
            }

            Vertex currAirport = Vertex();
            currAirport.code = code_; currAirport.name = name_; currAirport.city = city_; currAirport.city2 = city2_; 
            currAirport.country = country_; currAirport.code_iata = code_iata_; currAirport.code_icao = code_icao_;
            currAirport.lat = lat_; currAirport.lng = lng_;

            airports[code_] = currAirport;
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

            stringstream lineRead(routeLine);
            string data;
            int dataCount = 0;
            string airline_ = "EMPTY"; string sourceCode_letter_ = "EMPTY"; int sourceCode_ = -1; 
            string destCode_letter_ = "EMPTY"; int destCode_ = -1; long double dist_ = -2;
            
            while (getline(lineRead, data, ',')) {
                switch (dataCount)
                {
                    data.erase(remove(data.begin(), data.end(), '"'), data.end());
                    data.erase(remove(data.begin(), data.end(), ' '), data.end());
                    case 0:
                        /** 2 Letter IATA or 3 Letter ICAO Airline Code */
                        airline_ = data;
                        break;

                    case 1:
                        /** Open Flights Airline Code */
                        break;

                    case 2:
                        /** 3 Letter IATA or 4 Letter ICAO Source Airport Code */
                        sourceCode_letter_ = data;
                        break;

                    case 3:
                        /** Open Flights Source Airport Code */
                        try
                        {
                            sourceCode_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            map<string, int>::iterator lookup = airportDict.find(sourceCode_letter_);
                            if (lookup != airportDict.end()) {
                                sourceCode_ = lookup->second;
                            }
                        }
                        break;
                    
                    case 4:
                        /** 3 Letter IATA or 4 Letter ICAO Dest Airport Code */
                        destCode_letter_ = data;
                        break;

                    case 5:
                        /** Open Flights Dest Airport Code */
                        try
                        {
                            destCode_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            map<string, int>::iterator lookup = airportDict.find(destCode_letter_);
                            if (lookup != airportDict.end()) {
                                destCode_ = lookup->second;
                            }
                        }
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
            currEdge.airline = airline_; currEdge.sourceCode_letter = sourceCode_letter_; currEdge.sourceCode = sourceCode_; 
            currEdge.destCode_letter = destCode_letter_; currEdge.destCode = destCode_; currEdge.dist = dist_;

            routes.emplace_back(currEdge);
        }
    } else {
        std::cout << "NO ROUTE DATA" << std::endl;
    }
    routeFileReader.close();
}

void Graph::printAirportData()
{
    for (std::pair<int, Vertex> curr : airports) {
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

void Graph::printRouteData()
{
    for (Edge edge : routes) {
        std::cout << std::endl;
        std::cout << "-------------ROUTE ENTRY-------------" << std::endl;
        std::cout << std::endl;

        std::cout << "AIRLINE [" << edge.airline << "]" << std::endl;
        std::cout << "SOURCE CODE LETTER [" << edge.sourceCode_letter << "]" << std::endl;
        std::cout << "SOURCE CODE [" << edge.sourceCode << "]" << std::endl;
        std::cout << "DEST CODE LETTER [" << edge.destCode_letter << "]" << std::endl;
        std::cout << "DEST CODE [" << edge.destCode << "]" << std::endl;
        std::cout << "DIST [" << edge.dist << "]" << std::endl;

        std::cout << std::endl;
        std::cout << "-----------END ROUTE ENTRY-----------" << std::endl;
        std::cout << std::endl;
    }
}

void Graph::writeAirportData(string outputFile)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);
    for (std::pair<int, Vertex> curr : airports) {
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

void Graph::writeRouteData(string outputFile)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);
    for (Edge edge : routes) {
        fileWriter << std::endl;
        fileWriter << "-------------ROUTE ENTRY-------------" << std::endl;
        fileWriter << std::endl;

        fileWriter << "AIRLINE [" << edge.airline << "]" << std::endl;
        fileWriter << "SOURCE CODE LETTER [" << edge.sourceCode_letter << "]" << std::endl;
        fileWriter << "SOURCE CODE [" << edge.sourceCode << "]" << std::endl;
        fileWriter << "DEST CODE LETTER [" << edge.destCode_letter << "]" << std::endl;
        fileWriter << "DEST CODE [" << edge.destCode << "]" << std::endl;
        fileWriter << "DIST [" << edge.dist << "]" << std::endl;

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
