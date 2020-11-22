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
            int dataCount = 0;
            string name_ = ""; int code_ = 0; string city_ = ""; string country_ = ""; double lat_ = 0; double lng_ = 0;
            string code_iata = ""; string code_icao = "";
            while (getline(lineRead, data, ',')) {
                switch (dataCount)
                {
                    case 1:
                        /** Airport Name */
                        //name_ = data.substr(1, data.length() - 2);
                        name_ = data;
                        name_.erase(remove(name_.begin(), name_.end(), '"'), name_.end());
                        //name_.erase(remove(name_.begin(), name_.end(), ' '), name_.end());
                        name_.erase(0, name_.find_first_not_of(' '));
                        name_.erase(name_.find_last_not_of(' ') + 1);
                        break;
                    
                    case 2:
                        /** City */
                        //city_ = data.substr(1, data.length() - 2);
                        city_ = data;
                        city_.erase(remove(city_.begin(), city_.end(), '"'), city_.end());
                        //city_.erase(remove(city_.begin(), city_.end(), ' '), city_.end());
                        city_.erase(0, city_.find_first_not_of(' '));
                        city_.erase(city_.find_last_not_of(' ') + 1);
                        break;

                    case 3:
                        /** Country */
                        //country_ = data.substr(1, data.length() - 2);
                        country_ = data;
                        country_.erase(remove(country_.begin(), country_.end(), '"'), country_.end());
                        //country_.erase(remove(country_.begin(), country_.end(), ' '), country_.end());
                        country_.erase(0, country_.find_first_not_of(' '));
                        country_.erase(country_.find_last_not_of(' ') + 1);
                        break;

                    case 0:
                        /** Open Flights Airport Code */
                        try
                        {
                            code_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            //std::cout << "INVALID ARG WITH CODE [" << data << "]" << std::endl;
                            //std::cerr << e.what() << '\n';
                        }
                        break;

                    case 6:
                        /** Latitude */
                        try
                        {
                            lat_ = std::stod(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            //std::cout << "INVALID ARG WITH LAT [" << data << "]" << std::endl;
                            //std::cerr << e.what() << '\n';
                        }
                        break;

                    case 7:
                        /** Longitude */
                        try
                        {
                            lng_ = std::stod(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            //std::cout << "INVALID ARG WITH LNG [" << data << "]" << std::endl;
                            //std::cerr << e.what() << '\n';
                        }
                        break;

                    case 4:
                        /** 3 Letter IATA Airport Code */
                        //code_iata = data.substr(1, data.length() - 2);
                        code_iata = data;
                        code_iata.erase(remove(code_iata.begin(), code_iata.end(), '"'), code_iata.end());
                        code_iata.erase(remove(code_iata.begin(), code_iata.end(), ' '), code_iata.end());
                        break;
                    
                    case 5:
                        /** 4 Letter ICAO Airport Code */
                        //code_icao = data.substr(1, data.length() - 2);
                        code_icao = data;
                        code_icao.erase(remove(code_icao.begin(), code_icao.end(), '"'), code_icao.end());
                        code_icao.erase(remove(code_icao.begin(), code_icao.end(), ' '), code_icao.end());
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
            if (code_iata.length() == 3) {
                airportDict[code_iata] = code_;
            } else if (code_icao.length() == 4) {
                airportDict[code_icao] = code_;
            }
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
            int sourceCode_ = -1; int destCode_ = -1; string airline_ = ""; double dist_ = 0;
            string sourceCodeStr = ""; string destCodeStr = "";
            bool sourceCodeFound = false;
            bool destCodeFound = false;
            while (getline(lineRead, data, ',')) {
                switch (dataCount)
                {
                    case 3:
                        /** Open Flights Source Airport Code */
                        try
                        {
                            sourceCodeFound = true;
                            sourceCode_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            sourceCodeFound = false;
                            //std::cout << "INVALID ARG WITH SOURCE CODE [" << data << "]" << std::endl;
                            //std::cerr << e.what() << '\n';
                        }
                        break;
                    
                    case 5:
                        /** Open Flights Dest Airport Code */
                        try
                        {
                            destCodeFound = true;
                            destCode_ = std::stoi(data);
                        }
                        catch(const std::invalid_argument& e)
                        {
                            destCodeFound = false;
                            //std::cout << "INVALID ARG WITH DEST CODE [" << data << "]" << std::endl;
                            //std::cerr << e.what() << '\n';
                        }
                        break;

                    case 0:
                        /** 2 Letter IATA or 3 Letter ICAO Airline Code */
                        airline_ = data;
                        airline_.erase(remove(airline_.begin(), airline_.end(), '"'), airline_.end());
                        airline_.erase(remove(airline_.begin(), airline_.end(), ' '), airline_.end());
                        break;

                    case 1:
                        /** Open Flights Airline Code */
                        break;

                    case 2:
                        /** 3 Letter IATA or 4 Letter ICAO Source Airport Code */
                        sourceCodeStr = data;
                        sourceCodeStr.erase(remove(sourceCodeStr.begin(), sourceCodeStr.end(), '"'), sourceCodeStr.end());
                        sourceCodeStr.erase(remove(sourceCodeStr.begin(), sourceCodeStr.end(), ' '), sourceCodeStr.end());
                        break;

                    case 4:
                        /** 3 Letter IATA or 4 Letter ICAO Dest Airport Code */
                        destCodeStr = data;
                        destCodeStr.erase(remove(destCodeStr.begin(), destCodeStr.end(), '"'), destCodeStr.end());
                        destCodeStr.erase(remove(destCodeStr.begin(), destCodeStr.end(), ' '), destCodeStr.end());
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
            
            if (!sourceCodeFound) {
                map<string, int>::iterator lookup = airportDict.find(sourceCodeStr);
                if (lookup != airportDict.end()) {
                    sourceCode_ = lookup->second;
                    sourceCodeFound = true;
                }
            }
            if (!destCodeFound) {
                map<string, int>::iterator lookup = airportDict.find(destCodeStr);
                if (lookup != airportDict.end()) {
                    destCode_ = lookup->second;
                    destCodeFound = true;
                }
            }

            /** NOTE: NEED TO CALC DIST AS A FUNCTION OF SOURCE (LAT, LNG) AND DEST (LAT, LNG) */
            Edge currEdge = Edge();
            currEdge.sourceCode = sourceCode_; currEdge.destCode = destCode_; currEdge.airline = airline_; 
            currEdge.dist = dist_;

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

void Graph::writeAirportData(string outputFile)
{
    ofstream fileWriter;
    fileWriter.open(outputFile);
    for (std::pair<int, Vertex> curr : airports) {
        //std::cout << "----------AIRPORT ENTRY: " << curr.first << "----------" << std::endl;
        fileWriter << std::endl;
        fileWriter << "------------AIRPORT ENTRY------------" << std::endl;
        fileWriter << std::endl;

        fileWriter << "NAME [" << curr.second.name << "]" << std::endl;
        fileWriter << "CITY [" << curr.second.city << "]" << std::endl;
        fileWriter << "COUNTRY [" << curr.second.country << "]" << std::endl;
        fileWriter << "CODE [" << curr.second.code << "]" << std::endl;
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
        //std::cout << "----------ROUTE ENTRY: " << edge.sourceCode << "----------" << std::endl;
        fileWriter << std::endl;
        fileWriter << "-------------ROUTE ENTRY-------------" << std::endl;
        fileWriter << std::endl;

        fileWriter << "SOURCE [" << edge.sourceCode << "]" << std::endl;
        fileWriter << "DEST [" << edge.destCode << "]" << std::endl;
        fileWriter << "AIRLINE [" << edge.airline << "]" << std::endl;
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
