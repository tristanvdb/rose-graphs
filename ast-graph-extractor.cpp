
#include "graph-extractor.hpp"
#include "rose.h"

struct AstGraphExtractorTraversal : public  AstBottomUpProcessing<SgNode *> {
  std::vector<SgNode *> & p_nodes;
  std::vector<std::pair<SgNode *, SgNode *> > & p_struct_edges;

  AstGraphExtractorTraversal(std::vector<SgNode *> & nodes, std::vector<std::pair<SgNode *, SgNode *> > & struct_edges) :
    p_nodes(nodes),
    p_struct_edges(struct_edges)
  {}

  virtual SgNode * evaluateSynthesizedAttribute(SgNode * node, SynthesizedAttributesList synth_attrs) {
    p_nodes.push_back(node);
    for (SynthesizedAttributesList::iterator it = synth_attrs.begin(); it != synth_attrs.end(); it++) {
      p_struct_edges.push_back(std::pair<SgNode *, SgNode *>(*it, node));
    }
    return node;
  }
};

AstGraphExtractor::AstGraphExtractor(const std::vector<std::string> & args) :
  GraphExtractor(args),
  p_nodes(),
  p_struct_edges()
{}

void AstGraphExtractor::extract() {
  AstGraphExtractorTraversal traversal(p_nodes, p_struct_edges);
  traversal.traverse(project);
}

const std::vector<SgNode *> & AstGraphExtractor::getNodes() const { return p_nodes; }

const std::vector<std::pair<SgNode *, SgNode *> > & AstGraphExtractor::getEdges() const { return p_struct_edges; }

