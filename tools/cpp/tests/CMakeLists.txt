MESSAGE(STATUS "Adding C++ tests")
SET(BINARY ${CMAKE_PROJECT_NAME}_test)

# Find the test sources
FILE(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.cc)

# For Windows: Prevent overriding the parent project's compiler/linker settings
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

ADD_EXECUTABLE(${BINARY} ${TEST_SOURCES} ${SOURCES})

ADD_TEST(NAME ${BINARY} COMMAND ${BINARY})

# TARGET_LINK_LIBRARIES(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
TARGET_LINK_LIBRARIES(${BINARY} PRIVATE ${CMAKE_PROJECT_NAME}_lib gtest)
