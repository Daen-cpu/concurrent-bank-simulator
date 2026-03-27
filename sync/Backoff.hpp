#pragma once

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

inline void backoff(int attempt) {
    int capped = (attempt < 16) ? attempt : 16;

    boost::this_thread::sleep_for(
        boost::chrono::nanoseconds(1LL << capped)
    );
}