cmake_minimum_required(VERSION 3.21)
project(TianAnMen)

set(CMAKE_CXX_STANDARD 17)

add_executable(TianAnMen main.cc main.cc main.h clientmanage.cc clientmanage.h client.cc client.h util.cc util.h packet.cc packet.h)
if(WIN32)
    target_link_libraries(TianAnMen wsock32 ws2_32)
endif()