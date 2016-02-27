#ifndef HEAP_BINARY_HEAP_HPP
#define HEAP_BINARY_HEAP_HPP

#include <cstddef>
#include <vector>

namespace heap
{
    template <typename T, typename Comparator>
    class BinaryHeap
    {
      public:
        explicit BinaryHeap(const size_t iSize, const Comparator& iComparator);

        void insert(const T& iElement);
        bool isEmpty() const;

        size_t size() const;

      protected:
        T deleteRoot();
        const T& getRoot() const;

        void exchange(const size_t iFirstIndex, const size_t iSecondIndex);
        void swim(const size_t iElementIndex);

        Comparator _comparator;
        size_t _elementCount;
        std::vector<T> _elements;

    };
}

#endif