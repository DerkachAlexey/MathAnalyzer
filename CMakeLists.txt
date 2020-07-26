cmake_minimum_required(VERSION 2.8)

project(MathAnalyzer)

add_subdirectory(src/)
add_subdirectory(tests/)

add_executable(run src/main.cpp)
target_link_libraries(run Analyzer)

target_include_directories(run PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Core ${CMAKE_CURRENT_SOURCE_DIR}/src/Visitors ${CMAKE_CURRENT_SOURCE_DIR}/src/Nodes)