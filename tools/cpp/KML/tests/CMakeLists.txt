SET(BINARY ${CMAKE_PROJECT_NAME}_test)

FILE(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.h *.cc)

# SET(SOURCES ${TEST_SOURCES})

# For Windows: Prevent overriding the parent project's compiler/linker settings
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

ADD_EXECUTABLE(${BINARY} ${TEST_SOURCES})

ADD_TEST(NAME ${BINARY} COMMAND ${BINARY})

TARGET_LINK_LIBRARIES(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)
