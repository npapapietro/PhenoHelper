project(PhenoHelper)
cmake_minimum_required (VERSION 3.2.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++14")

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(BOOST_INCLUDE_DIR $ENV{BOOST_INC})

add_library(ROOTSTRUCTURE RootStructure.cpp)
add_library(LAGRANGIANLIB Lagrangian.cpp)

add_executable(PhenoHelper main.cpp)

target_link_libraries(LAGRANGIANLIB ROOTSTRUCTURE)
target_link_libraries(PhenoHelper LAGRANGIANLIB)
