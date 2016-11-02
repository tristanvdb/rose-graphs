
#include "graph-extractor.hpp"
#include "rose.h"

struct AstGraphExtractorTraversal : public  AstBottomUpProcessing<SgNode *> {
  std::vector<SgNode *> & p_nodes;
  std::vector<std::pair<SgNode *, SgNode *> > & p_edges;

  AstGraphExtractorTraversal(std::vector<SgNode *> & nodes, std::vector<std::pair<SgNode *, SgNode *> > & edges) :
    p_nodes(nodes),
    p_edges(edges)
  {}

  virtual SgNode * evaluateSynthesizedAttribute(SgNode * node, SynthesizedAttributesList synth_attrs) {
    p_nodes.push_back(node);
    for (SynthesizedAttributesList::iterator it = synth_attrs.begin(); it != synth_attrs.end(); it++) {
      p_edges.push_back(std::pair<SgNode *, SgNode *>(*it, node));
    }
    return node;
  }
};

AstGraphExtractor::AstGraphExtractor(const std::vector<std::string> & args) :
  GraphExtractor(args)
{
  p_edges.push_back(std::pair<std::string, std::vector<std::pair<SgNode *, SgNode *> > >("ast", std::vector<std::pair<SgNode *, SgNode *> >()));
  p_edges.push_back(std::pair<std::string, std::vector<std::pair<SgNode *, SgNode *> > >("symbol", std::vector<std::pair<SgNode *, SgNode *> >()));
}

void AstGraphExtractor::extract() {
  AstGraphExtractorTraversal traversal(p_nodes, p_edges[0].second);
  traversal.traverse(project);

  std::vector<SgNode *>::iterator it_node;
  for (it_node = p_nodes.begin(); it_node != p_nodes.end(); it_node++) {
    SgVarRefExp * varref = isSgVarRefExp(*it_node);
    if (varref != NULL) {
      SgInitializedName * initname = isSgInitializedName(varref->get_symbol()->get_declaration());
      assert(initname != NULL);
      p_edges[1].second.push_back(std::pair<SgNode *, SgNode *>(initname, varref));
    }
    SgFunctionRefExp * fncref = isSgFunctionRefExp(*it_node);
    if (fncref != NULL) {
      SgFunctionDeclaration * fncdecl = isSgFunctionDeclaration(fncref->get_symbol_i()->get_declaration());
      assert(fncdecl != NULL);
      p_edges[1].second.push_back(std::pair<SgNode *, SgNode *>(fncdecl, fncref));
    }
  }
}

