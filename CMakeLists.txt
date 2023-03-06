cmake_minimum_required(VERSION 3.2)
project(logical_clocks)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  dataStructureTests
  ./tests/dataStructureTests.cc
) 

target_link_libraries(
  dataStructureTests
  gtest
  gtest_main
)

include(GoogleTest)
# gtest_discover_tests(storageTests)
gtest_add_tests(TARGET dataStructureTests)