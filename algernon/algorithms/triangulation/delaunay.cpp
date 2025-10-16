#include "triangulation.h"
#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include <queue>
#include <print>

namespace Algernon {

bool InCircle(const Vector3f &a, const Vector3f &b, const Vector3f &c, const Vector3f &d) {
  float ax = a.x - d.x;
  float ay = a.y - d.y;
  float bx = b.x - d.x;
  float by = b.y - d.y;
  float cx = c.x - d.x;
  float cy = c.y - d.y;

  float D = (ax * ax + ay * ay) * (bx * cy - cx * by) - (bx * bx + by * by) * (ax * cy - cx * ay) + (cx * cx + cy * cy) * (ax * by - bx * ay);

  return D > 0.0f;
}

Mesh GetDelauney(std::span<const Vector3f> vertices, std::span<const FaceIndices> facets) {
  Geometry geometry(facets);

  std::queue<Edge> edge_queue;

  for (auto edge : geometry.GetEdges()) {
    edge_queue.push(edge);
  }

  while (edge_queue.empty() == false) {

    auto edge = edge_queue.front();
    edge_queue.pop();

    auto he = edge.GetHalfedge();
    auto twin = he.GetTwinHalfedge();

    auto f1 = he.GetFace();
    auto f2 = twin.GetFace();

    auto a = vertices[he.GetSourceVertex().GetIndex()];
    auto b = vertices[twin.GetSourceVertex().GetIndex()];
    auto c = vertices[he.GetTargetVertex().GetIndex()];
    auto d = vertices[twin.GetTargetVertex().GetIndex()];

    if (InCircle(a, b, c, d)) {

      geometry.Flip(edge);

      for (const auto &edge : he.GetSourceVertex().GetAdjacentEdges()) {
        edge_queue.push(edge);
      }

      for (const auto &edge : twin.GetSourceVertex().GetAdjacentEdges()) {
        edge_queue.push(edge);
      }
    }
  }

  auto out_facets = geometry.GetFaceIndices();

  return Mesh(vertices, out_facets);
}

} // namespace Algernon