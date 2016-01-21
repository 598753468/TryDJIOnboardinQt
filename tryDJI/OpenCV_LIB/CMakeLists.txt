cmake_minimum_required(VERSION 2.8)
find_package( OpenCV REQUIRED )
#Show Images?
#ADD_DEFINITIONS(-DSHOW_DEBUG_IMAGES)
#

link_libraries (pthread)

SET(SOURCE_FILES
BGRAVideoFrame.h
CameraCalibration.cpp
CameraCalibration.hpp
DebugHelpers.hpp
GeometryTypes.cpp
GeometryTypes.hpp
Marker.cpp
Marker.hpp
MarkerDetector.cpp
MarkerDetector.hpp
TinyLA.cpp
TinyLA.hpp
)

add_library(SolvePnP STATIC ${SOURCE_FILES})

target_link_libraries( SolvePnP ${OpenCV_LIBS} )

set( CMAKE_BUILD_TYPE Debug )

