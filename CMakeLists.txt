cmake_minimum_required(VERSION 2.8)

project(robot_route_plan)

SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_C_FLAGS_DEBUG "-g -Wall") 

#SET(CAGL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../software/CGAL-4.9")
SET(CAGL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CGAL-4.9")

include_directories("${CAGL_PATH}/include")
link_directories("${CAGL_PATH}/lib")
#find_package(CGAL REQUIRED)
#include_directories(${CGAL_INCLUDE_DIRS})
#include(${CGAL_USE_FILE})
#link_directories(${CGAL_LIBRARY_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SRCS)  
ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})
target_link_libraries(${PROJECT_NAME} CGAL CGAL_Core)

install (TARGETS ${PROJECT_NAME} DESTINATION bin)
#install (FILES ${PROJECT_NAME} DESTINATION bin)
