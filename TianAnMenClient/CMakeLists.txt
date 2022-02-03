cmake_minimum_required(VERSION 3.21)
project(TianAnMenClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(TianAnMenClient main.cc main.h util.cc util.h eventhandler.cc eventhandler.h cmake-build-debug/packet.cc cmake-build-debug/packet.h)

if(WIN32)
    target_link_libraries(TianAnMenClient wsock32 ws2_32)
endif()
