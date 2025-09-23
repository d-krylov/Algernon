#ifndef ALGERNON_FACE_INDICES_IPP
#define ALGERNON_FACE_INDICES_IPP

namespace Algernon {

inline auto FaceIndices::size() const {
  return indices_.size();
}

inline auto FaceIndices::begin() {
  return indices_.begin();
}

inline auto FaceIndices::begin() const {
  return indices_.cbegin();
}

inline auto FaceIndices::end() {
  return indices_.end();
}

inline auto FaceIndices::end() const {
  return indices_.cend();
}

inline auto FaceIndices::GetEdgeView() const {
  return std::views::iota(0u, size()) | std::views::transform(std::bind_front(&FaceIndices::GetEdge, this));
}

inline auto FaceIndices::GetTriangleView() const {
  return std::views::iota(0u, size() - 2) | std::views::transform(std::bind_front(&FaceIndices::GetTriangle, this));
}

inline auto FaceIndices::GetTriangleFaceView() const {
  return std::views::iota(0u, size() - 2) | std::views::transform(std::bind_front(&FaceIndices::GetTriangleFace, this));
}

} // namespace Algernon

#endif // ALGERNON_FACE_INDICES_IPP