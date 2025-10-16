#include "algernon/geometry/include/geometry.h"
#include "algernon/geometry/include/geometry_element_walkers.h"
#include <print>

namespace Algernon {

bool Geometry::Flip(const Edge &edge) {
  auto ha1 = edge.GetHalfedge();
  auto ha2 = ha1.GetNextHalfedge();
  auto ha3 = ha2.GetNextHalfedge();

  auto hb1 = ha1.GetTwinHalfedge();
  auto hb2 = hb1.GetNextHalfedge();
  auto hb3 = hb2.GetNextHalfedge();

  auto va = ha1.GetSourceVertex();
  auto vb = hb1.GetSourceVertex();
  auto vc = ha3.GetSourceVertex();
  auto vd = hb3.GetSourceVertex();

  auto fa = ha1.GetFace();
  auto fb = hb1.GetFace();

  if (va.GetHalfedge() == ha1) {
    vertices_[va.GetIndex()] = hb2.GetIndex();
  }

  if (vb.GetHalfedge() == hb1) {
    vertices_[vb.GetIndex()] = ha2.GetIndex();
  }

  faces_[fa.GetIndex()] = ha1.GetIndex();
  faces_[fb.GetIndex()] = hb1.GetIndex();

  halfedges_[ha1.GetIndex()].next_ = hb3.GetIndex();
  halfedges_[hb3.GetIndex()].next_ = ha2.GetIndex();
  halfedges_[ha2.GetIndex()].next_ = ha1.GetIndex();
  halfedges_[hb1.GetIndex()].next_ = ha3.GetIndex();
  halfedges_[ha3.GetIndex()].next_ = hb2.GetIndex();
  halfedges_[hb2.GetIndex()].next_ = hb1.GetIndex();

  halfedges_[ha1.GetIndex()].vertex_ = vc.GetIndex();
  halfedges_[hb1.GetIndex()].vertex_ = vd.GetIndex();

  halfedges_[ha3.GetIndex()].face_ = fb.GetIndex();
  halfedges_[hb3.GetIndex()].face_ = fa.GetIndex();

  return true;
}

void Geometry::InsertVertexInFace(Face face) {
  auto new_vertex = CreateVertex();
  auto face_degree = face.GetDegree();

  std::vector<Face> internal_faces;
  std::vector<Halfedge> input_halfedges(face_degree);
  std::vector<Halfedge> output_halfedges(face_degree);
  std::vector<Halfedge> face_halfedges;

  for (auto i = 0; i < face_degree; i++) {
    if (i == 0) {
      internal_faces.emplace_back(face);
    } else {
      internal_faces.emplace_back(CreateFace());
    }

    input_halfedges[i] = CreateEdge();
    output_halfedges[(i + 1) % face_degree] = input_halfedges[i].GetTwinHalfedge();
  }

  for (auto halfedge : face.GetAdjacentHalfedges()) {
    face_halfedges.emplace_back(halfedge);
  }

  for (auto i = 0; i < face_degree; i++) {
    faces_[internal_faces[i].GetIndex()] = face_halfedges[i].GetIndex();

    halfedges_[input_halfedges[i].GetIndex()].next_ = output_halfedges[i].GetIndex();
    halfedges_[input_halfedges[i].GetIndex()].vertex_ = face_halfedges[i].GetTargetVertex().GetIndex();
    halfedges_[input_halfedges[i].GetIndex()].face_ = internal_faces[i].GetIndex();

    halfedges_[output_halfedges[i].GetIndex()].next_ = face_halfedges[i].GetIndex();
    halfedges_[output_halfedges[i].GetIndex()].vertex_ = new_vertex.GetIndex();
    halfedges_[output_halfedges[i].GetIndex()].face_ = internal_faces[i].GetIndex();

    halfedges_[face_halfedges[i].GetIndex()].next_ = input_halfedges[i].GetIndex();
    halfedges_[face_halfedges[i].GetIndex()].face_ = internal_faces[i].GetIndex();
  }

  vertices_[new_vertex.GetIndex()] = output_halfedges[0].GetIndex();
}

void Geometry::InsertEdgeInFace(Halfedge he1, Halfedge he2) {
  auto new_edge = CreateEdge();

  auto face_0 = he1.GetFace();
  auto face_1 = CreateFace();

  faces_[face_0.GetIndex()] = new_edge.GetIndex();
  faces_[face_1.GetIndex()] = new_edge.GetTwinHalfedge().GetIndex();

  halfedges_[new_edge.GetIndex()].next_ = he2.GetIndex();
  halfedges_[new_edge.GetIndex()].vertex_ = he1.GetSourceVertex().GetIndex();
  halfedges_[new_edge.GetIndex()].face_ = face_0.GetIndex();

  halfedges_[new_edge.GetTwinHalfedge().GetIndex()].next_ = he1.GetIndex();
  halfedges_[new_edge.GetTwinHalfedge().GetIndex()].vertex_ = he2.GetSourceVertex().GetIndex();
  halfedges_[new_edge.GetTwinHalfedge().GetIndex()].face_ = face_1.GetIndex();

  halfedges_[he1.GetPreviousOutgoingNeighbor().GetIndex()].next_ = new_edge.GetIndex();
  halfedges_[he2.GetPreviousOutgoingNeighbor().GetIndex()].next_ = new_edge.GetTwinHalfedge().GetIndex();

  auto current_he = he1;

  while (current_he != new_edge.GetTwinHalfedge()) {
    halfedges_[current_he.GetIndex()].face_ = face_1.GetIndex();
    current_he = current_he.GetNextHalfedge();
  }
}

void Geometry::InsertVertexOnEdge(Edge edge) {
  auto new_vertex = CreateVertex();
  auto new_edge = CreateEdge();

  vertices_[new_vertex.GetIndex()] = edge.GetHalfedge().GetIndex();

  halfedges_[new_edge.GetIndex()].next_ = edge.GetHalfedge().GetIndex();
  halfedges_[new_edge.GetIndex()].vertex_ = edge.GetSourceVertex().GetIndex();
  halfedges_[new_edge.GetIndex()].face_ = edge.GetHalfedge().GetFace().GetIndex();

  halfedges_[new_edge.GetTwinHalfedge().GetIndex()].next_ = edge.GetHalfedge().GetTwinHalfedge().GetNextHalfedge().GetIndex();
  halfedges_[new_edge.GetTwinHalfedge().GetIndex()].vertex_ = new_vertex.GetIndex();
  halfedges_[new_edge.GetTwinHalfedge().GetIndex()].face_ = edge.GetHalfedge().GetTwinHalfedge().GetFace().GetIndex();

  halfedges_[edge.GetHalfedge().GetTwinHalfedge().GetIndex()].next_ = new_edge.GetTwinHalfedge().GetIndex();
  halfedges_[edge.GetHalfedge().GetPreviousHalfedge().GetIndex()].next_ = new_edge.GetIndex();
  halfedges_[edge.GetHalfedge().GetIndex()].vertex_ = new_vertex.GetIndex();

  if (edge.GetHalfedge().GetSourceVertex().GetHalfedge() == edge.GetHalfedge()) {
    vertices_[edge.GetHalfedge().GetSourceVertex().GetIndex()] = new_edge.GetIndex();
  }
}

void Geometry::InsertVertexOnEdgeTriangular(Edge edge) {
  InsertVertexOnEdge(edge);

  auto he1 = edge.GetHalfedge();
  auto he2 = he1.GetNextHalfedge().GetNextHalfedge();
  InsertEdgeInFace(he1, he2);

  auto hea = he1.GetNextOutgoingNeighbor();
  auto heb = hea.GetNextHalfedge().GetNextHalfedge();
  InsertEdgeInFace(hea, heb);
}

void Geometry::RemoveEdge(Edge edge) {
  auto he0 = edge.GetHalfedge();
  auto he1 = edge.GetHalfedge().GetTwinHalfedge();

  auto v0 = he0.GetTargetVertex();
  auto v1 = he1.GetTargetVertex();

  auto f0 = he0.GetFace();
  auto f1 = he1.GetFace();

  auto he0_previous = he0.GetPreviousHalfedge();
  auto he1_previous = he1.GetPreviousHalfedge();

  auto he0_next = he0.GetNextHalfedge();
  auto he1_next = he1.GetNextHalfedge();

  if (v0.GetHalfedge() == he1) {
    vertices_[v0] = he0_next;
  }

  if (v1.GetHalfedge() == he0) {
    vertices_[v1] = he1_next;
  }

  for (auto he : f0.GetAdjacentHalfedges()) {
    halfedges_[he].face_ = f1;
  }

  halfedges_[he1_previous].next_ = he0_next;
  halfedges_[he0_previous].next_ = he1_next;

  if (f1.GetHalfedge() == he1) {
    faces_[f1] = he1_next;
  }
}

void Geometry::ContractEdgeTriangular(Edge edge) {
}

void Geometry::DeleteFace(Face face) {
  for (auto halfedge : face.GetAdjacentHalfedges()) {
    halfedges_[halfedge].face_ = INVALID_INDEX;
  }

  faces_[face] = INVALID_INDEX;
}

} // namespace Algernon