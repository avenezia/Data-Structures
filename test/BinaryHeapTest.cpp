#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

#include "gtest/gtest.h"

#include "MaxHeap.hpp"

namespace heap
{
    TEST (BinaryHeapTest, testConstructor_zeroElements)
    {
        ASSERT_THROW(MaxHeap<int> heap(0), std::runtime_error);
    }

    TEST (BinaryHeapTest, testConstructor_rangeOfZeroElements)
    {
        vector<int> values;
        ASSERT_THROW(MaxHeap<int> heap(values.begin(), values.end()), std::runtime_error);
    }

    TEST (BinaryHeapTest, testDeleteMax)
    {
        vector<int> values = {-18, 9, 30, -23, 43};
        MaxHeap<int> heap(values.begin(), values.end());
        vector<int> expectedValues = {43, 30, 9, -18, -23};
        size_t initialSize = heap.size();
        for (size_t index = 0; index < initialSize; ++index)
        {
            int max = heap.deleteMax();
            ASSERT_EQ(expectedValues[index], max);
            ASSERT_EQ(initialSize - index - 1, heap.size());
        }
    }

    TEST (BinaryHeapTest, testDeleteMax_emptyHeap)
    {
        MaxHeap<int> heap(10);
        ASSERT_THROW(heap.deleteMax(), std::runtime_error);
    }

    TEST (BinaryHeapTest, testGetMax)
    {
        vector<int> values = {-1, 2, 8};
        MaxHeap<int> heap(values.begin(), values.end());
        vector<int> expectedValues = {8, 2, -1};
        for (size_t index = 0; index < expectedValues.size(); ++index)
        {
            ASSERT_EQ(expectedValues[index], heap.getMax());
            heap.deleteMax();
        }
    }

    TEST (BinaryHeapTest, testGetMax_emptyHeap)
    {
        MaxHeap<int> heap(10);
        ASSERT_THROW(heap.getMax(), std::runtime_error);
    }

    TEST (BinaryHeapTest, testInsert_emptyHeap)
    {
        vector<int> values = {30, 40};
        MaxHeap<int> heap(values.begin(), values.end());
        ASSERT_THROW(heap.insert(90), std::runtime_error);
    }

    TEST (BinaryHeapTest, testIsEmpty)
    {
        MaxHeap<int> heap(10);
        ASSERT_TRUE(heap.isEmpty());
    }

    TEST (BinaryHeapTest, testSize)
    {
        MaxHeap<int> heap(5);
        heap.insert(3);
        heap.insert(4);
        ASSERT_EQ(2, heap.size());
    }

}
