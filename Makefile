
INCFLAGS=-I$(ROSEDIR)/include -I$(ROSEDIR)/include/rose -I$(BOOSTDIR)/include
LIBFLAGS=-L$(ROSEDIR)/lib -L$(BOOSTDIR)/lib # -Wl,-rpath
LIBS=-lrose # -lboost_filesystem

CXX=g++

all: graph-extractor

graph-extractor.o: graph-extractor.cpp graph-extractor.hpp
	$(CXX) $(INCFLAGS) -c graph-extractor.cpp -o graph-extractor.o

ast-graph-extractor.o: ast-graph-extractor.cpp graph-extractor.hpp
	$(CXX) $(INCFLAGS) -c ast-graph-extractor.cpp -o ast-graph-extractor.o

main.o: main.cpp graph-extractor.hpp
	$(CXX) $(INCFLAGS) -c main.cpp -o main.o

graph-extractor: graph-extractor.o ast-graph-extractor.o main.o
	libtool --mode=link $(CXX) $(LIBFLAGS) $(LIBS) main.o graph-extractor.o ast-graph-extractor.o -o graph-extractor

clean:
	rm -f graph-extractor.o ast-graph-extractor.o main.o graph-extractor

