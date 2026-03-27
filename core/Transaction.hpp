#pragma once
#include <cstdint>

struct Transaction {
    int from;
    int to;
    int64_t amount;
};