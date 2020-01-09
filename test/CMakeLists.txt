cmake_minimum_required(VERSION 3.5)
project(UtilitesTests)
add_executable(${PROJECT_NAME}
		WatchdogTest.cpp parallel_forTest.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} Utilities)
