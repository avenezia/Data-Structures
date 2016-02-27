#include "BinaryHeap.hpp"

#include <stdexcept>
#include <utility>
using namespace std;

namespace heap
{
    template <typename T, typename Comparator>
    BinaryHeap<T, Comparator>::BinaryHeap(const size_t iSize, const Comparator& iComparator)
        : _comparator(iComparator),
          _elementCount(0),
          _elements(iSize + 1)
    {

    }

    template <typename T, typename Comparator>
    T BinaryHeap<T, Comparator>::deleteRoot()
    {
        if (_elementCount == 0)
        {
            throw runtime_error("Attemp to delete an element from an empty heap");
        }

    }

    template <typename T, typename Comparator>
    void BinaryHeap<T, Comparator>::exchange(const size_t iFirstIndex, const size_t iSecondIndex)
    {
        T temporary = move(_elements[iFirstIndex]);
        _elements[iFirstIndex] = move(_elements[iSecondIndex]);
        _elements[iSecondIndex] = move(temporary);
    }

    template <typename T, typename Comparator>
    const T& BinaryHeap<T, Comparator>::getRoot() const
    {
        if (_elementCount == 0)
        {
            throw runtime_error("Attemp to get an element from an empty heap");
        }

        return _elements[1];
    }

    template <typename T, typename Comparator>
    void BinaryHeap<T, Comparator>::insert(const T& iElement)
    {
        if (_elementCount == _elements.size()- 1)
        {
            throw runtime_error("Attemp to insert in a full heap");
        }
        _elements[++_elementCount] = iElement;
    }

    template <typename T, typename Comparator>
    bool BinaryHeap<T, Comparator>::isEmpty() const
    {
        return _elementCount == 0;
    }

    template <typename T, typename Comparator>
    size_t BinaryHeap<T, Comparator>::size() const
    {
        return _elementCount;
    }

    template <typename T, typename Comparator>
    void BinaryHeap<T, Comparator>::swim(const size_t iElementIndex)
    {
        size_t elementIndex = iElementIndex;
        while (elementIndex > 1 && _comparator(elementIndex / 2, elementIndex))
        {
            exchange(elementIndex / 2, elementIndex);
        }
    }
}
