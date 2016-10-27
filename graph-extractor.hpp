
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
};

class AstGraphExtractor : public GraphExtractor {
  protected:
    std::vector<SgNode *> p_nodes;
    std::map<SgNode *, SgNode *> p_struct_edges;

  public:
    AstGraphExtractor(const std::vector<std::string> & args);
    virtual void extract();
};

