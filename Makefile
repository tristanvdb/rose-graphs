
####

INCFLAGS=-I$(ROSEDIR)/include -I$(ROSEDIR)/include/rose -I$(BOOSTDIR)/include
LIBFLAGS=-L$(ROSEDIR)/lib -L$(BOOSTDIR)/lib
LIBS=-lrose

CXX=g++

#### Build

all: graph-extractor

graph-extractor.o: graph-extractor.cpp graph-extractor.hpp
	$(CXX) $(INCFLAGS) -c graph-extractor.cpp -o graph-extractor.o

ast-graph-extractor.o: ast-graph-extractor.cpp graph-extractor.hpp
	$(CXX) $(INCFLAGS) -c ast-graph-extractor.cpp -o ast-graph-extractor.o

main.o: main.cpp graph-extractor.hpp
	$(CXX) $(INCFLAGS) -c main.cpp -o main.o

graph-extractor: graph-extractor.o ast-graph-extractor.o main.o
	libtool --mode=link $(CXX) $(LIBFLAGS) $(LIBS) main.o graph-extractor.o ast-graph-extractor.o -o graph-extractor


#### Test

test_0.npy: graph-extractor
	./graph-extractor --graph=ast --format=npy --output=test_0 $(ROSESRC)/tests/nonsmoke/functional/CompileTests/C_tests/test2016_01.c

check: test_0.npy

#### Clean

clean:
	rm -f graph-extractor.o ast-graph-extractor.o main.o graph-extractor

####

