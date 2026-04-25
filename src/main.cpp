#include "data.h"
#include <iostream>
#include <vector>

int main() {
    tickerData t;
    calculation calc(t);

    std::vector<double> closes = {100,102,101,103,105,104,106,108,110};

    std::cout << "RSI = " << calc.calRSIDaily(closes) << "\n";
    std::cout << "EMA = " << calc.calEMADaily(closes) << "\n";
}
