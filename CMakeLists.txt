# Minimum version of CMake required to build this project.
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

################################
# Project
################################
project(KML
	VERSION 0.0.1
    DESCRIPTION "Streaming Machine Learning in c++/cython"
    LANGUAGES CXX)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
endif()

# Minimum cpp standard
SET(CMAKE_CXX_STANDARD 11)

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
# Find Packages
################################
# Find the python interpreter, SET the PYTHON_EXECUTABLE variable
if(CMAKE_VERSION VERSION_LESS 3.12)
	# this logic is deprecated in CMake after 3.12
	FIND_PACKAGE(PythonInterp REQUIRED)
else()
	# the new hotness. This will preferentially find Python3 instead of Python2.
    # And also works with Virtual Environments.
	FIND_PACKAGE(Python)
	SET(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
endif()

# Find CCACHE to speed up builds.
MESSAGE(STATUS "Attempting to find ccache...")
FIND_PROGRAM(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    MESSAGE(STATUS "ccache found!")
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
else()
    MESSAGE(STATUS "ccache not found!")
endif(CCACHE_FOUND)

# Find Catch2 for Unit Testing
# find_package(Catch2 REQUIRED)

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
       You should create a separate directory for build FILEs.")
endif()

# Create a sources variable with a link to all cpp FILEs to compile
SET(CPP_DIR "${CMAKE_SOURCE_DIR}/tools/cpp/KML")
FILE(GLOB_RECURSE SOURCES "${CPP_DIR}/src/*.cc" "${CPP_DIR}/src/*.tcc")

ADD_LIBRARY(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES})

# Add the directories needed.
INCLUDE_DIRECTORIES(${CMAKE_PROJECT_NAME}_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
        "${CPP_DIR}/include"
        "${CPP_DIR}/src"
)

################################
# Testing
################################
OPTION(BUILD_TESTING "Build gtest unit test" OFF)
if (BUILD_TESTING)
	MESSAGE(STATUS "Enabled testing")
    ENABLE_TESTING()
    FIND_PACKAGE(GTest)
    SET(BUILD_GMOCK OFF)
    ADD_SUBDIRECTORY("${CPP_DIR}/tests")
    ADD_SUBDIRECTORY("${CPP_DIR}/lib/googletest")
endif()
