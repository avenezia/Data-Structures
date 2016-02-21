#ifndef HEAP_BINARY_HEAP_HPP
#define HEAP_BINARY_HEAP_HPP

#include <vector>

namespace heap
{
    template <typename T, typename Comparator>
    class BinaryHeap
    {
      public:
        explicit BinaryHeap(const Comparator& iComparator);

        void insert(const T& iElement);
        bool isEmpty() const;

      protected:
        Comparator _comparator;
        size_t _elementNumber;
        std::vector<T> _elements;

    };
}

#endif