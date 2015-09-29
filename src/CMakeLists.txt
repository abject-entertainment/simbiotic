cmake_minimum_required(VERSION 3.3)

project(simbiotic VERSION 0.1.0 LANGUAGES CXX)

message(STATUS "Building for platform: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

# src/core
include_directories(core)
add_library(core_obj OBJECT
	core/Master.cpp
	core/Path.cpp
	)

# deliverable
add_executable(simbiotic
	main.cpp
	$<TARGET_OBJECTS:core_obj>
	)
