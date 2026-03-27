#pragma once

#include <boost/thread/mutex.hpp>
#include <vector>
#include <utility>
#include <cstddef>

enum class LockStrategy {
    PerAccount,
    Striping
};

class LockManager {
public:
    using Mutex = boost::mutex;

    LockManager(size_t accounts,
                LockStrategy strategy,
                size_t stripes = 16);

    /*Возвращает мьютексы в правильном порядке, второй может быть nullptr
(если оба аккаунта попали в один stripe) */
    std::pair<Mutex*, Mutex*> get_locks(int acc1, int acc2);

private:
    LockStrategy strategy_;

    std::vector<Mutex> account_mutexes_;

    std::vector<Mutex> striped_mutexes_;
    size_t stripes_;

private:
    Mutex& get_striped(int id);
};