cmake_minimum_required(VERSION 3.20)
project(cycle-search)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} src/solution.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest)

add_executable(${PROJECT_NAME}-test src/solution.cpp)
target_link_libraries(${PROJECT_NAME}-test PRIVATE GTest::GTest)
target_compile_definitions(${PROJECT_NAME}-test PRIVATE TESTING=1)
