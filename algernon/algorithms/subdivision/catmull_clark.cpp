#include "subdivision.h"
#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include <ranges>

namespace Algernon {

Mesh CatmullClark(std::span<const Vector3f> vertices, std::span<const FaceIndices> facets) {
  Geometry geometry(facets, true);

  // return Mesh(new_vertices, new_facets);
}

} // namespace Algernon