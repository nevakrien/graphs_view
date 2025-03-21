cmake_minimum_required(VERSION 3.10)
project(GraphEditor)

set(CMAKE_CXX_FLAGS_DEBUG "-g1 -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "-fsanitize=address")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(GraphEditor main.cpp GraphScene.cpp GraphNode.cpp GraphEdge.cpp) 
target_link_libraries(GraphEditor Qt6::Widgets)
