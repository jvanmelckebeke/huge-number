project(BigNumber)

set(HEADER_FILES bignumber.h)
set(SOURCE_FILES operators/addition.cpp construct.cpp rangoperations.cpp misc.cpp comparison.cpp display.cpp extra.cpp operators/reduction.cpp operators/multiplication.cpp operators/division.cpp)

add_library(bignumber STATIC ${SOURCE_FILES} ${HEADER_FILES})