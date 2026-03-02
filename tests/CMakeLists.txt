add_executable(signal_tests signal_tests.cpp)
target_link_libraries(signal_tests PRIVATE 
    GTest::gtest_main 
    tick_consumer 
    state_estimator 
    optimizer
)
add_test(NAME signal_tests COMMAND signal_tests)
