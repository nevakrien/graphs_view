cmake_minimum_required(VERSION 3.10)
project(GraphEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(GraphEditor main.cpp GraphScene.cpp GraphNode.cpp GraphEdge.cpp) 
target_link_libraries(GraphEditor Qt6::Widgets)
