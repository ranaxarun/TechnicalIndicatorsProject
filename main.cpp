#include "data.h"
#include <vector>
#include <iostream>

int main() {
    tickerData t;
    calculation calc(t);

    std::vector<double> closes = {100,102,101,103,105,104,106,108,110};

    double rsi = calc.calRSIDaily(closes);
    double ema = calc.calEMADaily(closes);

    std::cout << "RSI = " << rsi << "\n";
    std::cout << "EMA = " << ema << "\n";
}
