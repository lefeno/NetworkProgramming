cmake_minimum_required(VERSION 2.8)

project(NetworkProgramming)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/client-channel)
include_directories(${PROJECT_SOURCE_DIR}/server-asio)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}
        "main.cpp"
        client-channel/ClientController.cpp
        client-channel/ClientChannel.cpp
        server-posix/ServerPosix.cpp
        server-posix/ServerPosixFork.cpp
        server-posix/ServerPosixPreFork.cpp
        server-posix/ServerPosixPreForkDescriptorPass.cpp
        server-posix/ServerPosixThread.cpp server-posix/ServerPosixPreThread.cpp
        server-posix/ServerPosixPreThread.h server-asio/ServerAsioAllocation.cpp
        server-asio/ServerAsioAllocation.hpp server-asio/MemoryHandler.cpp
        server-asio/MemoryHandler.hpp server-asio/AllocatorHandler.h
        server-asio/CustomAllocHandler.h server-asio/Session.cpp server-asio/ChatServer.cpp server-asio/ChatServer.hpp server-asio/ChatParticipant.h server-asio/ChatRoom.cpp server-asio/ChatRoom.hpp server-asio/ChatSession.cpp server-asio/ChatSession.hpp)

set (BOOST_INCLUDEDIR "/usr/boost/include/boost")
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARY})