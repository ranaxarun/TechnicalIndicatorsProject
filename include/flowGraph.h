#pragma once
#include <tbb/flow_graph.h>


class flowGraph {
public:

    tbb::flow::graph g;
    tbb::flow::source_node<int> src
    tbb::flow::function_node<int, int> fn;
  
    flowGraph();
    void run(int input);
  
};
