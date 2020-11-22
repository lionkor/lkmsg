cmake_minimum_required(VERSION 3.13)

project(messages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2 -s")

include_directories("include/lk")

if (LK_MESSAGES_STATIC)
    message("building lk::msg as static library")
    set(BUILD_MESSAGES_AS STATIC)
else () 
    message("building lk::msg as shared library (specify LK_MESSAGES_STATIC for static building)")
    set(BUILD_MESSAGES_AS SHARED)
endif()

add_library(lkmsg ${BUILD_MESSAGES_AS}
    src/messages.cpp
    src/Message.cpp
    src/Listener.cpp
    src/Channel.cpp
    src/MultiListener.cpp
)

add_executable(messages-test
    src/test.cpp
)

target_link_libraries(messages-test lkmsg)

