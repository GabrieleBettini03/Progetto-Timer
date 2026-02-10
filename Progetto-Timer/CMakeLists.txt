cmake_minimum_required(VERSION 4.0)
project(Progetto_Timer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")
find_package(Qt6 COMPONENTS REQUIRED Widgets Test)

add_executable(Progetto_Timer main.cpp
        AnalogClock.h
        Timer.cpp
        Timer.h)

target_link_libraries(Progetto_Timer Qt6::Widgets)

# === Unit Testing ===
add_executable(UnitTesting_Timer UnitTesting_Timer.cpp
        Timer.cpp
        Timer.h
        TestTimer.h)

target_link_libraries(UnitTesting_Timer Qt6::Test)