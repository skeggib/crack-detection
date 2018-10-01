cmake_minimum_required (VERSION 2.8)
project (crack-detection)
set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories (${OPENCV_INCLUDE_DIR})
include_directories ("headers")

add_executable(evaluation src/evaluation.cpp src/scoring.cpp)
target_link_libraries (evaluation ${OpenCV_LIBS})

add_executable(traitement 
    src/processing.cpp
    src/arguments.cpp
    src/filters.cpp)
target_link_libraries (traitement ${OpenCV_LIBS})

add_executable(optimisation
    src/optimization.cpp
    src/arguments.cpp
    src/filters.cpp
    src/scoring.cpp)
target_link_libraries (optimisation ${OpenCV_LIBS})
