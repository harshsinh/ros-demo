add_executable (camdriver_node camdriver_node.cxx)
add_executable (grayscale_node grayscale_node.cxx)
target_link_libraries (camdriver_node
                        ${catkin_LIBRARIES}
                        ${OpenCV_LIBRARIES}
)
target_link_libraries (grayscale_node
                        ${catkin_LIBRARIES}
                        ${OpenCV_LIBRARIES}
)
