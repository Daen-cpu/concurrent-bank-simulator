#include "LockManager.hpp"

LockManager::LockManager(size_t accounts,
                         LockStrategy strategy,
                         size_t stripes)
    : strategy_(strategy),
      account_mutexes_(strategy == LockStrategy::PerAccount ? accounts : 0),
      striped_mutexes_(strategy == LockStrategy::Striping ? stripes : 0),
      stripes_(stripes)
{
}

LockManager::Mutex& LockManager::get_striped(int id) {
    return striped_mutexes_[id % stripes_];
}

std::pair<LockManager::Mutex*, LockManager::Mutex*>
LockManager::get_locks(int acc1, int acc2) {

    Mutex* m1;
    Mutex* m2;

    if (strategy_ == LockStrategy::PerAccount) {
        m1 = &account_mutexes_[acc1];
        m2 = &account_mutexes_[acc2];
    } else {
        m1 = &get_striped(acc1);
        m2 = &get_striped(acc2);
    }


    if (m1 == m2) {
        return {m1, nullptr};
    }


    return (m1 < m2)
        ? std::make_pair(m1, m2)
        : std::make_pair(m2, m1);
}