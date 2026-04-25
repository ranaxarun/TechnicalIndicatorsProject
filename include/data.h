#ifndef DATA_H
#define DATA_H

#include <string>

struct tickerData {
    std::string id;
    std::string period;
    double open;
    double close;
    double low;
    double high;
};

class calculation{
    public:
    tickerData ticker;
    double calRSIDaily(ticker&); 
    double calEMADaily(ticker&); 
};
  
#endif
