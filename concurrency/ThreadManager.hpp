#pragma once
#include <boost/thread.hpp>
#include <functional>

class ThreadManager {
public:
    void run(size_t threads, std::function<void()> worker) {
        for (size_t i = 0; i < threads; ++i) {
            group_.create_thread(worker);
        }
    }

    void join() {
        group_.join_all();
    }

private:
    boost::thread_group group_;
};