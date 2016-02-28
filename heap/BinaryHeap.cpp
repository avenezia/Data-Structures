#include "BinaryHeap.hpp"

#include <iterator>
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
    template <typename RandomAccessIterator>
    BinaryHeap<T, Comparator>::BinaryHeap(RandomAccessIterator first, RandomAccessIterator last, const Comparator& iComparator)
        : _comparator(iComparator),
          _elementCount(0),
          _elements(distance(first, last) + 1)
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    template <typename T, typename Comparator>
    T BinaryHeap<T, Comparator>::deleteRoot()
    {
        if (_elementCount == 0)
        {
            throw runtime_error("Attemp to delete an element from an empty heap");
        }

        T root = move(_elements[1]);
        exchange(1, _elementCount--);
        sink(1);
        return root;
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
        swim(_elementCount);
    }

    template <typename T, typename Comparator>
    bool BinaryHeap<T, Comparator>::isEmpty() const
    {
        return _elementCount == 0;
    }

    template <typename T, typename Comparator>
    void BinaryHeap<T, Comparator>::sink(const size_t iElementIndex)
    {
        bool isSinkDone = false;
        while (2 * iElementIndex <= _elementCount && !isSinkDone)
        {
            size_t childIndex = 2 * iElementIndex;
            // Checking which of the 2 children has to be compared with the parent.
            if (childIndex < _elementCount && _comparator(childIndex, childIndex + 1))
            {
                ++childIndex;
            }
            if (_comparator(iElementIndex, childIndex))
            {
                // If the inequality comparison between the parent at iElementIndex and the child at childIndex
                // is satisfied, the parent is swapped with the child, and the former goes down in the hierarchy.
                exchange(iElementIndex, childIndex);
                iElementIndex = childIndex;
            }
            else
            {
                isSinkDone = true;
            }
        }
    }

    template <typename T, typename Comparator>
    size_t BinaryHeap<T, Comparator>::size() const
    {
        return _elementCount;
    }

    template <typename T, typename Comparator>
    void BinaryHeap<T, Comparator>::swim(const size_t iElementIndex)
    {
        while (iElementIndex > 1 && _comparator(iElementIndex / 2, iElementIndex))
        {
            // If the inequality comparison between the child at iElementIndex and the parent at iElementIndex / 2
            // is satisfied, the child is swapped with the parent, and the former goes up in the hierarchy.
            exchange(iElementIndex / 2, iElementIndex);
            iElementIndex = iElementIndex / 2;
        }
    }
}
