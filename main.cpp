#include "core/Bank.hpp"
#include "simulation/Simulator.hpp"
#include "infra/Metrics.hpp"

int main() {
    Metrics metrics;

    Bank bank(
        1000,                   // accounts
        100000,                 // initial balance
        LockStrategy::Striping, // стратегия
        16,                     // stripes
        16,                     // retries
        &metrics
    );

    Simulator sim(
        bank,
        metrics,
        8,          // threads
        100000      // tx per thread
    );

    sim.run();

    return 0;
}