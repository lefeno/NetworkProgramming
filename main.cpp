#include "server-posix/ServerPosixFork.h"
#include "server-posix/ServerPosixPreFork.h"
#include "server-posix/ServerPosixThread.h"
#include "server-posix/ServerPosixPreThread.h"
#include "server-asio/ServerAsioAllocation.h"

using namespace std;
using namespace network_programming;

int main() {
    ServerAsioAllocation serverAsio{};

    return 0;
}
