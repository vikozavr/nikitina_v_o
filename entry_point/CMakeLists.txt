project(entry_point)


SET(OpenCV_DIR C:/opencv/build/)
find_package(OpenCV REQUIRED)

add_executable(entry_point main.cpp)
target_link_libraries(entry_point  ${OpenCV_LIBS})
target_link_libraries(entry_point object_tracker)