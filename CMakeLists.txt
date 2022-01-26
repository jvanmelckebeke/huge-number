cmake_minimum_required(VERSION 3.16.3)
project(random_primes)

set(CMAKE_CXX_STANDARD 20)

set(EXTRA_TOOLS runners/helpers/testhelper.cpp runners/helpers/testhelper.h)

include_directories(bigassnumber)
add_subdirectory(bigassnumber)

include_directories(tools)
add_subdirectory(tools)


add_executable(test_manual runners/manual_numbertest.cpp ${EXTRA_TOOLS})
add_executable(test_automatic runners/automatic_numbertest.cpp ${EXTRA_TOOLS})
add_executable(primecheck runners/primetest.cpp ${EXTRA_TOOLS})
add_executable(test_performance runners/performancetest.cpp)


target_link_libraries(test_manual bignumber timer)
target_link_libraries(test_automatic bignumber timer)
target_link_libraries(primecheck bignumber timer)
target_link_libraries(test_performance bignumber timer)