# C++ library for Crasher

[Crashser](https://github.com/VladimirBalun/Crashser) - 
open source dump/crash server for different programming 
languages (used for crash analysis in various applications).
This library is crossplatfrom (now only Windows, Linux, OSX) 
implementation C++ client for Crasher dump/crash server.

## How to build library
In order to build the library, you will need
the following installed packages on your machine:

  - **boost**

After that you can use the following commands:

    cd crasher-cpp-client
    mkdir build
    cd build
    cmake ..

## Additional build options
 You can choose target library type (static 
 or dynamic), disabling or enabling examples
 with the following options for cmake:

    cmake .. -DBUILD_STATIC_LIBRARY=ON -DBUILD_EXAMPLES=ON

## Examples

 Segmentation Faults and std::terminate calls sometimes 
 happen in programs. Programmers usually wish to get as 
 much information as possible on such incidents, 
 so having a stacktrace will significantly improve 
 debugging and fixing. So, we can you Crashser library for these
 purposes:

```cpp
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
```

 Sometimes it is necessary to control the throwing of some exceptions. 
 With Crashser library you can do it like this:

```cpp
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
```

## License
Information about license will be added later...
