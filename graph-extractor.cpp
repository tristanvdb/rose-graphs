
#include "graph-extractor.hpp"

#include "cnpy.hpp"

#include "rose.h"


GraphExtractor::GraphExtractor(const std::vector<std::string> & args) : 
  project(frontend(args)),
  p_nodes(),
  p_edges()
{}


GraphExtractor::~GraphExtractor() {
   delete project;
}

void GraphExtractor::stats(std::ostream & out) const {
  out << "nodes: " << p_nodes.size() << std::endl;

  for (int i = 0; i < p_edges.size(); i++)
    out << p_edges[i].first << ": " << p_edges[i].second.size() << std::endl;
}

void GraphExtractor::toDOT(const std::string & output) const {
  // TODO
}

void save_nodes(
  const std::string & output,
  const std::vector<SgNode *> & nodes,
  std::map<SgNode *, size_t> & ntmap
) {
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
  oss << output << "nodes.npy";
  const unsigned int shape[] = { n , m };
  cnpy::npy_save(oss.str().c_str(), nodes_, shape, 2);

  delete nodes_;
}

void save_edges(
  const std::string & output,
  const std::vector<std::pair<SgNode *, SgNode *> > & edges,
  const std::map<SgNode *, size_t> & ntmap,
  const std::string & suffix
) {
  size_t n = edges.size();
  float * edges_ = new float[3*n];
  for (int i = 0; i < n; i++) {
//  std::cout << "edge " << suffix << " " << i << std::endl;
//  std::cout << "  " << edges[i].first << std::endl;
//  std::cout << "  " << edges[i].second << std::endl;
    size_t src = ntmap.at(edges[i].first);
    size_t sink = ntmap.at(edges[i].second);
    edges_[        i] = (float)src;
    edges_[    n + i] = (float)sink;
    edges_[2 * n + i] = 1.;
  }

  std::ostringstream oss;
  oss << output << "edges_" << suffix << ".npy";
  const unsigned int shape[] = { 3 , n };
  cnpy::npy_save(oss.str().c_str(), edges_, shape, 2);
  delete edges_; 
}

void GraphExtractor::toNPY(const std::string & output) const {
  std::map<SgNode *, size_t> ntmap;
  save_nodes(output, p_nodes, ntmap);

  for (int i = 0; i < p_edges.size(); i++)
    save_edges(output, p_edges[i].second, ntmap, p_edges[i].first);
}

