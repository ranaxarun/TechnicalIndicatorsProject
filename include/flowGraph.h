#pragma once
#include <tbb/flow_graph.h>


class flowGraph {
public:

    tbb::flow::graph g;
    tbb::flow::source_node<std::map<int,std::string>> src
    tbb::flow::function_node<std::map<int,std::string>, int> fn;
  
    flowGraph();
    void run(int input);
  
};
