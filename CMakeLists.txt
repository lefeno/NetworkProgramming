cmake_minimum_required(VERSION 2.8)

project(NetworkProgramming)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/client-channel)
include_directories(${PROJECT_SOURCE_DIR}/server-asio)
include_directories(${PROJECT_SOURCE_DIR}/server-posix)
find_package(Threads REQUIRED)

set(ROOM_SOURCE
        room/Participant.h
        room/Room.hpp room/Room.cpp
)

set(MEMORY_HANDLER
        memory_handler/MemoryHandler.cpp memory_handler/MemoryHandler.hpp
        memory_handler/AllocatorHandler.h
        memory_handler/CustomAllocHandler.h
        )

set (SOCKET
        socket/Socket.cpp socket/Socket.hpp
        socket/Connection.cpp socket/Connection.hpp
        )

add_executable(ServerAsio
        server-asio/server_asio_main.cpp
        server-asio/ServerAsio.cpp server-asio/ServerAsio.hpp
        server-asio/Session.cpp server-asio/Session.hpp
        ${ROOM_SOURCE}
        )


add_executable(ServerPosix
        server-posix/server_posix_main.cpp
        server-posix/ServerPosix.cpp server-posix/ServerPosix.hpp
        ${SOCKET}
        ${ROOM_SOURCE}
        server-posix/PosixSession.cpp server-posix/PosixSession.hpp)

add_executable(ClientPseudo
        client-pseudo/client_main.cpp
        client-pseudo/ClientPseudo.cpp client-pseudo/ClientPseudo.hpp
        ${SOCKET}
        )

find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(ServerAsio ${Boost_INCLUDE_DIRS})

target_link_libraries(ClientPseudo Threads::Threads)
target_link_libraries(ServerAsio Threads::Threads)
target_link_libraries(ServerAsio ${Boost_LIBRARIES})