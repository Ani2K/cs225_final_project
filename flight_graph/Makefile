EXENAME = graph
OBJS = graph.o main.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: main.cpp graph.h graph.cpp
	$(CXX) $(CXXFLAGS) main.cpp

graph.o : graph.h graph.cpp
	$(CXX) $(CXXFLAGS) graph.cpp
	
test: output_msg catch/catchmain.cpp tests/test_graph.cpp tests/test_bfs.cpp tests/test_dstra.cpp tests/test_landmark.cpp graph.cpp
	$(LD) catch/catchmain.cpp tests/test_graph.cpp tests/test_bfs.cpp tests/test_dstra.cpp tests/test_landmark.cpp graph.cpp $(LDFLAGS) -o test

test_graph: output_msg catch/catchmain.cpp tests/test_graph.cpp graph.cpp
	$(LD) catch/catchmain.cpp tests/test_graph.cpp graph.cpp $(LDFLAGS) -o test

test_bfs: output_msg catch/catchmain.cpp tests/test_bfs.cpp graph.cpp
	$(LD) catch/catchmain.cpp tests/test_bfs.cpp graph.cpp $(LDFLAGS) -o test

test_dstra: output_msg catch/catchmain.cpp tests/test_dstra.cpp graph.cpp
	$(LD) catch/catchmain.cpp tests/test_dstra.cpp graph.cpp $(LDFLAGS) -o test

test_landmark: output_msg catch/catchmain.cpp tests/test_landmark.cpp graph.cpp
	$(LD) catch/catchmain.cpp tests/test_landmark.cpp graph.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test
