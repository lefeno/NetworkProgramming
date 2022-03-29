cmake_minimum_required(VERSION 2.8)

project(NetworkProgramming)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/client-channel)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED system)

add_executable(${PROJECT_NAME}
        "main.cpp"
        client-channel/ClientController.cpp
        client-channel/ClientChannel.cpp
        server-posix/ServerPosix.cpp
        server-posix/ServerPosixFork.cpp
        server-posix/ServerPosixPreFork.cpp
        server-posix/ServerPosixPreForkDescriptorPass.cpp
        server-posix/ServerPosixThread.cpp server-posix/ServerPosixPreThread.cpp server-posix/ServerPosixPreThread.h server-asio/ServerAsioAllocation.cpp server-asio/ServerAsioAllocation.h server-asio/MemoryHandler.cpp server-asio/MemoryHandler.h server-asio/AllocatorHandler.cpp server-asio/AllocatorHandler.h)

target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARY})