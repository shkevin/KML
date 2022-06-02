# Minimum version of CMake required to build this project.
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

################################
# Project
################################
project(KML
    VERSION 0.0.1
    DESCRIPTION "Streaming Machine Learning in C++/Cython"
    LANGUAGES CXX)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
endif()

# Minimum cpp standard
SET(CMAKE_CXX_STANDARD 11)

# Change C++ build output
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

################################
# Macros
################################
MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list ${CPP_DIR}/include/*.h)
    SET(dir_list "")
    FOREACH(FILE_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${FILE_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

################################
# Compiler Flags
################################
SET(AC_COMMON_FLAGS "${AC_COMMON_FLAGS} -fno-builtin -Wall -Wshadow -fno-strict-aliasing -fno-strength-reduce -fomit-frame-pointer -Os")
SET(AC_COMMON_FLAGS "${AC_COMMON_FLAGS} -fno-exceptions -fcheck-new -fno-rtti -Wpedantic")
SET(CMAKE_CXX_FLAGS "${AC_COMMON_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # For debugging
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions") # Add exception handling

# if compiler is Clang, link libc++, otherwise, link default libstdc++
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fsanitize=signed-integer-overflow")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags SET by default system
if(UNIX)
    MESSAGE(STATUS "Compiling on ${CMAKE_SYSTEM_NAME} with ${CMAKE_CXX_STANDARD} CXX standard")
elseif(WIN32)
    MESSAGE("This is a Windows System. Not currently supported!")
endif()

################################
# Find Main Packages
################################
# Find CCACHE to speed up builds.
MESSAGE(STATUS "Attempting to find ccache...")
FIND_PROGRAM(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    MESSAGE(STATUS "ccache found!")
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking.
else()
    MESSAGE(STATUS "ccache not found!")
endif(CCACHE_FOUND)

################################
# Normal Libraries & Executables
################################
# If using microsoft visual studio.
if(MSVC)
    SET(CMAKE_USE_RELATIVE_PATHS ON CACHE INTERNAL "" FORCE)
endif()

# Disable in-source builds to prevent source tree corruption.
if("${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  MESSAGE(FATAL_ERROR "FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.")
endif()

# Create a sources variable with a link to all cpp files to compile
SET(CPP_DIR "${CMAKE_SOURCE_DIR}/tools/cpp")
FILE(GLOB_RECURSE SOURCES "${CPP_DIR}/KML/src/*.cc" "${CPP_DIR}/KML/src/*.tcc")
FILE(GLOB_RECURSE APP_SOURCES "${CPP_DIR}/apps/*.cc")

# Add the directories needed.
ADD_LIBRARY(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${APP_SOURCES})
INCLUDE_DIRECTORIES(${CMAKE_PROJECT_NAME}_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
        "${CPP_DIR}/KML/include"
        "${CPP_DIR}/KML/src"
)

################################
# Python
################################
OPTION(BUILD_PYTHON "Build Python" OFF)
if(BUILD_PYTHON)
    MESSAGE(STATUS "Building Cython Modules")
    # Find the python interpreter, SET the PYTHON_EXECUTABLE variable
    if(CMAKE_VERSION VERSION_LESS 3.12)
        # this logic is deprecated in CMake after 3.12
        FIND_PACKAGE(PythonInterp REQUIRED)
    else()
        # This will preferentially find Python3 instead of Python2.
        # And also works with Virtual Environments.
        FIND_PACKAGE(Python)
        SET(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
    endif()

    SET(NUM_THREADS 10)
    SET(BUILD_DIR ${CMAKE_BINARY_DIR})
    SET(PACK_DIR ${CMAKE_BINARY_DIR}/tools/packages)
    SET(OUTPUT "${BUILD_DIR}/KML/python_timestamp")
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT}
        COMMAND ${PYTHON_EXECUTABLE} setup.py
            sdist --dist-dir=${PACK_DIR}
            egg_info --egg-base=${BUILD_DIR}
            build --build-base=${BUILD_DIR} --build-lib=${BUILD_DIR} --build-temp=${BUILD_DIR}/KML
            build_ext --build-lib=${BUILD_DIR} --build-temp=${BUILD_DIR}/KML -j${NUM_THREADS}
            bdist_wheel --bdist-dir=${BUILD_DIR}/build --dist-dir=${PACK_DIR}
        COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/PyKML.egg-info
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Building Python"
        )

    ADD_CUSTOM_TARGET(python_package ALL DEPENDS ${OUTPUT})

    if(BUILD_TESTING)
        SET(PYTHON_DIR "${CMAKE_SOURCE_DIR}/tools/python/KML")
        ADD_SUBDIRECTORY("${PYTHON_DIR}/tests")
    endif(BUILD_TESTING)

endif(BUILD_PYTHON)

################################
# Testing
################################
OPTION(BUILD_TESTING "Build C++ Unit Tests" OFF)
if(BUILD_TESTING)
    MESSAGE(STATUS "Enabled testing")
    ENABLE_TESTING()

    INCLUDE(FetchContent)
    FetchContent_Declare(
        googletest
            URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding project's compiler/linker settings
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    SET(gmock OFF CACHE BOOL "" FORCE)
    FETCHCONTENT_MAKEAVAILABLE(googletest)
    ADD_SUBDIRECTORY("${CPP_DIR}/KML/tests")
endif(BUILD_TESTING)

################################################################################
# Documentation
################################################################################
OPTION(BUILD_DOCUMENTATION "Build Documentation" OFF)
if(BUILD_DOCUMENTATION)
    MESSAGE(STATUS "Building Documentation")
    # Doxygen documentation of main library
    FIND_PACKAGE(Doxygen REQUIRED OPTIONAL_COMPONENTS dot)
    if(DOXYGEN_DOT_EXECUTABLE)
      SET(DOXYGEN_HAVE_DOT YES)
    else()
      SET(DOXYGEN_HAVE_DOT NO)
    endif(DOXYGEN_DOT_EXECUTABLE)

    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${CMAKE_BINARY_DIR}/docs/html/index.html
      COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/docs
      DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/README.md
        ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile
        ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
      COMMENT "Building doxygen documentation for 'KML' library")
    ADD_CUSTOM_TARGET(documentation ALL
      DEPENDS
        ${CMAKE_CURRENT_BINARY_DIR}/docs/html/index.html)

    # Sphinx documentation of Python bindings
    # if(BUILD_PYTHON_BINDINGS)
    #   add_custom_command(
    #     OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/docs/python/html/index.html
    #     COMMAND ${PYTHON_EXECUTABLE}
    #       setup.py
    #         build_sphinx
    #     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/extras/python-bindings
    #     DEPENDS
    #       ${CMAKE_CURRENT_SOURCE_DIR}/extras/python-bindings/README.md
    #       ${CMAKE_CURRENT_SOURCE_DIR}/extras/python-bindings/docs/conf.py
    #       ${CMAKE_CURRENT_SOURCE_DIR}/extras/python-bindings/docs/index.rst
    #       foo-python-bindings
    #     COMMENT "Building sphinx Python documentation for 'foo' library")
    #   add_custom_target(foo-python-documentation DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/docs/python/html/index.html)
    #   add_dependencies(documentation foo-python-documentation)
    # endif(BUILD_PYTHON_BINDINGS)
endif(BUILD_DOCUMENTATION)
