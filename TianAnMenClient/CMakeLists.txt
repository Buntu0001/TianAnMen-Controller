cmake_minimum_required(VERSION 3.21)
project(TianAnMenClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()
add_executable(TianAnMenClient main.cc main.h Misc/util.cc Misc/util.h Helper/event_handler.cc Helper/event_handler.h Connection/packet.cc Connection/packet.h Misc/structure.h Connection/handling.cc Connection/handling.h)
if(WIN32)
    target_link_libraries(TianAnMenClient wsock32 ws2_32 Wininet.lib)
endif()
