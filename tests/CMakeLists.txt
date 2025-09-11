FetchContent_MakeAvailable(googletest)

enable_testing()

set(ALGERNON_TESTS_SOURCES
  ${PROJECT_SOURCE_DIR}/tests/geometry_test.cpp
  ${PROJECT_SOURCE_DIR}/tests/mesh_test.cpp
)

add_executable(Tests ${ALGERNON_TESTS_SOURCES})

target_link_libraries(Tests 
  PRIVATE gtest gtest_main Algernon  
)

add_test(NAME Tests COMMAND Tests)