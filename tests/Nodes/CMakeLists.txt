cmake_minimum_required(VERSION 2.8)

project(nodes_tests)

include_directories("../../src/Core")
include_directories("../../src/Nodes")
include_directories("../../src/Visitors")

set( symbol_test symbol_test.cpp
		 "../catch2.hpp" )

add_executable( symbol_test ${symbol_test})
target_link_libraries( symbol_test Analyzer )