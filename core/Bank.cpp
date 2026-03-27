#include <iostream>
#include "Bank.hpp"

Bank::Bank(size_t accounts,
           Balance initial_balance,
           LockStrategy strategy,
           size_t stripes,
           int max_retries,
           Metrics* metrics)
    : lock_manager_(accounts, strategy, stripes),
      total_(accounts * initial_balance),
      max_retries_(max_retries),
      metrics_(metrics)
{
    accounts_.reserve(accounts);

    for (size_t i = 0; i < accounts; ++i) {
        accounts_.emplace_back(static_cast<int>(i), initial_balance);
    }
}

bool Bank::transfer(const Transaction& tx) {
    if (tx.from == tx.to)
        return false;

    auto [m1, m2] = lock_manager_.get_locks(tx.from, tx.to);

    for (int attempt = 0; attempt < max_retries_; ++attempt) {

        boost::unique_lock<boost::mutex> lock1(*m1, boost::defer_lock);
        boost::unique_lock<boost::mutex> lock2;

        if (!lock1.try_lock()) {
            if (metrics_) metrics_->retries++;
            backoff(attempt);
            continue;
        }

        if (m2) {
            lock2 = boost::unique_lock<boost::mutex>(*m2, boost::defer_lock);

            if (!lock2.try_lock()) {
                if (metrics_) metrics_->retries++;
                backoff(attempt);
                continue;
            }
        }

        Account& from = accounts_[tx.from];
        Account& to   = accounts_[tx.to];

        if (!from.unsafe_withdraw(tx.amount)) {
            return false;
        }

        to.unsafe_deposit(tx.amount);

        if (metrics_) metrics_->success++;
        return true;
    }

    if (metrics_) metrics_->failures++;
    return false;
}

void Bank::print_balances() const {
    std::cout << "\n=== Final Account Balances ===\n";

    for (size_t i = 0; i < accounts_.size(); ++i) {
        std::cout << "Account " << i << ": " << accounts_[i].raw_balance() << "\n";
    }

    std::cout << "Total: " << total_balance() << "\n";
}


