/* Copyright (C) 2025 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "TestCppClient.h"
#include "EReader.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <memory>

int main(int argc, char** argv) {
    std::cout << "Simple IBKR Historical Data Client" << std::endl;
    std::cout << "Make sure TWS/IB Gateway is running with API enabled" << std::endl;
    std::cout << "====================================================\n" << std::endl;
    
    TestCppClient client;
    
    // Connect to TWS paper trading
    const char* host = "127.0.0.1";
    int port = 4002;  // TWS paper trading port
    int clientId = 999;
    
    if (client.connect(host, port, clientId)) {
        std::cout << "\nConnected successfully! Waiting for historical data..." << std::endl;
        
        // Create and start the EReader
        std::shared_ptr<EReader> reader = std::make_shared<EReader>(client.getClient(), &client.getSignal());
        reader->start();
        
        std::cout << "Will disconnect automatically when data is received.\n" << std::endl;
        
        // Wait for data with timeout
        int timeout = 0;
        const int MAX_TIMEOUT = 30;
        
        while (client.isConnected() && timeout < MAX_TIMEOUT && !client.isHistoricalDataCompleted()) {
            // Process messages
            client.getSignal().waitForSignal();
            reader->processMsgs();
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
            timeout++;
            
            if (timeout % 5 == 0) {
                std::cout << "Still waiting for data... (" << timeout << " seconds)" << std::endl;
            }
        }
        
        if (client.isHistoricalDataCompleted()) {
            std::cout << "\n✅ Data received successfully! Disconnecting..." << std::endl;
            // Small delay to ensure all messages are processed
            std::this_thread::sleep_for(std::chrono::seconds(1));
            client.disconnect();
        }
        else if (timeout >= MAX_TIMEOUT) {
            std::cout << "\n⚠️  Timeout after " << MAX_TIMEOUT << " seconds. No data received." << std::endl;
            std::cout << "This usually means:" << std::endl;
            std::cout << "1. No market data permissions in your paper account" << std::endl;
            std::cout << "2. Check TWS for any error messages" << std::endl;
            std::cout << "3. Make sure you're using the correct port (4002 for paper)" << std::endl;
            client.disconnect();
        }
    }
    
    std::cout << "Program ended." << std::endl;
    return 0;
}
