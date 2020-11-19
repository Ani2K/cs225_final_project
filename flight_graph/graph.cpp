#include <vector>
#include <string>
#include <map>
#include "graph.h"

using std::vector;
using std::string;
using std::map;

Graph::Graph(string fileName)
{

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
}

vector<Graph::Vertex> Graph::bfs()
{

}

vector<Graph::Vertex> Graph::dstra(Vertex start, Vertex end)
{

}

vector<Graph::Vertex> Graph::landmark(Vertex start, Vertex mid, Vertex end)
{

}

void Graph::processData(string aiportFile, string flightFile)
{
    
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
