cmake_minimum_required(VERSION 3.21)
project(TianAnMenClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

add_executable(TianAnMenClient main.cc main.h util.cc util.h eventhandler.cc eventhandler.h packet.cc packet.h structure.h)

if(WIN32)
    target_link_libraries(TianAnMenClient wsock32 ws2_32 Wininet.lib)
endif()
