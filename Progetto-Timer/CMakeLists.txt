cmake_minimum_required(VERSION 4.0)
project(Progetto_Timer)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(Progetto_Timer main.cpp
        AnalogClock.h
        AnalogClock.h)

target_link_libraries(Progetto_Timer Qt6::Widgets)