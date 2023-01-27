project(entry_point)





add_executable(entry_point main.cpp)
target_link_libraries(entry_point  ${OpenCV_LIBS})
target_link_libraries(entry_point object_tracker)