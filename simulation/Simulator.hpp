#pragma once

#include "../core/Bank.hpp"
#include "../concurrency/ThreadManager.hpp"
#include "TransactionGenerator.hpp"
#include "../infra/Metrics.hpp"
#include "../infra/Timer.hpp"

class Simulator {
public:
    Simulator(Bank& bank,
              Metrics& metrics,
              int threads,
              int tx_per_thread);

    void run();

private:
    Bank& bank_;
    Metrics& metrics_;

    int threads_;
    int tx_per_thread_;
};