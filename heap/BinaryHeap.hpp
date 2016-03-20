#ifndef HEAP_BINARY_HEAP_HPP
#define HEAP_BINARY_HEAP_HPP

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>


namespace heap
{
    template <typename T, typename Comparator>
    class BinaryHeap
    {
      public:

        explicit BinaryHeap(const size_t iSize, const Comparator& iComparator)
            : _comparator(iComparator),
              _elementCount(0),
              _elements(iSize + 1)
        {
            if (iSize == 0)
            {
                throw std::runtime_error("Attempt to create a heap of zero elements");
            }
        }

        template <typename RandomAccessIterator>
        explicit BinaryHeap(RandomAccessIterator first, RandomAccessIterator last, const Comparator& iComparator)
            : BinaryHeap(distance(first, last), iComparator)
        {
            while (first != last)
            {
                insert(*first);
                ++first;
            }
        }

        // TODO: Make it pure virtual.
        virtual ~BinaryHeap()
        {
        }

        virtual void insert(const T& iElement)
        {
            if (_elementCount == _elements.size()- 1)
            {
                throw std::runtime_error("Attemp to insert in a full heap");
            }
            _elements[++_elementCount] = iElement;
            swim(_elementCount);
        }

        virtual bool isEmpty() const
        {
            return _elementCount == 0;
        }

        virtual size_t size() const
        {
            return _elementCount;
        }


      protected:

        /* It extracts the root, moves the last element in the root position and calls the top-down reheapify. */
        T deleteRoot()
        {
            if (_elementCount == 0)
            {
                throw std::runtime_error("Attemp to delete an element from an empty heap");
            }

            T root = move(_elements[1]);
            exchange(1, _elementCount--);
            sink(1);
            return root;
        }

        const T& getRoot() const
        {
            if (_elementCount == 0)
            {
                throw std::runtime_error("Attemp to get an element from an empty heap");
            }

            return _elements[1];
        }

        void exchange(const size_t iFirstIndex, const size_t iSecondIndex)
        {
            T temporary = move(_elements[iFirstIndex]);
            _elements[iFirstIndex] = move(_elements[iSecondIndex]);
            _elements[iSecondIndex] = move(temporary);
        }

        /** It represents the top-down reheapify. */
        void sink(const size_t iElementIndex)
        {
            bool isSinkDone = false;
            size_t elementIndex = iElementIndex;
            while (2 * elementIndex <= _elementCount && !isSinkDone)
            {
                size_t childIndex = 2 * elementIndex;
                // Checking which of the 2 children has to be compared with the parent.
                if (childIndex < _elementCount && _comparator(_elements[childIndex], _elements[childIndex + 1]))
                {
                    ++childIndex;
                }
                if (_comparator(_elements[elementIndex], _elements[childIndex]))
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

        /** It represents the bottom-up reheapify. */
        void swim(const size_t iElementIndex)
        {
            size_t elementIndex = iElementIndex;
            while (elementIndex > 1 && _comparator(_elements[elementIndex / 2], _elements[elementIndex]))
            {
                // If the inequality comparison between the child at elementIndex and the parent at elementIndex / 2
                // is satisfied, the child is swapped with the parent, and the former goes up in the hierarchy.
                exchange(elementIndex / 2, elementIndex);
                elementIndex = elementIndex / 2;
            }
        }

        Comparator _comparator;
        size_t _elementCount;
        std::vector<T> _elements;

    };

}

#endif