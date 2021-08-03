cmake_minimum_required(VERSION 3.19)

project(crasher_cpp_client)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(PROJECT_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)
set(PROJECT_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)
set(PROJECT_PROTOCOL_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protocol)
set(PROJECT_PROTOCOL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protobuf)

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_STATIC_LIBRARY "Build static or dynamic library" OFF)

find_package(Boost REQUIRED)
find_package(Protobuf REQUIRED)

set(PROTO_FILES app_info.proto core_dump.proto os_info.proto)
execute_process(COMMAND mkdir ${PROJECT_PROTOCOL_OUTPUT_DIR})
execute_process(COMMAND protoc --proto_path=${PROJECT_PROTOCOL_INPUT_DIR}
                               --cpp_out=${PROJECT_PROTOCOL_OUTPUT_DIR}
                               ${PROTO_FILES} RESULT_VARIABLE PROTOBUF_RESULT)

if(NOT PROTOBUF_RESULT EQUAL "0")
    message("Error with protobuf compilation: ${PROTOBUF_RESULT}")
endif()

include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_PROTOCOL_OUTPUT_DIR})
file(GLOB LIBRARY_SOURCE_FILES "sources/*.cpp")

if(BUILD_STATIC_LIBRARY)
    add_library(${PROJECT_NAME} STATIC ${LIBRARY_SOURCE_FILES})
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BIN_DIR})
    set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BIN_DIR})
else()
    add_library(${PROJECT_NAME} SHARED ${LIBRARY_SOURCE_FILES})
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BIN_DIR})
    set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BIN_DIR})
endif()

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_BIN_DIR})
endif()

if(BUILD_EXAMPLES)
    include_directories(${PROJECT_INCLUDE_DIR})
    set(EXAMPLES sigsegv_handling_example)
    foreach(EXAMPLE ${EXAMPLES})
        add_executable(${EXAMPLE} examples/${EXAMPLE}.cpp)
        target_link_libraries(${EXAMPLE} ${Boost_LIBRARIES} ${PROJECT_NAME})
        set_target_properties(${EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
        set_target_properties(${EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BIN_DIR})
        set_target_properties(${EXAMPLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BIN_DIR})
        if(CMAKE_GENERATOR MATCHES "Visual Studio")
            set_target_properties(${EXAMPLE} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_BIN_DIR})
        endif()
    endforeach()
endif()