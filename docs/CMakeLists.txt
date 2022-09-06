# Doxygen documentation of main library
MESSAGE(STATUS "Building Documentation")

# FIND_PACKAGE(Doxygen REQUIRED OPTIONAL_COMPONENTS dot)
# if(DOXYGEN_DOT_EXECUTABLE)
#   SET(DOXYGEN_HAVE_DOT YES)
# else()
#   SET(DOXYGEN_HAVE_DOT NO)
# endif(DOXYGEN_DOT_EXECUTABLE)

# # Set variables for shorthand reference
# SET(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/KML)
# SET(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
# SET(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
# SET(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
# SET(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}Doxyfile)

# # Build the Doxygen documentation that will be used with sphinx
# file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
# CONFIGURE_FILE(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
# ADD_CUSTOM_COMMAND(
#   OUTPUT ${DOXYGEN_INDEX_FILE}
#   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#   DEPENDS
#     ${PROJECT_SOURCE_DIR}/README.md
#     ${DOXYGEN_IN}
#     ${DOXYGEN_OUT}
#   COMMENT "Building doxygen documentation for ${PROJECT_NAME}"
# )

# ADD_CUSTOM_TARGET(docs ALL
#   DEPENDS
#     ${DOXYGEN_INDEX_FILE}
# )

FIND_PACKAGE(Doxygen REQUIRED)
FIND_PACKAGE(Sphinx REQUIRED)

FILE(COPY ${CMAKE_SOURCE_DIR}/README.rst DESTINATION ${CMAKE_BINARY_DIR})
FILE(COPY source DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY Doxyfile.in DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY "images/HQ 01-03-resized.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

ADD_CUSTOM_TARGET(documenation ALL COMMAND make html
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/source
    COMMENT "Building Sphinx Documentation"
    DEPENDS python_package
)

# SET(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/KML)
# SET(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/source/_build)
# SET(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
# SET(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
# SET(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# # Replace variables inside @@ with the current values
# CONFIGURE_FILE(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# # Doxygen won't create this for us
# FILE(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

# # Only regenerate Doxygen when the Doxyfile or public headers change
# ADD_CUSTOM_COMMAND(
#     OUTPUT ${DOXYGEN_INDEX_FILE}
#     DEPENDS ${HEADERS}
#     COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
#     # MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
#     COMMENT "Generating C++ docs for ${PROJECT_NAME}"
#     VERBATIM
# )

# # Nice named target so we can run the job easily
# ADD_CUSTOM_TARGET(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

# SET(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/source)
# SET(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR})
# SET(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

# SET(OUTPUT "${CMAKE_BINARY_DIR}/docs")
# ADD_CUSTOM_COMMAND(OUTPUT ${OUTPUT}
#     COMMAND ${PYTHON_EXECUTABLE} -m sphinx-autodoc -f -o
#         ${CMAKE_CURRENT_BINARY_DIR}
#         ${DOXYGEN_INPUT_DIR}
#     COMMENT "Building Cython Documentation"
# )

# # Nice named target so we can run the job easily
# ADD_CUSTOM_TARGET(cython_doc ALL DEPENDS ${OUTPUT})

# # Only regenerate Sphinx when:
# # - Doxygen has rerun
# # - Our doc files have been updated
# # - The Sphinx config has been updated
# ADD_CUSTOM_COMMAND(
#     OUTPUT ${SPHINX_INDEX_FILE}
#     COMMAND
#       ${SPHINX_EXECUTABLE} -q -b html
#       -Dbreathe_projects.KML=${DOXYGEN_OUTPUT_DIR}/xml
#     ${SPHINX_SOURCE} ${SPHINX_BUILD}
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#     DEPENDS
#       ${CMAKE_CURRENT_SOURCE_DIR}/source/index.rst
#       ${DOXYGEN_INDEX_FILE}
#     MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
#     COMMENT "Generating documentation with Sphinx"
# )
# ADD_CUSTOM_TARGET(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})

# # Add an install target to install the docs
# INCLUDE(GNUInstallDirs)
# INSTALL(DIRECTORY ${SPHINX_BUILD}
#     DESTINATION ${CMAKE_INSTALL_DOCDIR}
# )
