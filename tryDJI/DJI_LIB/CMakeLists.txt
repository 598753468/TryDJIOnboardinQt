CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
link_libraries (pthread)
ADD_DEFINITIONS(-DPLATFORM_LINUX)
ADD_DEFINITIONS(-DTINYXML_CFG)
SET(SOURCE_FILES #define variable
DJI_Pro_Sample.cpp
tinyxml2.cpp
DJI_Pro_App.cpp
DJI_Pro_Codec.cpp
DJI_Pro_Hw.cpp
DJI_Pro_Link.cpp
DJI_Pro_Rmu.cpp
DJI_Pro_Sample.h
tinyxml2.h
DJI_Pro_App.h
DJI_Pro_Codec.h
DJI_Pro_Hw.h
DJI_Pro_Link.h
DJI_Pro_Rmu.h
DJI_Pro_Config.h
)

add_library(DJI STATIC ${SOURCE_FILES})

set( CMAKE_BUILD_TYPE Debug )
