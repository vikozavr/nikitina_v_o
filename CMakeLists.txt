cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(optical_flow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

#SET(OpenCV_DIR C:/opencv/build/)

find_package(OpenCV REQUIRED)

include_directories(lib entry_point)
add_subdirectory(lib)
add_subdirectory(entry_point)



IF("${CMAKE_BUILD_TYPE}" EQUAL "Debug")
    install(TARGETS entry_point 
            CONFIGURATIONS Debug
            DESTINATION bin.dbg)
    SET(CURRENT_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})

ELSEIF("${CMAKE_BUILD_TYPE}" EQUAL "Release")
    install(TARGETS entry_point 
            CONFIGURATIONS Release
            DESTINATION bin.rel)
    SET(CURRENT_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
ELSEIF("${CMAKE_BUILD_TYPE}" EQUAL "RelWithDebInfo")
    install(TARGETS entry_point 
            CONFIGURATIONS RelWithDebInfo
            DESTINATION bin.relwithdbg)
    SET(CURRENT_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO})
ELSE()
    install(TARGETS entry_point DESTINATION bin)
    SET(CURRENT_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}) 
endif()
message("${CMAKE_BUILD_TYPE}")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dll/opencv_world460d.dll  ${CURRENT_OUTPUT_DIR}/opencv_world460d.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dll/opencv_videoio_ffmpeg460_64.dll  ${CURRENT_OUTPUT_DIR}/opencv_videoio_ffmpeg460_64.dll COPYONLY)
