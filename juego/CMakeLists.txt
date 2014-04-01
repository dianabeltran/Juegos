cmake_minimum_required(VERSION 2.8)
project(JUEGO_DEMO)

#aux_source_directory(. SRC_LIST)
#find_package(PCL 1.0 REQUIRED COMPONENTS io kdtree filters features keypoints sample_consensus segmentation visualization)
find_package(OpenCV REQUIRED)
include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})

# Nodelet library
add_library(${PROJECT_NAME} juego_demo.cpp)
add_executable(juego_demo juego_demo.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})#LIBS



#target_link_libraries(features_demo pcl_io pcl_kdtree pcl_filters pcl_features pcl_keypoints pcl_visualization /opt/ros/groovy/lib/libpcl_common.so.1.6 /usr/lib/libvtkCommon.so.5.8 /usr/lib/libvtkFiltering.so.5.8 /opt/ros/groovy/lib/libpcl_search.so.1.6 /usr/lib/libvtkRendering.so.5.8 /usr/lib/libvtkGraphics.so.5.8 )
#-lopencv_core -lopencv_imgproc -lopencv_objdetect -lopencv_highgui
target_link_libraries(juego_demo opencv_core opencv_imgproc opencv_objdetect opencv_highgui)


