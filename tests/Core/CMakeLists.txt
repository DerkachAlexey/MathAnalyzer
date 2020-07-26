cmake_minimum_required(VERSION 2.8)

project(core_tests)

include_directories("../../src/Core")
include_directories("../../src/Nodes")
include_directories("../../src/Visitors")

#parser test
set( parser_test parser_test.cpp
"../catch2.hpp" )


add_executable( parser_test ${parser_test})
target_link_libraries( parser_test  Analyzer )

set( diff_test diff_test.cpp
		"../catch2.hpp")

add_executable( diff_test ${diff_test})

target_link_libraries( diff_test  Analyzer )

set( function_test function_test.cpp
		"../catch2.hpp")

add_executable( function_test ${function_test})

target_link_libraries( function_test  Analyzer )

set( math_vector_test math_vector_test.cpp
		"../catch2.hpp")

add_executable( math_vector_test ${math_vector_test})

target_link_libraries( math_vector_test  Analyzer )