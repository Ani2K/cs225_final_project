# asa8-jacobdr4-taraad2
Final Project

Running

  -Pulling repo to an ews directory
  -Navigate to flight_graph directory  
  -Can compile general code in main.cpp using “make” which is then run using “./graph”  
  -Can compile test cases using either “make test” (all tests), “make test_graph”, “make test_bfs”, “make test_dstra”, “make test_landmark” which are run using “./test”  
  
Functionality

  -Can construct a empty graph structure using Graph() or processed graph structure using Graph("data/airports_text_short.txt", "data/routes.dat")  
  -There are get, add, and remove methods for vertices and edges using a variety of inputs (see graph.h  
  -Can run a breadth first search traversal given a starting node using bfs(Vertex start). This will traverse all nodes in that connected portion of the graph.  
  -Can find the shortest path between two airports using dstra(Vertex start, Vertex end) 
  -Can find the shortest path between two airports through a third midpoint air


