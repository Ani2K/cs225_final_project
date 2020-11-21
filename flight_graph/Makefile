EXENAME = graph
OBJS = main.o graph.o

CXX = clang++
CXXFLAGS = -std=c++0x -c -g -O0 -Wall -Wextra
LD = clang++
LDFLAGS = -std=c++0x

all: $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp graph.h graph.cpp
	$(CXX) $(CXXFLAGS) main.cpp

graph.o : graph.h graph.cpp
	$(CXX) $(CXXFLAGS) graph.cpp

clean:
	-rm -f *.o $(EXENAME)
