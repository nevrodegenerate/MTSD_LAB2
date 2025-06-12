cmake_minimum_required(VERSION 3.15)
project(char_list_tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

add_library(char_list STATIC
  source/char_list.cpp
  source/char_list.h
)

add_executable(tests 
  test/test.cpp
  test/pch.cpp
  test/pch.h
)

target_precompile_headers(tests PRIVATE test/pch.h)

target_link_libraries(tests PRIVATE
  char_list
  GTest::gtest_main
  GTest::gmock
)

add_test(NAME char_list_tests COMMAND tests)
