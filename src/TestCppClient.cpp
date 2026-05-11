/* Copyright (C) 2025 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "TestCppClient.h"

#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <atomic>

TestCppClient::TestCppClient() : m_osSignal(2000), m_pClient(new EClientSocket(this, &m_osSignal)) {
    m_extraAuth = false;
    m_dataReceived = false;
}

TestCppClient::~TestCppClient() {
    delete m_pClient;
}

bool TestCppClient::connect(const char * host, int port, int clientId) {
    std::cout << "Connecting to " << host << ":" << port << " clientId:" << clientId << std::endl;
    
    bool bRes = m_pClient->eConnect(host, port, clientId, m_extraAuth);
    
    if (bRes) {
        std::cout << "Connected to " << host << ":" << port << " clientId:" << clientId << std::endl;
        
        // Request historical data after a short delay
        std::this_thread::sleep_for(std::chrono::seconds(2));
       // requestHistoricalData();
	   requestTop10HistoricalData();
    } else {
        std::cout << "Failed to connect" << std::endl;
    }
    
    return bRes;
}

void TestCppClient::disconnect() const {
    m_pClient->eDisconnect();
    std::cout << "Disconnected" << std::endl;
}

void TestCppClient::requestHistoricalData(
    const std::vector<std::string>& stockSymbols,
    const std::string& duration = "1 M",
    const std::string& barSize = "1 day",
    int delayMs = 250) {
    
    if (stockSymbols.empty()) {
        std::cerr << "Error: No stock symbols provided" << std::endl;
        return;
    }
    
    std::cout << "\n===== REQUESTING HISTORICAL DATA FOR " 
              << stockSymbols.size() << " STOCKS =====\n" << std::endl;
    
    int tickerId = 1001;
    int successCount = 0;
    
    for (const auto& symbol : stockSymbols) {
        try {
            Contract contract;
            contract.symbol = symbol;
            contract.secType = "STK";
            contract.exchange = "SMART";
            contract.currency = "USD";
            
            std::cout << "[" << tickerId << "] Requesting " << barSize 
                      << " bars for " << symbol << " over " << duration << "..." 
                      << std::flush;
            
            m_pClient->reqHistoricalData(
                tickerId,
                contract,
                "",
                duration,
                barSize,
                "TRADES",
                1,      // Regular Trading Hours only
                1,      // yyyyMMdd format
                false,  // Not keeping updates
                TagValueListSPtr()
            );
            
            std::cout << " Request sent successfully" << std::endl;
            successCount++;
            tickerId++;
            
            // Rate limiting: don't exceed IBKR's recommended 50 requests per 10 seconds
            if (delayMs > 0 && tickerId < 1001 + stockSymbols.size()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            }
            
        } catch (const std::exception& e) {
            std::cerr << "\nError requesting data for " << symbol << ": " 
                      << e.what() << std::endl;
        }
    }
    
    std::cout << "\nCompleted: " << successCount << "/" << stockSymbols.size() 
              << " requests sent successfully" << std::endl;
}

// Usage example:
void TestCppClient::requestTop10HistoricalData() {
    std::vector<std::string> topStocks = {
        "AAPL", "MSFT", "GOOGL", "AMZN", "NVDA",
        "META", "TSLA", "BRK.B", "UNH", "JPM"
    };
    
    // Request 1 month of daily data for top 10 stocks
    requestHistoricalData(topStocks, "1 M", "1 day", 250);
    
    // Or for a different timeframe:
    // requestHistoricalData(topStocks, "1 Y", "1 week", 500);
}



void TestCppClient::error(int id, int errorCode, const std::string& errorString) {
    std::cout << "Error. Id: " << id << ", Code: " << errorCode << ", Msg: " << errorString << std::endl;
}

void TestCppClient::error(int id, time_t errorTime, int errorCode, const std::string& errorString, const std::string& advancedOrderRejectJson) {
    std::cout << "Error. Id: " << id << ", Time: " << errorTime << ", Code: " << errorCode << ", Msg: " << errorString << std::endl;
}

void TestCppClient::connectionClosed() {
    std::cout << "Connection closed" << std::endl;
}

void TestCppClient::nextValidId(OrderId orderId) {
    std::cout << "Next Valid Id: " << orderId << std::endl;
}

void TestCppClient::managedAccounts(const std::string& accountsList) {
    std::cout << "Account List: " << accountsList << std::endl;
}

void TestCppClient::historicalData(TickerId reqId, const Bar& bar) {
    m_dataReceived = true;
    std::cout << "Historical Bar - Time: " << bar.time
              << ", Open: " << bar.open
              << ", High: " << bar.high
              << ", Low: " << bar.low
              << ", Close: " << bar.close
              << ", Volume: " << bar.volume << std::endl;

            
}

void TestCppClient::historicalDataEnd(int reqId, const std::string& startDate, const std::string& endDate) {
    std::cout << "\nHistorical data completed. From " << startDate << " to " << endDate << std::endl;
    m_historicalDataCompleted = true;  // Set flag instead of disconnecting
    // DON'T call disconnect() here
}
