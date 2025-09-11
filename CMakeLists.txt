cmake_minimum_required(VERSION 3.25)

project(Algernon LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

include(cmake/libraries.cmake)
include(cmake/clang_format.cmake)

FetchContent_MakeAvailable(
  glm
  tinyobjloader
)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API 1)

add_subdirectory(algernon)

if(${PROJECT_IS_TOP_LEVEL})

  add_clang_format_target(format "build")

  add_subdirectory(examples)

  add_subdirectory(tests)

endif()



