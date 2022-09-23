MESSAGE(STATUS "Adding C++ Sources")
SET(BINARY ${CMAKE_PROJECT_NAME}_lib)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list ./include/*.h)
    SET(dir_list "")
    FOREACH(FILE_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${FILE_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# Get the source files and the subdirectories for headers.
FILE(GLOB_RECURSE CPP_SOURCES LIST_DIRECTORIES true *.h *.cc *.tcc)
HEADER_DIRECTORIES(HEADERS)

ADD_LIBRARY(${BINARY} STATIC ${CPP_SOURCES})

FILE(COPY include DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Include the private sources/public headers.
TARGET_INCLUDE_DIRECTORIES(${BINARY}
    PUBLIC ${HEADERS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
