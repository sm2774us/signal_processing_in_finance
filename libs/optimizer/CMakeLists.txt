add_library(optimizer INTERFACE)
target_include_directories(optimizer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(optimizer INTERFACE Eigen3::Eigen)
