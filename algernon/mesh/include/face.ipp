#ifndef ALGERNON_FACE_IPP
#define ALGERNON_FACE_IPP

namespace Algernon {

inline auto Face::size() const {
  return indices_.size();
}

inline auto Face::begin() {
  return indices_.begin();
}

inline auto Face::begin() const {
  return indices_.cbegin();
}

inline auto Face::end() {
  return indices_.end();
}

inline auto Face::end() const {
  return indices_.cend();
}

inline auto Face::GetEdgeView() const {
  return std::views::iota(0u, size()) | std::views::transform(std::bind_front(&Face::GetEdge, this));
}

inline auto Face::GetTriangleView() const {
  return std::views::iota(0u, size() - 2) | std::views::transform(std::bind_front(&Face::GetTriangle, this));
}

inline auto Face::GetTriangleFaceView() const {
  return std::views::iota(0u, size() - 2) | std::views::transform(std::bind_front(&Face::GetTriangleFace, this));
}

} // namespace Algernon

#endif // ALGERNON_FACE_IPP