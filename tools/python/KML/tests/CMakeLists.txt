# Copy all of the test_*.py files.
FILE(GLOB_RECURSE PY_TEST_SOURCES LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/*.py)
foreach (filename ${PY_TEST_SOURCES})
	string(REPLACE "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" target ${filename})
    message(STATUS "Copying ${filename} to ${target}")
    configure_file("${filename}" "${target}" COPYONLY)
endforeach (filename)
