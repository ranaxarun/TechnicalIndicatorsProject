#include "data.h"
#include<iostream>
#include<string>

//tickerData::tickerData(){}

tickerData:: tickerData(std::string id,std::string period,double open,double close,double low, double high):
    id(id),period(period),open(open),close(close),low(low),high(high){}

//calculation::calculation(){}

calculation::calculation(tickerData &stockInfo):ticker(stockInfo)
{
}

double calculation::calRSIDaily(tickerData &stockInfo)
{
 std::cout<<"RSI logic to be added";
 return 0.0 ;// this will change after the logic
}

double calculation::calEMADaily(tickerData &stockInfo)
{
   std::cout<<"EMA logic to be added";
    return 0.0 ;// this will change after the logic
}
