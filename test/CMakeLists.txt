cmake_minimum_required(VERSION 3.3)

project(simbiotic_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

# tests

# include_directories(../dependencies/googletest/googletest/include)
# link_libraries(${PROJECT_SOURCE_DIR}/../build/googletest/libgtest_main.a)

add_definitions(-DTEST_BUILD)

add_executable(test_Path main.cpp core/Path.cpp ../src/core/Path.cpp)