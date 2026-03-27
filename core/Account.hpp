#pragma once
#include <cstdint>

class Account {
public:
    using Balance = int64_t;

    Account(int id, Balance initial)
        : id_(id), balance_(initial) {}

    int id() const noexcept {
        return id_;
    }

    Balance raw_balance() const noexcept {
        return balance_;
    }

    void unsafe_deposit(Balance amount) noexcept {
        balance_ += amount;
    }

    bool unsafe_withdraw(Balance amount) noexcept {
        if (balance_ < amount) return false;
        balance_ -= amount;
        return true;
    }

private:
    int id_;
    Balance balance_;
};