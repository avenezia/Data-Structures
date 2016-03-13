#include "BinaryHeap.hpp"

#include <functional>

namespace heap
{

    template <typename T>
    class MaxHeap : public BinaryHeap<T, std::less<T>>
    {
      public:
        explicit MaxHeap(const size_t iSize)
            : BinaryHeap<T, std::less<T>>(iSize, std::less<T>())
        {
        }

        template <typename RandomAccessIterator>
        explicit MaxHeap(RandomAccessIterator first, RandomAccessIterator last)
            : BinaryHeap<T, std::less<T>>(first, last, std::less<T>())
        {
        }

        virtual ~MaxHeap()
        {
        }

        T deleteMax()
        {
            return BinaryHeap<T, std::less<T>>::deleteRoot();
        }
        
        const T& getMax() const
        {
            return BinaryHeap<T, std::less<T>>::getRoot();
        }

    };
}