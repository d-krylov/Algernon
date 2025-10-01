#ifndef ALGERNON_TRANSFORM_ITERATOR_H
#define ALGERNON_TRANSFORM_ITERATOR_H

#include "core_types.h"
#include <iterator>

namespace Algernon {

template <typename Base, typename Getter> class TransformIterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = std::invoke_result_t<Getter, const Base &, IndexType>;
  using difference_type = std::ptrdiff_t;
  using reference = value_type;
  using pointer = void;

  TransformIterator() = default;

  TransformIterator(const Base *base, std::size_t position, Getter getter) : base_(base), position_(position), getter_(getter) {
  }

  reference operator*() const {
    return (base_->*getter_)(position_);
  }

  reference operator[](difference_type n) const {
    return (base_->*getter_)(position_ + n);
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

  TransformIterator &operator--() {
    --position_;
    return *this;
  }

  TransformIterator operator--(int) {
    auto temp = *this;
    --(*this);
    return temp;
  }

  TransformIterator &operator+=(difference_type n) {
    position_ += n;
    return *this;
  }

  TransformIterator &operator-=(difference_type n) {
    position_ -= n;
    return *this;
  }

  friend TransformIterator operator+(TransformIterator it, difference_type n) {
    it += n;
    return it;
  }

  friend TransformIterator operator+(difference_type n, TransformIterator it) {
    it += n;
    return it;
  }

  friend TransformIterator operator-(TransformIterator it, difference_type n) {
    it -= n;
    return it;
  }

  friend difference_type operator-(const TransformIterator &a, const TransformIterator &b) {
    return static_cast<difference_type>(a.position_) - static_cast<difference_type>(b.position_);
  }

  bool operator==(const TransformIterator &other) const = default;

private:
  const Base *base_;
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

  auto operator[](IndexType i) const {
    return (base_->*getter_)(i);
  }

private:
  const Base *base_;
  Getter getter_;
  IndexType size_;
};

} // namespace Algernon

#endif // ALGERNON_TRANSFORM_ITERATOR_H