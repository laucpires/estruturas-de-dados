cmake_minimum_required(VERSION 3.26)
project(ed)

enable_testing()

include(GoogleTest)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(1_point exercise/1_point.cpp src/point.cpp)
add_executable(2_point exercise/2_point.cpp src/point.cpp)
add_executable(3_hours exercise/3_hours.cpp src/hours.cpp)
add_executable(4_hours exercise/4_hours.cpp src/hours.cpp)
add_executable(5_pair exercise/5_pair.cpp)
add_executable(trabalho-0804 src/trabalho-0804.cpp)

add_executable(vector_list exercise/vector_list.cpp)
add_executable(linked_list exercise/linked_list.cpp)
add_executable(doubly_linked_list exercise/doubly_linked_list.cpp)

add_executable(vector_list_test test/vector_list.cpp)
target_link_libraries(vector_list_test gtest gtest_main)
gtest_add_tests(TARGET vector_list_test)

add_executable(linked_list_test test/linked_list.cpp)
target_link_libraries(linked_list_test gtest gtest_main)
gtest_add_tests(TARGET linked_list_test)

add_executable(doubly_linked_list_test test/doubly_linked_list.cpp)
target_link_libraries(doubly_linked_list_test gtest gtest_main)
gtest_add_tests(TARGET doubly_linked_list_test)

find_package(Doxygen)

set(DOXYGEN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/doc")

configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)

add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Gerando documentação com Doxygen"
    VERBATIM)
