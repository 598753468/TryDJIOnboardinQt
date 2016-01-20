project(tryDJI)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
#add_subdirectory(DJI_LIB)
link_libraries (pthread)
ADD_DEFINITIONS(-DPLATFORM_LINUX)
ADD_DEFINITIONS(-DTINYXML_CFG)
find_package( OpenCV REQUIRED )
add_executable(${PROJECT_NAME} ${SRC_LIST})
set( CMAKE_BUILD_TYPE Debug )
SET(SOURCE_FILES
DJI_Pro_Sample.cpp
tinyxml2.cpp
DJI_Pro_App.cpp
DJI_Pro_Codec.cpp
DJI_Pro_Hw.cpp
DJI_Pro_Link.cpp
DJI_Pro_Rmu.cpp
Transmission.cpp
CTimer.cpp
SmoothControl.cpp
)
INCLUDE_DIRECTORIES( #相关头文件的目录
${PROJET_SOURCE_DIR}
)

target_link_libraries( tryDJI ${OpenCV_LIBS} )
