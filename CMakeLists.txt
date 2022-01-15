cmake_minimum_required(VERSION 3.21)
project(random_primes)

set(CMAKE_CXX_STANDARD 14)

set(EXTRA_TOOLS runners/helpers/testhelper.cpp runners/helpers/testhelper.h)

include_directories(bigassnumber)
add_subdirectory(bigassnumber)


add_executable(test_manual runners/manual_numbertest.cpp ${EXTRA_TOOLS})
add_executable(test_automatic runners/automatic_numbertest.cpp ${EXTRA_TOOLS})


target_link_libraries(test_manual bignumber)
target_link_libraries(test_automatic bignumber)