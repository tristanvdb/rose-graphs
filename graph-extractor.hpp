
#include <vector>
#include <string>
#include <iostream>

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
  public:
    AstGraphExtractor(const std::vector<std::string> & args);
    virtual void extract();
};

