#include "data.h"
#include <iostream>
#include <cmath>

tickerData::tickerData() {}

calculation::calculation(tickerData &stockInfo)
    : ticker(stockInfo) {}

// -------------------------
// RSI CALCULATION
// -------------------------
double calculation::calRSIDaily(const std::vector<double> &closes, int period)
{
    if (closes.size() <= period)
        return 0.0;

    double gain = 0.0, loss = 0.0;

    // First average gain/loss
    for (int i = 1; i <= period; i++) {
        double diff = closes[i] - closes[i - 1];
        if (diff >= 0)
            gain += diff;
        else
            loss -= diff;
    }

    gain /= period;
    loss /= period;

    // Wilder smoothing
    for (size_t i = period + 1; i < closes.size(); i++) {
        double diff = closes[i] - closes[i - 1];
        double g = diff > 0 ? diff : 0;
        double l = diff < 0 ? -diff : 0;

        gain = (gain * (period - 1) + g) / period;
        loss = (loss * (period - 1) + l) / period;
    }

    if (loss == 0)
        return 100.0;

    double rs = gain / loss;
    return 100.0 - (100.0 / (1.0 + rs));
}

// -------------------------
// EMA CALCULATION
// -------------------------
double calculation::calEMADaily(const std::vector<double> &closes, int period)
{
    if (closes.size() < period)
        return 0.0;

    double multiplier = 2.0 / (period + 1);
    double ema = 0.0;

    // First SMA
    for (int i = 0; i < period; i++)
        ema += closes[i];
    ema /= period;

    // EMA smoothing
    for (size_t i = period; i < closes.size(); i++)
        ema = (closes[i] - ema) * multiplier + ema;

    return ema;
}
