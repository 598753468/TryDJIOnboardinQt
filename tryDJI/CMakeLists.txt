project(tryDJI)

cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )

aux_source_directory(. SRC_LIST)

add_subdirectory(DJI_LIB)
add_subdirectory(OpenCV_LIB)
link_libraries (pthread)
ADD_DEFINITIONS(-DPLATFORM_LINUX)
ADD_DEFINITIONS(-DTINYXML_CFG)            

#INCLUDE_DIRECTORIES(${PROJET_SOURCE_DIR}/DJI_LIB)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries( tryDJI
${OpenCV_LIBS}
DJI
SolvePnP
)

add_dependencies(${PROJECT_NAME}
DJI
SolvePnP
)


set( CMAKE_BUILD_TYPE Debug ) #to debug
