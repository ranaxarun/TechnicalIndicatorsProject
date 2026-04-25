
#include "flowGraph.h"


flowGraph::flowGraph(tbb::flow::graph g ): 
                                        g(g), 
                                        src(g,[]()->std::map<int,std::string>{ return map },false),
                                        fn(g, )

{
  
}
