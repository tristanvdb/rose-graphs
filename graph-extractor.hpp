
#include <map>
#include <vector>
#include <string>
#include <iostream>

class SgNode;
class SgProject;

class GraphExtractor {
  protected:
    SgProject * project;

  public:
    GraphExtractor(const std::vector<std::string> & args);
    virtual ~GraphExtractor();

    virtual void extract() = 0;

    void stats(std::ostream & out) const;
    void toNPY(const std::string & output) const;
    void toDOT(const std::string & output) const;

  protected:
    virtual const std::vector<SgNode *> & getNodes() const = 0;
    virtual const std::vector<std::pair<SgNode *, SgNode *> > & getEdges() const = 0;
};

class AstGraphExtractor : public GraphExtractor {
  public:
    typedef enum {
      structure,
      type,
      symbol
    } EdgeRelationKind;

  protected:
    std::vector<SgNode *> p_nodes;
    std::vector<std::pair<SgNode *, SgNode *> > p_struct_edges;

  public:
    AstGraphExtractor(const std::vector<std::string> & args);
    virtual void extract();

  protected:
    virtual const std::vector<SgNode *> & getNodes() const;
    virtual const std::vector<std::pair<SgNode *, SgNode *> > & getEdges() const;
};

