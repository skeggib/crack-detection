﻿cmake_minimum_required (VERSION 2.8)
project (crack-detection)
set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

include_directories (${OPENCV_INCLUDE_DIR})
include_directories ("headers")

add_executable(evaluation 
    src/evaluation.cpp
    src/scoring.cpp
    src/arguments.cpp)
target_link_libraries (evaluation ${OpenCV_LIBS})

add_executable(precision
    src/precision.cpp
    src/arguments.cpp
    src/scoring.cpp)
target_link_libraries (precision ${OpenCV_LIBS})

add_executable(recall
    src/recall.cpp
    src/arguments.cpp
    src/scoring.cpp)
target_link_libraries (recall ${OpenCV_LIBS})

add_executable(seuilGris 
    src/seuilGris.cpp
    src/arguments.cpp
    src/filters.cpp)
target_link_libraries (seuilGris ${OpenCV_LIBS})

add_executable(sobel 
    src/sobel.cpp
    src/arguments.cpp
    src/filters.cpp)
target_link_libraries (sobel ${OpenCV_LIBS})

add_executable(laplacien 
    src/laplacien.cpp
    src/arguments.cpp
    src/filters.cpp)
target_link_libraries (laplacien ${OpenCV_LIBS})

add_executable(gradient_direction 
    src/gradient_direction.cpp
    src/arguments.cpp
    src/filters.cpp)
target_link_libraries (gradient_direction ${OpenCV_LIBS})

add_executable(low_freq_substraction 
    src/low_freq_substraction.cpp
    src/arguments.cpp
    src/filters.cpp)
target_link_libraries (low_freq_substraction ${OpenCV_LIBS})

add_executable(sobel_clusters 
    src/sobel_clusters.cpp
    src/arguments.cpp
    src/filters.cpp)
target_link_libraries (sobel_clusters ${OpenCV_LIBS})
