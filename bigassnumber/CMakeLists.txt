project(BigAssNumber)

set(HEADER_FILES bigassnumber.h)
set(SOURCE_FILES operators.cpp assignment.cpp rangoperations.cpp misc.cpp comparison.cpp display.cpp extra.cpp)

add_library(bignumber STATIC ${SOURCE_FILES} ${HEADER_FILES})