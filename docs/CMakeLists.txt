# Doxygen documentation of main library
MESSAGE(STATUS "Building Documentation")

# Look for an executable called sphinx-build
FIND_PROGRAM(SPHINX_EXECUTABLE
             NAMES sphinx-build
             DOC "Path to sphinx-build executable")

INCLUDE(FindPackageHandleStandardArgs)

# Handle standard arguments to find_package like REQUIRED and QUIET
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    Sphinx
    "Failed to find sphinx-build executable"
    SPHINX_EXECUTABLE)

FIND_PACKAGE(Doxygen REQUIRED)
FIND_PACKAGE(Sphinx REQUIRED)

# Copy rst files like LICENSE/README to build.
FILE(GLOB RST_FILES ${PROJECT_SOURCE_DIR}/*.rst)
foreach(rst ${RST_FILES})
	FILE(COPY "${rst}" DESTINATION ${CMAKE_BINARY_DIR})
endforeach()

FILE(COPY source DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
FILE(COPY "images/HQ 01-03-resized.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

# Would a symbolic link be better than just copying?
FILE(COPY ${CMAKE_SOURCE_DIR}/tools/python/kml/notebooks DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/source)

# Create doxygen output directory.
FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/source/_build/doxygen)

ADD_CUSTOM_TARGET(documenation ALL COMMAND make html
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/source
    COMMENT "Building Sphinx Documentation"
    DEPENDS python_package
)
