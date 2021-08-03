#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <csignal>
#include <boost/stacktrace.hpp>

void my_signal_handler(int signum) {
    ::signal(signum, SIG_DFL);
    boost::stacktrace::safe_dump_to("./backtrace.dump");
    ::raise(SIGABRT);
}

int main() {
    ::signal(SIGSEGV, &my_signal_handler);
    return 0;
}
