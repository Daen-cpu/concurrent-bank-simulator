#pragma once

#include "../core/Transaction.hpp"
#include <thread>
#include <random>
#include <chrono>


class TransactionGenerator {
public:
    explicit TransactionGenerator(int accounts)
        : accounts_(accounts) {}

    Transaction next() {
        return {
            rand_account(),
            rand_account(),
            rand_amount()
        };
    }

private:
    int accounts_;

    static inline thread_local std::mt19937 rng_{
        static_cast<unsigned>(
            std::chrono::high_resolution_clock::now()
                .time_since_epoch()
                .count()
        ) ^ std::hash<std::thread::id>{}(std::this_thread::get_id())
    };

    int rand_account() {
        std::uniform_int_distribution<int> dist(0, accounts_ - 1);
        return dist(rng_);
    }

    int64_t rand_amount() {
        std::uniform_int_distribution<int64_t> dist(1, 1000);
        return dist(rng_);
    }
};