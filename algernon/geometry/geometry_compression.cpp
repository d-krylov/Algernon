#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include <print>

namespace Algernon {

template <typename T>
std::vector<T> ApplyPermutation(std::span<const T> source, std::span<const IndexType> permutation) {
  std::vector<T> out;
  out.reserve(permutation.size());
  for (const auto &index : permutation) {
    if (index != INVALID_INDEX) {
      out.emplace_back(source[index]);
    }
  }
  return out;
}

// clang-format off
template <typename T, typename... Members>
void Update(std::span<T> destination, std::span<const IndexType> map, Members... members) {
  auto update_field = [&](IndexType &value) { if (value != INVALID_INDEX) { value = map[value]; }};
  for (auto &element : destination) {
    if constexpr (std::same_as<T, Geometry::halfedge_t>) {
      (update_field(element.*members), ...);
    } else {
      update_field(element);
    }
  }
}
// clang-format on

void Geometry::CompressHalfedges() {
  std::vector<IndexType> indices_map(GetHalfedgesSize(), INVALID_INDEX);
  std::vector<IndexType> indices_new;

  for (const auto &he : GetHalfedges()) {
    if (he.IsValid()) {
      auto index = he.GetIndex();
      indices_map[index] = indices_new.size();
      indices_new.emplace_back(index);
    }
  }

  halfedges_ = ApplyPermutation<Geometry::halfedge_t>(halfedges_, indices_new);

  if (UsesImplicitTwin() == false) {
    he_edges_ = ApplyPermutation<IndexType>(he_edges_, indices_new);
    he_twins_ = ApplyPermutation<IndexType>(he_twins_, indices_new);
  }

  Update<halfedge_t>(halfedges_, indices_map, &halfedge_t::vertex_, &halfedge_t::face_, &halfedge_t::next_);

  if (UsesImplicitTwin() == false) {
    Update<IndexType>(he_edges_, indices_map);
    Update<IndexType>(he_twins_, indices_map);
  }
}

void Geometry::CompressVertices() {
  std::vector<IndexType> indices_map(GetVerticesSize(), INVALID_INDEX);
  std::vector<IndexType> indices_new;
  for (const auto &vertex : GetVertices()) {
    if (vertex.IsValid()) {
      auto index = vertex.GetIndex();
      indices_map[index] = indices_new.size();
      indices_new.emplace_back(index);
    }
  }
  vertices_ = ApplyPermutation<IndexType>(vertices_, indices_new);
  Update<halfedge_t>(halfedges_, indices_map, &halfedge_t::vertex_);
}

void Geometry::CompressFaces() {
  std::vector<IndexType> indices_map(GetFacesSize(), INVALID_INDEX);
  std::vector<IndexType> indices_new;

  for (const auto &face : GetFaces()) {
    if (face.IsValid()) {
      auto index = face.GetIndex();
      indices_map[index] = indices_new.size();
      indices_new.emplace_back(index);
    }
  }

  faces_ = ApplyPermutation<IndexType>(faces_, indices_new);
  Update<halfedge_t>(halfedges_, indices_map, &halfedge_t::face_);
}

void Geometry::CompressEdges() {
}

void Geometry::Compress() {
  CompressHalfedges();
  CompressEdges();
  CompressFaces();
  CompressVertices();
}

} // namespace Algernon