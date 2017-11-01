add_executable (impub_node main.cpp)
target_link_libraries (impub_node
                        ${catkin_LIBRARIES}
                        ${OpenCV_LIBRARIES}
)
