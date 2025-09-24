#ifndef ALGERNON_TRANSFORM_ITERATOR_H
#define ALGERNON_TRANSFORM_ITERATOR_H

#include "core_types.h"
#include <iterator>

namespace Algernon {

template <typename Base, typename Getter> class TransformIterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = std::invoke_result_t<Getter, const Base &, IndexType>;
  using difference_type = std::ptrdiff_t;

  TransformIterator() = default;

  TransformIterator(const Base *face, std::size_t position, Getter getter) : face_(face), position_(position), getter_(getter) {
  }

  value_type operator*() const {
    return (face_->*getter_)(position_);
  }

  TransformIterator &operator++() {
    ++position_;
    return *this;
  }

  TransformIterator operator++(int) {
    TransformIterator temp = *this;
    ++(*this);
    return temp;
  }

  bool operator==(const TransformIterator &other) const = default;

private:
  const Base *face_;
  std::size_t position_;
  Getter getter_;
};

template <typename Base, typename Getter> class BaseElements {
public:
  BaseElements(const Base *base, Getter getter, IndexType size) : base_(base), getter_(getter), size_(size) {
  }

  auto begin() const {
    return TransformIterator(base_, 0, getter_);
  }

  auto end() const {
    return TransformIterator(base_, size_, getter_);
  }

private:
  const Base *base_;
  Getter getter_;
  IndexType size_;
};

} // namespace Algernon

#endif // ALGERNON_TRANSFORM_ITERATOR_H