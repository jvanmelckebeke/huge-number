project(BigAssNumber)

set(HEADER_FILES bigassnumber.h)
set(SOURCE_FILES operators.cpp constructors.cpp rangoperations.cpp misc.cpp comparison.cpp display.cpp)

add_library(bignumber STATIC ${SOURCE_FILES} ${HEADER_FILES})