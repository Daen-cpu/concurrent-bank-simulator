#pragma once

#include "Account.hpp"
#include "Transaction.hpp"

#include "../sync/LockManager.hpp"
#include "../sync/Backoff.hpp"
#include "../infra/Metrics.hpp"

#include <vector>
#include <atomic>

class Bank {
public:
    using Balance = int64_t;

    Bank(size_t accounts,
         Balance initial_balance,
         LockStrategy strategy,
         size_t stripes,
         int max_retries,
         Metrics* metrics);

    bool transfer(const Transaction& tx);

    Balance total_balance() const noexcept {
        return total_.load(std::memory_order_relaxed);
    }

    size_t accounts_count() const noexcept {
        return accounts_.size();
    }

    void print_balances() const;

private:
    std::vector<Account> accounts_;
    LockManager lock_manager_;

    std::atomic<Balance> total_;

    int max_retries_;
    Metrics* metrics_;
};