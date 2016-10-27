
#include "graph-extractor.hpp"

#include <iostream>

#include <cassert>

int main(int argc, char * argv[]) {
  std::vector<std::string> args;
  args.push_back(argv[0]);

  std::string kgraph("");
  std::string output("");

  for (int i = 1; i < argc; i++) {
    std::string arg(argv[i]);
    if (arg.substr(0,8) == "--graph=") {
      kgraph = arg.substr(8);
    }
    else if (arg.substr(0,9) == "--output=") {
      output = arg.substr(9);
    }
    else
      args.push_back(arg);
  }

  GraphExtractor * graph = NULL;

  if (kgraph == "ast")
    graph = new AstGraphExtractor(args);
  else
    assert(false);

  graph->extract();

  graph->stats(std::cout);

  graph->toNPY(output);
  graph->toDOT(output);

  delete graph;

  return 0;
}

