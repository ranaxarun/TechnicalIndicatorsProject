#ifndef DATA_H
#define DATA_H

#include <string>


struct ticker {
    std::string id;
    std::string period;
    double open;
    double close;
    double low;
    double high;

   
    double calRSIDaily(); 
    double calEMADaily(); 
};

#endif
