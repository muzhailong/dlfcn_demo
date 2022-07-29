if(LIB_SRC_INCLUDE)
    return()
endif()
set(LIB_SRC_INCLUDE on)

add_library(hello SHARED hello.cpp)

add_library(world SHARED world.cpp)
