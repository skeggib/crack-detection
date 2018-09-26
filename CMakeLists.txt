cmake_minimum_required (VERSION 2.8)
project (crack-detection)

# OpenCV
find_package(OpenCV REQUIRED)

include_directories (${OPENCV_INCLUDE_DIR})
include_directories ("headers")

add_executable (evaluation src/evaluation.cpp src/scoring.cpp)
target_link_libraries (evaluation ${OpenCV_LIBS})

add_executable (inverse src/inverse.cpp)
target_link_libraries (inverse ${OpenCV_LIBS})

add_executable (sobel src/sobel.cpp src/tools.cpp)
target_link_libraries (sobel ${OpenCV_LIBS})

add_executable (gaussianBlurTest src/gaussianBlurTest.cpp)
target_link_libraries (gaussianBlurTest ${OpenCV_LIBS})

add_executable (clusters src/clusters.cpp src/tools.cpp)
target_link_libraries (clusters ${OpenCV_LIBS})

add_executable (optimization src/optimization.cpp src/tools.cpp src/scoring.cpp)
target_link_libraries (optimization ${OpenCV_LIBS})