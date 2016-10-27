
#include "graph-extractor.hpp"

#include "cnpy.hpp"

#include "rose.h"


GraphExtractor::GraphExtractor(const std::vector<std::string> & args) : 
  project(frontend(args))
{}


GraphExtractor::~GraphExtractor() {
   delete project;
}

void GraphExtractor::stats(std::ostream & out) const {
  const std::vector<SgNode *> & nodes = getNodes();
  out << "nodes: " << nodes.size() << std::endl;

  const std::vector<std::pair<SgNode *, SgNode *> > & edges = getEdges();
  out << "edges: " << edges.size() << std::endl;
}

void GraphExtractor::toDOT(const std::string & output) const {
  // TODO
}

void GraphExtractor::toNPY(const std::string & output) const {
  // TODO
}

