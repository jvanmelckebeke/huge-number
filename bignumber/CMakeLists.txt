project(BigNumber)

set(HEADER_FILES hugenumber.h)
set(SOURCE_FILES hugenumber.cpp)

add_library(bignumber STATIC ${SOURCE_FILES} ${HEADER_FILES})