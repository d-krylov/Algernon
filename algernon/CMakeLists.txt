set(ALGERNON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/algernon)

set(ALGERNON_SOURCES
  ${ALGERNON_SOURCE_DIR}/core/core.cpp
  ${ALGERNON_SOURCE_DIR}/core/core_types.cpp
  ${ALGERNON_SOURCE_DIR}/geometry/geometry_element.cpp
  ${ALGERNON_SOURCE_DIR}/geometry/geometry.cpp
  ${ALGERNON_SOURCE_DIR}/algorithms/marching_cubes/marching_cubes.cpp
  ${ALGERNON_SOURCE_DIR}/algorithms/marching_cubes/marching_cubes_tables.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/face.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/mesh.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/mesh_loader.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/mesh_tools.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/sphere.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/plane.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/polyhedron.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/polygon.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/triangle.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/segment.cpp
  ${ALGERNON_SOURCE_DIR}/mathematics/bounding_box.cpp
)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} 
  PRIVATE ${ALGERNON_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  glm::glm
  tinyobjloader
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
  GLM_ENABLE_EXPERIMENTAL
)