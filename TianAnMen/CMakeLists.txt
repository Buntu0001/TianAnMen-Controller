cmake_minimum_required(VERSION 3.21)
project(TianAnMen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()
add_executable(TianAnMen main.cc main.cc main.h Connection/client.cc Connection/client.h Misc/util.cc Misc/util.h Connection/packet.cc Connection/packet.h Misc/structure.h Connection/handling.cc Connection/handling.h Connection/client_list.cc Connection/client_list.h)
if(WIN32)
    target_link_libraries(TianAnMen wsock32 ws2_32)
endif()