#include "BinaryHeap.hpp"

#include <functional>

namespace heap
{

    template <typename T>
    class MinHeap : public BinaryHeap<T, std::greater<T>>
    {
      public:
        explicit MinHeap(const size_t iSize)
            : BinaryHeap<T, std::greater<T>>(iSize, std::greater<T>())
        {
        }

        template <typename RandomAccessIterator>
        explicit MinHeap(RandomAccessIterator first, RandomAccessIterator last)
            : BinaryHeap<T, std::greater<T>>(first, last, std::greater<T>())
        {
        }

        virtual ~MinHeap()
        {
        }

        T deleteMin()
        {
            return BinaryHeap<T, std::greater<T>>::deleteRoot();
        }
        
        const T& getMin() const
        {
            return BinaryHeap<T, std::greater<T>>::getRoot();
        }

    };
}