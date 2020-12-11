Weekly Summary
==============

11/15 - 11/22
-------------
This week, we met intially to discuss high-level goals for our project. First, we discussed our project contract, deciding upon meeting times, how we wanted to split up work, etc. We formally typed this up in our team contract which every member in the group confirmed and agreed to. Next, we focused on our project goals. We decided to use the airport dataset and decided on which traversal method and algorithms we wanted to use. After doing a bit of research about the data set and some possible implementations, we typed up a high level project outline in our project goals document. Then, during the week we started some of the initial set up for our code. Ani created the framework for our graph class which will hold the airport/flight network. He also processed the airport and flight route data for use in the graph implementation.

11/22 - 11/29
-------------
At our last meeting, we made some design choices regarding weights for graph edges and what information to include in vertices and edges. We decided to include name, codes, city, country, lat, and lng in vertices and for edges source and dest codes, airline code, the calculated distance between two vertices, and the number of stops. We also decided to implement vertex connection as an adjacency list that each vertex holds internally. Ani implemented the graph structure as well as different helper functions for internal and external use and did some preliminary testing of the code base so far. BFS and our two pathing algorithms remain to be implemented.

11/29 - 12/05
-------------
This week, we completed two pathing algorithms. Tara did the BFS algorithm, and Jacob did Dijkstra's algorithm along with Ani. Light testing was done on these, so we plan to add a greater number of tests by next week, as well as tests that go over more complex flight routes. Tara will also be doing the landmark algorithm, which is the final method that we ned to complete for the project. As a side note, we met with our project coordinator this week.  

12/05 - 12/11
-------------
This week, we finished up some final revisions to the landmark path and graph structure. We implemented Catch Testing for each of the main componenets. Ani wrote testing for the graph stucture. Tara wrote testing for dijsktra's algorithm and landmark path algorithm. Jacob implemented testing for the Breadth First Search Traversal. We fixed all bugs that came up in this testing. Additionally we created and recorded our final presentation, wrote our final report, and wrote the read me for our code. We pushed final versions of all the code and tested it on a fresh EWS machine.