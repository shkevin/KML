# Minimum version of CMake required to build this project.
CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

################################
# Project
################################
PROJECT(KML
    DESCRIPTION "Streaming Machine Learning in C++/Cython"
    LANGUAGES CXX)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
endif()

# Minimum cpp standard
SET(CMAKE_CXX_STANDARD 11)

################################
# Global Variables
################################
if(NOT WIN32)
  STRING(ASCII 27 Esc)
  SET(ColourReset "${Esc}[m")
  SET(ColourBold  "${Esc}[1m")
  SET(Red         "${Esc}[31m")
  SET(Green       "${Esc}[32m")
  SET(Yellow      "${Esc}[33m")
  SET(Blue        "${Esc}[34m")
  SET(Magenta     "${Esc}[35m")
  SET(Cyan        "${Esc}[36m")
  SET(White       "${Esc}[37m")
  SET(BoldRed     "${Esc}[1;31m")
  SET(BoldGreen   "${Esc}[1;32m")
  SET(BoldYellow  "${Esc}[1;33m")
  SET(BoldBlue    "${Esc}[1;34m")
  SET(BoldMagenta "${Esc}[1;35m")
  SET(BoldCyan    "${Esc}[1;36m")
  SET(BoldWhite   "${Esc}[1;37m")
endif()

# Replace built in message system for color output.
function(message)
  LIST(GET ARGV 0 MessageType)
  if(MessageType STREQUAL FATAL_ERROR OR MessageType STREQUAL SEND_ERROR)
    LIST(REMOVE_AT ARGV 0)
    _message(${MessageType} "${BoldRed}${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL WARNING)
    LIST(REMOVE_AT ARGV 0)
    _message(${MessageType} "${BoldYellow}${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL AUTHOR_WARNING)
    LIST(REMOVE_AT ARGV 0)
    _message(${MessageType} "${BoldCyan}${ARGV}${ColourReset}")
  elseif(MessageType STREQUAL STATUS)
    LIST(REMOVE_AT ARGV 0)
    _message(${MessageType} "${BoldGreen}${ARGV}${ColourReset}")
  else()
    _message("${ARGV}")
  endif()
endfunction()

################################
# Macros
################################

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
    # SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking.
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

# Add the directories needed for main files.
ADD_SUBDIRECTORY("${CPP_DIR}/KML")
ADD_SUBDIRECTORY("${CPP_DIR}/apps")

################################
# Python
################################
OPTION(BUILD_PYTHON "Build Python" OFF)
if(BUILD_PYTHON)
    MESSAGE(STATUS "Building Cython Modules")
    # Find the python interpreter, SET the PYTHON_EXECUTABLE variable
    if(CMAKE_VERSION VERSION_LESS 3.12)
        # this logic is deprecated in CMake after 3.12
        FIND_PACKAGE(PythonInterp3 REQUIRED)
    else()
        # This will preferentially find Python3 instead of Python2.
        # And also works with Virtual Environments.
        SET(Python3_FIND_STRATEGY VERSION)
        SET(Python3_FIND_VIRTUALENV FIRST)
        FIND_PACKAGE(Python3 COMPONENTS Interpreter)
        SET(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
    endif()

    SET(NUM_THREADS 10) # Default to building with 10 threads.
    SET(BUILD_DIR ${CMAKE_BINARY_DIR})
    SET(PACK_DIR ${CMAKE_BINARY_DIR}/tools/packages)
    SET(OUTPUT "${BUILD_DIR}/KML/python_timestamp")
    FILE(MAKE_DIRECTORY ${BUILD_DIR}/KML)

    ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT}
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/setup.py
            sdist --dist-dir=${PACK_DIR}
            egg_info --egg-base=${BUILD_DIR}/KML
            build --build-base=${BUILD_DIR}/build --build-lib=${BUILD_DIR}/build --build-temp=${BUILD_DIR}/KML
            build_ext --build-lib=${BUILD_DIR} --build-temp=${BUILD_DIR}/KML -j${NUM_THREADS}
            bdist_wheel --bdist-dir=${BUILD_DIR}/build --dist-dir=${PACK_DIR}
        COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
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
# C++ Code Coverage
################################
OPTION(BUILD_COVERAGE "Create C++ Coverage" OFF)
if(BUILD_COVERAGE)
	# if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    MESSAGE(STATUS "Building Coverage")
    SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
	INCLUDE(CodeCoverage)
    append_coverage_compiler_flags()
	SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
	SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    setup_target_for_coverage_gcovr_html(
        NAME coverage EXECUTABLE ctest
        --schedule-random -j 4 --test-dir tools/cpp/tests
        EXCLUDE "build/*" "*main.cc*"
        )
    # setup_target_for_coverage_gcovr_xml(${PROJECT_NAME}_coverage NAME coverage)
endif(BUILD_COVERAGE)

################################
# C++ Testing
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
    ADD_SUBDIRECTORY("${CPP_DIR}/tests")
endif(BUILD_TESTING)

################################################################################
# Documentation
################################################################################
OPTION(BUILD_DOCUMENTATION "Build Documentation" OFF)
if(BUILD_DOCUMENTATION)
    ADD_SUBDIRECTORY("docs")
endif(BUILD_DOCUMENTATION)
