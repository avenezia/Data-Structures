#include "BinaryHeap.hpp"

namespace heap
{
    template <typename T, typename Comparator>
    BinaryHeap<T, Comparator>::BinaryHeap(const Comparator& iComparator)
        : _comparator(iComparator),
          _elementNumber(0)
    {

    }

    template <typename T, typename Comparator>
    void BinaryHeap<T, Comparator>::insert(const T& iElement)
    {
        _elements.push_back(iElement);
    }

    template <typename T, typename Comparator>
    bool BinaryHeap<T, Comparator>::isEmpty() const
    {
        return _elementNumber == 0;
    }

    template <typename T, typename Comparator>
    size_t BinaryHeap<T, Comparator>::size() const
    {
        return _elementNumber;
    }
}