#include <iostream>
#include "data.h"

int main()
{
    tickerData data ("1","14",12,78,87,65);
    
    calculation c (data);
    
    std::cout<<"Hello World";

    return 0;
}
