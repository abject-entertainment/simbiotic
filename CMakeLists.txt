cmake_minimum_required(VERSION 3.3)

project(simbiotic_project VERSION 0.1.0 LANGUAGES NONE)

add_subdirectory(src)

add_subdirectory(test EXCLUDE_FROM_ALL)