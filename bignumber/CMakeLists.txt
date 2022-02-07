project(bignumber)

set(BASE_HEADER_FILES bignumber.h)
#set(BASE_SOURCE_FILES base/extra.cpp)

#linked implementation
set(LINKED_HEADER_FILES ${BASE_HEADER_FILES} linked/linkedbignumber.h)

set(LINKED_SOURCE_FILES ${BASE_SOURCE_FILES}
        linked/construct.cpp
        linked/rangoperations.cpp
        linked/misc.cpp
        linked/comparison.cpp
        linked/display.cpp

        linked/operators/addition.cpp
        linked/operators/reduction.cpp
        linked/operators/multiplication.cpp
        linked/operators/division.cpp)


add_library(linkedbignumber STATIC ${LINKED_SOURCE_FILES} ${LINKED_HEADER_FILES})
