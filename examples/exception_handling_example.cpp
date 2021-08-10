#include <iostream>

#include "crashser.h"

void functionWithUnhandledException()
{
    // You can also throw exception by default and get stack trace,
    // but the code below provides information about the exception in more detail
    Crashser::throwWithStackTrace(std::logic_error("Unhandled exception"));
}

int main(int argc, char** argv)
{
    try {
        functionWithUnhandledException();
    } catch (const std::exception& e) {
        try {
            // OSInfo name is determined automatically, but you can override it like below
            const Crashser::OSInfo os_info("OSX", "11.2.2");
            const Crashser::AppInfo app_info("test_example_app", "0.0.1");

            // Getting stack trace from exception and build core dump structure
            std::string stack_trace = Crashser::getStackTrace(e);
            Crashser::CoreDump core_dump(std::move(stack_trace), &os_info, &app_info);

            // Sending core dump to Crashser collector
            Crashser::DumpServerConnector connector("localhost", "8080");
            connector.sendCoreDump(core_dump, [](const std::string& response_body) {
                std::cout << response_body << std::endl; // onResponse - isn't an asynchronous operation
            });
        } catch (const std::exception& e) {
            std::cerr << "Error crash handling: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}