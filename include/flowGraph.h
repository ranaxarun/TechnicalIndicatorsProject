#pragma once
#include <tbb/flow_graph.h>

using namespace tbb::flow;

class flowGraph {
public:
    tbb::flow::source_node<int> src
    tbb::flow::graph g;
    tbb::flow::buffer_node<int>        buf;
    tbb::flow::function_node<int, int> fn;
  

    Processor();
    void run(int input);
    void regfunction(function_node<int, int>& node, int val);
};
