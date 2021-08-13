cmake_minimum_required(VERSION 3.12)
project(queue_example)
set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.76.0 REQUIRED COMPONENTS)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(queue_example main.cpp)
    target_link_libraries(queue_example ${Boost_LIBRARIES})
endif()
