set(EXECUTABLES
  shapes
  marching_cubes
)

FetchContent_MakeAvailable(
  polyscope
)

target_compile_definitions(polyscope PUBLIC
  GLM_ENABLE_EXPERIMENTAL
)

foreach(exe ${EXECUTABLES})
  add_executable(${exe} ${CMAKE_CURRENT_SOURCE_DIR}/${exe}/${exe}.cpp)
  target_link_libraries(${exe} PRIVATE Algernon polyscope)
endforeach()