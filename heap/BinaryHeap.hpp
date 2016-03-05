#ifndef HEAP_BINARY_HEAP_HPP
#define HEAP_BINARY_HEAP_HPP

#include <cstddef>
#include <functional>
#include <vector>

namespace heap
{
    template <typename T, typename Comparator>
    class BinaryHeap
    {
      public:
        explicit BinaryHeap(const size_t iSize, const Comparator& iComparator);
        template <typename RandomAccessIterator>
        explicit BinaryHeap(RandomAccessIterator first, RandomAccessIterator last, const Comparator& iComparator);
        virtual ~BinaryHeap() = 0;

        virtual void insert(const T& iElement);
        virtual bool isEmpty() const;

        virtual size_t size() const;

      protected:
        T deleteRoot();
        const T& getRoot() const;

        void exchange(const size_t iFirstIndex, const size_t iSecondIndex);
        /** It represents the top-down reheapify. */
        void sink(const size_t iElementIndex);
        /** It represents the bottom-up reheapify. */
        void swim(const size_t iElementIndex);

        Comparator _comparator;
        size_t _elementCount;
        std::vector<T> _elements;

    };

    template <typename T>
    class MaxHeap : public BinaryHeap<T, std::less<T>>
    {
      public:
        explicit MaxHeap(const size_t iSize);
        template <typename RandomAccessIterator>
        explicit MaxHeap(RandomAccessIterator first, RandomAccessIterator last);
        ~MaxHeap();

        T deleteMax();
        const T& getMax() const;

    };
}

#endif