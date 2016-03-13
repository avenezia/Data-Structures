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
    BinaryHeap<T, Comparator>::~BinaryHeap()
    {
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
        size_t elementIndex = iElementIndex;
        while (2 * elementIndex <= _elementCount && !isSinkDone)
        {
            size_t childIndex = 2 * elementIndex;
            // Checking which of the 2 children has to be compared with the parent.
            if (childIndex < _elementCount && _comparator(childIndex, childIndex + 1))
            {
                ++childIndex;
            }
            if (_comparator(elementIndex, childIndex))
            {
                // If the inequality comparison between the parent at elementIndex and the child at childIndex
                // is satisfied, the parent is swapped with the child, and the former goes down in the hierarchy.
                exchange(elementIndex, childIndex);
                elementIndex = childIndex;
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
        size_t elementIndex = iElementIndex;
        while (elementIndex > 1 && _comparator(elementIndex / 2, elementIndex))
        {
            // If the inequality comparison between the child at elementIndex and the parent at elementIndex / 2
            // is satisfied, the child is swapped with the parent, and the former goes up in the hierarchy.
            exchange(elementIndex / 2, elementIndex);
            elementIndex = elementIndex / 2;
        }
    }

    template <typename T>
    MaxHeap<T>::MaxHeap(const size_t iSize)
        : BinaryHeap<T, std::less<T>>(iSize, std::less<T>())
    {
    }

    template <typename T>
    template <typename RandomAccessIterator>
    MaxHeap<T>::MaxHeap(RandomAccessIterator first, RandomAccessIterator last)
        : BinaryHeap<T, std::less<T>>(first, last, std::less<T>())
    {
    }

    template <typename T>
    MaxHeap<T>::~MaxHeap()
    {
    }

    template <typename T>
    T MaxHeap<T>::deleteMax() 
    {
        return BinaryHeap<T, std::less<T>>::deleteRoot();
    }

    template <typename T>
    const T& MaxHeap<T>::getMax() const
    {
        return BinaryHeap<T, std::less<T>>::getRoot();
    }

    //template <typename Comparator> class BinaryHeap<int, Comparator>;
    template class MaxHeap<int>;
}
