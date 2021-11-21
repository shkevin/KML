# Minimum version of CMake required to build this<Plug>PeepOpenroject
cmake_minimum_required(VERSION 3.0)

################################
# Project
################################
project(KML
	VERSION 0.0.1
	DESCRIPTION "Machine Learning in CPP"
    LANGUAGES CXX)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Minimum cpp standard
SET(CMAKE_CXX_STANDARD 20)

################################
# Macros
################################
MACRO(HEADER_DIRECTORIES return_list)
	FILE(GLOB_RECURSE new_list *.h)
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

# if compiler is Clang, link libc++, otherwise, link default libstdc++
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fsanitize=signed-integer-overflow")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

# Make binaries installed in bin folder
# SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
	# the new hotness. This will preferentially find Python3 instead of Python2
	FIND_PACKAGE(Python)
	SET(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
endif()

################################
# Normal Libraries & Executables
################################
# If using microsfot visual studio.
if(MSVC)
    SET(CMAKE_USE_RELATIVE_PATHS ON CACHE INTERNAL "" FORCE)
endif()

# Disable in-source builds to prevent source tree corruption.
if("${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  MESSAGE(FATAL_ERROR "FATAL: In-source builds are not allowed.
       You should create a separate directory for build FILEs.")
endif()

# Include eigen package
FIND_PACKAGE(Eigen3 REQUIRED)
LINK_DIRECTORIES(${Eigen_INCLUDE_DIRS})

# Add cpp FILEs to build
SET(BINARY ${PROJECT_NAME})
MESSAGE(STATUS "Adding source and header files")
SET(CPP_DIR "${CMAKE_SOURCE_DIR}/tools/cpp/KML")

# Create a sources variable with a link to all cpp FILEs to compile
FILE(GLOB_RECURSE SOURCES "${CPP_DIR}/src/*.cc" "${CPP_DIR}/src/*.tcc")

# Add the directories needed.
INCLUDE_DIRECTORIES(${BINARY}
    PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
        "${CPP_DIR}/include"
        "${CPP_DIR}/src"
)

# Fake main
LIST(APPEND SOURCES "./main.cc")

# Add an executable with the above sources
ADD_EXECUTABLE(${BINARY} ${SOURCES})

# Link the eigen libraries required.
TARGET_LINK_LIBRARIES(${BINARY} ${Eigen_LIBRARIES})

################################
# Testing
################################
FIND_PACKAGE(GTest)
OPTION(BUILD_TESTING "Build gtest unit test" ON)
if (BUILD_TESTING)
	MESSAGE(STATUS "Enabled testing")
    add_library(${BINARY}_lib STATIC ${SOURCES})
	enable_testing()
    # LINK_DIRECTORIES("${CPP_DIR}/tests")
    ADD_SUBDIRECTORY("${CPP_DIR}/tests")
    ADD_SUBDIRECTORY("${CPP_DIR}/lib/googletest")
endif()

# SET(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
# SET(CPACK_PACKAGE_VERSION "${VERSION}")
# SET(CPACK_MONOLITHIC_INSTALL 1)
# include(CPack)
