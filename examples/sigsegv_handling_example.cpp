#include <csignal>
#include <iostream>

#include "crashser.h"

void my_signal_handler(int sig_number)
{
    try {
        // OSInfo name is determined automatically, but you can override it like below
        const Crashser::OSInfo os_info("OSX", "11.2.2");
        const Crashser::AppInfo app_info("test_example_app", "0.0.1");

        // Getting stack trace and build core dump structure
        std::string stack_trace = Crashser::getStackTrace();
        Crashser::CoreDump core_dump(std::move(stack_trace), &os_info, &app_info);

        // Sending core dump to Crashser collector
        Crashser::DumpServerConnector connector("localhost", "8080");
        connector.sendCoreDump(core_dump, [](const std::string& response_body) {
            std::cout << response_body << std::endl; // onResponse - isn't an asynchronous operation
        });
    } catch (const std::runtime_error& e) {
        std::cerr << "Error crash handling: " << e.what() << std::endl;
    }

    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    ::signal(SIGSEGV, &my_signal_handler);
    ::raise(SIGSEGV);
    return EXIT_SUCCESS;
}
