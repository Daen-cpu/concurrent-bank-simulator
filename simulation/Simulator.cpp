#include "Simulator.hpp"
#include <iostream>

Simulator::Simulator(Bank& bank,
                     Metrics& metrics,
                     int threads,
                     int tx_per_thread)
    : bank_(bank),
      metrics_(metrics),
      threads_(threads),
      tx_per_thread_(tx_per_thread)
{
}

void Simulator::run() {
    ThreadManager tm;

    Timer timer;
    timer.start();

    tm.run(threads_, [this]() {
        TransactionGenerator gen(bank_.accounts_count());

        for (int i = 0; i < tx_per_thread_; ++i) {
            auto tx = gen.next();
            bank_.transfer(tx);
        }
    });

    tm.join();

    timer.stop();


    std::cout << "\n=== Simulation Results ===\n";
    std::cout << "Threads:      " << threads_ << "\n";
    std::cout << "Transactions: " << threads_ * tx_per_thread_ << "\n";
    std::cout << "Time (ms):    " << timer.elapsed_ms() << "\n";

    std::cout << "\n--- Metrics ---\n";
    std::cout << "Success:  " << metrics_.success.load() << "\n";
    std::cout << "Retries:  " << metrics_.retries.load() << "\n";
    std::cout << "Failures: " << metrics_.failures.load() << "\n";

    std::cout << "\n--- Derived ---\n";
    double total_tx = threads_ * tx_per_thread_;
    double success_rate = metrics_.success / total_tx;

    std::cout << "Success rate: " << success_rate * 100.0 << "%\n";
}