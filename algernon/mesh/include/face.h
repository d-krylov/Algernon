#ifndef ALGERNON_FACE_H
#define ALGERNON_FACE_H

#include "algernon/core/include/core_types.h"
#include <vector>
#include <span>
#include <ranges>
#include <functional>

namespace Algernon {

class Face {
public:
  Face(std::span<const IndexType> indices);

  Face(std::initializer_list<IndexType> indices);

  Face(IndexType i0, IndexType i1, IndexType i2);

  auto size() const;

  auto begin();

  auto begin() const;

  auto end();

  auto end() const;

  auto GetEdgeView() const;

  auto GetTriangleView() const;

  auto GetTriangleFaceView() const;

  Index2 GetEdge(IndexType index) const;

  Index3 GetTriangle(IndexType index) const;

  Face GetTriangleFace(IndexType index) const;

private:
  std::vector<IndexType> indices_;
};

} // namespace Algernon

#include "face.ipp"

#endif // ALGERNON_FACE_H