cmake_minimum_required (VERSION 3.19)

project (crasher_cpp_client)

set (CMAKE_CXX_STANDARD 17)

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (PROJECT_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (PROJECT_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)
set (PROJECT_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

option (BUILD_EXAMPLES "Build examples" ON)
option (BUILD_STATIC_LIBRARY "Build static or dynamic library" OFF)

find_package(Boost)

if (Boost_FOUND)

    include_directories (${Boost_INCLUDE_DIRS})

    if(BUILD_STATIC_LIBRARY)
        add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES_DIR}/utils.cpp)
    else()
        add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES_DIR}/utils.cpp)
    endif()

    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})

    if (BUILD_EXAMPLES)
        include_directories (${PROJECT_INCLUDE_DIR})
        add_executable (sigsegv_handling_example examples/sigsegv_handling_example.cpp)
        target_link_libraries (sigsegv_handling_example ${Boost_LIBRARIES} ${PROJECT_NAME})
    endif()

endif ()


