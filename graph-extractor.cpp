
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
  const std::vector<SgNode *> & nodes = getNodes();
  const std::vector<std::pair<SgNode *, SgNode *> > & edges = getEdges();

  std::map<SgNode *, size_t> ntmap;
  {
    size_t n = nodes.size();
    size_t m = V_SgNumVariants;
    float * nodes_ = new float[n*m];
    for (int i = 0; i < n*m; i++)
      nodes_[i] = 0.;
    for (int i = 0; i < n; i++) {
      ntmap.insert(std::pair<SgNode *, size_t>(nodes[i],i));
      nodes_[i * m + nodes[i]->variantT()] += 1.;
    }

    std::ostringstream oss;
    oss << "node_" << output << ".npy";
    const unsigned int shape[] = { n , m };
    cnpy::npy_save(oss.str().c_str(), nodes_, shape, 2);

    delete nodes_;
  }
  {
    size_t n = edges.size();
    float * edges_ = new float[3*n];
    for (int i = 0; i < n; i++) {
      size_t src = ntmap[edges[i].first];
      size_t sink = ntmap[edges[i].second];
      edges_[        i] = (float)src;
      edges_[    n + i] = (float)sink;
      edges_[2 * n + i] = 1.;
    }

    std::ostringstream oss;
    oss << "edge_" << output << ".npy";
    const unsigned int shape[] = { 3 , n };
    cnpy::npy_save(oss.str().c_str(), edges_, shape, 2);
    delete edges_; 
  }
}

