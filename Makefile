
####

CPPFLAGS=-I$(ROSEDIR)/include -I$(ROSEDIR)/include/rose -I$(BOOSTDIR)/include
LDFLAGS=-L$(ROSEDIR)/lib -L$(BOOSTDIR)/lib

LIBS=-lrose

CXX=g++
CXXFLAGS=

#### Build

all: graph-extractor

cnpy.o: cnpy.cpp cnpy.hpp
	$(CXX) $(CXXFLAGS) -c cnpy.cpp -o cnpy.o

graph-extractor.o: graph-extractor.cpp graph-extractor.hpp cnpy.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c graph-extractor.cpp -o graph-extractor.o

ast-graph-extractor.o: ast-graph-extractor.cpp graph-extractor.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c ast-graph-extractor.cpp -o ast-graph-extractor.o

main.o: main.cpp graph-extractor.hpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c main.cpp -o main.o

graph-extractor: graph-extractor.o ast-graph-extractor.o main.o cnpy.o
	libtool --mode=link $(CXX) $(LDFLAGS) $(LIBS) main.o graph-extractor.o ast-graph-extractor.o cnpy.o -o graph-extractor


#### Test

test_0.npy: graph-extractor
	./graph-extractor --graph=ast --format=npy --output=test_0 $(ROSESRC)/tests/nonsmoke/functional/CompileTests/C_tests/test2016_01.c

check: test_0.npy

#### Clean

clean:
	rm -f graph-extractor.o ast-graph-extractor.o main.o cnpy.o graph-extractor
	rm -f *.npy

####

