set(ALGERNON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/algernon)

set(ALGERNON_MESH_SOURCES
  ${ALGERNON_SOURCE_DIR}/mesh/SDF/SDF.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/face_indices.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/mesh.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/wavefront_loader.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/khronos_loader.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/core/mesh_tools.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/sphere.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/plane.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/polyhedron.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/polygon.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/triangle.cpp
  ${ALGERNON_SOURCE_DIR}/mesh/shapes/segment.cpp
)

set(ALGERNON_ALGORITHMS_SOURCES
  ${ALGERNON_SOURCE_DIR}/algorithms/conway/conway.cpp
  ${ALGERNON_SOURCE_DIR}/algorithms/marching_cubes/marching_cubes.cpp
  ${ALGERNON_SOURCE_DIR}/algorithms/marching_cubes/marching_cubes_tables.cpp
  ${ALGERNON_SOURCE_DIR}/algorithms/laplacian_smoothing/laplacian_smoothing.cpp
  ${ALGERNON_SOURCE_DIR}/algorithms/subdivision/catmull_clark.cpp
  ${ALGERNON_SOURCE_DIR}/algorithms/triangulation/delaunay.cpp
)

set(ALGERNON_GEOMETRY_SOURCES
  ${ALGERNON_SOURCE_DIR}/geometry/geometry_element_walkers.cpp
  ${ALGERNON_SOURCE_DIR}/geometry/geometry_elements.cpp
  ${ALGERNON_SOURCE_DIR}/geometry/geometry_builder.cpp
  ${ALGERNON_SOURCE_DIR}/geometry/geometry_mutation.cpp
  ${ALGERNON_SOURCE_DIR}/geometry/geometry_compression.cpp
  ${ALGERNON_SOURCE_DIR}/geometry/geometry.cpp
)

set(ALGERNON_SOURCES
  ${ALGERNON_MESH_SOURCES}
  ${ALGERNON_ALGORITHMS_SOURCES}
  ${ALGERNON_GEOMETRY_SOURCES}
  ${ALGERNON_SOURCE_DIR}/core/core.cpp
  ${ALGERNON_SOURCE_DIR}/core/core_types.cpp
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
  fastgltf
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
  GLM_ENABLE_EXPERIMENTAL
)