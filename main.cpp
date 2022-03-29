#include "server-posix/ServerPosixFork.h"
#include "server-posix/ServerPosixPreFork.h"
#include "server-posix/ServerPosixThread.h"
#include "server-posix/ServerPosixPreThread.h"

using namespace std;
using namespace network_programming;

int main() {
    ServerPosixPreThread serverPosix{};
    serverPosix.run();
    return 0;
}
