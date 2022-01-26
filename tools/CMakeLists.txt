project(TimerTool)

set(HEADER_FILES Timer.h)
set(SOURCE_FILES Timer.cpp)

add_library(timer STATIC ${SOURCE_FILES} ${HEADER_FILES})