add_executable(signal_tests signal_tests.cpp)

# Allow the tests to include libraries using relative paths from the root
target_include_directories(signal_tests PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(signal_tests PRIVATE 
    GTest::gtest_main 
    tick_consumer 
    state_estimator 
    optimizer
    hardware_bridge
    Eigen3::Eigen
)
add_test(NAME signal_tests COMMAND signal_tests)
