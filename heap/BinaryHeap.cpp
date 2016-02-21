#include "BinaryHeap.hpp"

namespace heap
{
    template <typename T, typename Comparator>
    BinaryHeap::BinaryHeap(const Comparator& iComparator)
        : _comparator(iComparator),
          _elementNumber(0)
    {

    }

    template <typename T, typename Comparator>
    void BinaryHeap::insert(const T& iElement)
    {
        _elements.push_back(iElement);
    }

    template <typename T, typename Comparator>
    bool BinaryHeap::isEmpty() const
    {
        return _elementNumber == 0;
    }   
}

#endif