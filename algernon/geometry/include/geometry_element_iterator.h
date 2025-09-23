#ifndef ALGERNON_GEOMETRY_ELEMENT_ITERATOR_H
#define ALGERNON_GEOMETRY_ELEMENT_ITERATOR_H

namespace Algernon {

template <typename WALKER> class GeometryIterator {
public:
  using return_type = typename WALKER::return_type;
  using element_type = typename WALKER::element_type;

  GeometryIterator(element_type element) : walker_(element) {
  }

  bool operator==(const GeometryIterator<WALKER> &rhs) const {
    return (is_active_ == true) && (walker_.current_element_ == rhs.walker_.current_element_);
  }

  auto &operator++() {
    walker_.Advance();
    is_active_ = true;
    return *this;
  }

  return_type operator*() const {
    return walker_.GetCurrent();
  }

  auto &begin() {
    is_active_ = !walker_.current_element_.IsValid();
    return *this;
  }

  auto &end() {
    is_active_ = true;
    return *this;
  }

private:
  WALKER walker_;
  bool is_active_ = true;
};

} // namespace Algernon

#endif // ALGERNON_GEOMETRY_ELEMENT_ITERATOR_H