cmake_minimum_required(VERSION 2.8)
project(JUEGO_DEMO)


find_package(OpenCV REQUIRED)
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})


add_library(${PROJECT_NAME} juego_demo.cpp)
add_executable(juego_demo juego_demo.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})#LIBS





target_link_libraries(juego_demo opencv_core opencv_imgproc opencv_objdetect opencv_highgui)


