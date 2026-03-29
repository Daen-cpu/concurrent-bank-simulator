# Concurrent Bank Simulator

A multi-threaded banking simulation focused on correctness and performance under high contention.

The system models concurrent money transfers between accounts using fine-grained locking and non-blocking synchronization strategies.

## Features

- Multi-threaded transaction processing using Boost.Thread
- Fine-grained locking with lock striping
- Non-blocking synchronization using try_lock + backoff
- Atomic global balance tracking
- Retry mechanism under contention
- Metrics collection (success / retries / failures)
## Problem

Simulating concurrent financial transactions introduces several challenges:

- Race conditions when updating account balances
- Deadlocks when multiple accounts are locked
- High contention under heavy load
- Maintaining global consistency of total balance
## Approach

- Each transaction attempts to acquire locks using `try_lock`
- On failure, a backoff strategy is applied to reduce contention
- Lock ordering prevents deadlocks
- Account updates are performed in a critical section
- Global balance is tracked using `std::atomic`
## Future Improvements

- Lock-free structures
- NUMA-aware allocation
- Thread affinity tuning
- Realistic transaction workloads