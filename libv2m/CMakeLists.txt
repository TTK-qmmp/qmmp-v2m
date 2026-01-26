cmake_minimum_required(VERSION 3.0)

project(v2m)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    v2mplayer.h
    sounddef.h
    v2mconv.h
)

set(SOURCES
    sounddef.cpp
    synth_core.cpp
    v2mconv.cpp
    v2mplayer.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${STATIC_LIB_SUFFIX})

install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/lib${PROJECT_NAME})
