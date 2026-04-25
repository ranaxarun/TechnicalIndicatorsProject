#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

struct tickerData {
    std::string id;
    std::string period;
    double open;
    double close;
    double low;
    double high;

    tickerData();
};

class calculation {
public:
    tickerData &ticker;

    calculation(tickerData &);
    
    double calRSIDaily(const std::vector<double> &closes, int period = 14);
    double calEMADaily(const std::vector<double> &closes, int period = 14);
};

#endif
