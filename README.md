# C++ library for Crasher

[Crashser](https://github.com/VladimirBalun/Crashser) - 
open source dump/crash server for different programming 
languages (used for crash analysis in various applications).
This library is crossplatfrom (now only Windows, Linux, OSX) 
implementation C++ client for Crasher dump/crash server.

## How to build library
In order to build the library, you will need
the following installed packages on your machine:

  - **cmake**
  - **protobuf**
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

## License
Information about license will be added later...
