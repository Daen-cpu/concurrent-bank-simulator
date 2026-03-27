#pragma once
#include <atomic>

struct Metrics {
    std::atomic<int> success{0};
    std::atomic<int> retries{0};
    std::atomic<int> failures{0};
};