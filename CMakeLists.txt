cmake_minimum_required(VERSION 3.22)
project(dz1)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS thread chrono)
find_package(Threads REQUIRED)

add_executable(dz1
        main.cpp
        core/Bank.cpp
        sync/LockManager.cpp
        simulation/Simulator.cpp
)

target_link_libraries(dz1
        Boost::thread
        Boost::chrono
        Threads::Threads
)