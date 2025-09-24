#include "algernon/geometry/include/geometry.h"

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
    vertex_indices_[va.GetIndex()] = hb2.GetIndex();
  }

  if (vb.GetHalfedge() == hb1) {
    vertex_indices_[vb.GetIndex()] = ha2.GetIndex();
  }

  face_indices_[fa.GetIndex()] = ha1.GetIndex();
  face_indices_[fb.GetIndex()] = hb1.GetIndex();

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

} // namespace Algernon