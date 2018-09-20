cmake_minimum_required(VERSION 2.8)
project(behavior_tree_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pthread -Werror=return-type")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include_directories( ../include ../sample_nodes )

add_executable(tutorial_factory_tree  tutorial_factory_tree.cpp )
target_link_libraries(tutorial_factory_tree
    ${BEHAVIOR_TREE_LIBRARIES}
    dummy_nodes
    movebase_node
    crossdoor_nodes )

