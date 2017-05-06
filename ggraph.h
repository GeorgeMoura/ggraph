#include <list>
#include <iostream>
#include <vector>
#include <limits.h>

typedef std::vector<std::list<std::pair<int,int> > > vlp;
typedef std::vector<std::vector<int> > vv;

class ggraph
{
  private:
    int V;
    vlp adj_list;
    vv adj_matrix;
    char storage_type;
    bool allocate_matrix(int);
    bool allocate_list(int);

  public:
  	ggraph();
  	ggraph(int);
  	ggraph(int, char);
    void set_graph_len(int);
    int len();
    void set_storage(char);
    void print();
    void add_edge(int, int, int);
    void add_node();
    void complete_und_unw();
};

