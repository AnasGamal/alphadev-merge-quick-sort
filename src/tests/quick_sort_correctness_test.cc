#include "../algorithms/quick_sort_variants.h"
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"

bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

template <typename SortFunc>
void testSortCorrectness(SortFunc sortFunc, int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;
    }


    sortFunc(arr.data(), arr.size());

    ASSERT_TRUE(isSorted(arr)) << "Sorting failed for size " << size;
}

TEST(QuickSortCorrectnessTest, Classic) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Classic Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSortClassic, size);
    }
}

TEST(QuickSortCorrectnessTest, Network3To8) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3-8 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSort3To8, size);
    }
}

TEST(QuickSortCorrectnessTest, Network3) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSort3, size);
    }
}

TEST(QuickSortCorrectnessTest, Network3To4) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3-4 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSort3To4, size);
    }
}

TEST(QuickSortCorrectnessTest, Network3To5) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3-5 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSort3To5, size);
    }
}

TEST(QuickSortCorrectnessTest, Even) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Even Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSortEven, size);
    }
}

TEST(QuickSortCorrectnessTest, Odd) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Odd Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSortOdd, size);
    }
}

TEST(QuickSortCorrectnessTest, PowerOf2) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Power of 2 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSortPowerOf2, size);
    }
}

TEST(QuickSortCorrectnessTest, VarSort3) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("VarSort3 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSortVarSort3, size);
    }
}

TEST(QuickSortCorrectnessTest, VarSort4) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("VarSort4 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSortVarSort4, size);
    }
}

TEST(QuickSortCorrectnessTest, VarSort5) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("VarSort5 Quick Sort, size=" + std::to_string(size));
        testSortCorrectness(quickSortVarSort5, size);
    }
}

TEST(QuickSortCorrectnessTest, EdgeCases) {
    std::vector<int> empty;
    quickSortClassic(empty.data(), empty.size());
    ASSERT_TRUE(empty.empty());

    std::vector<int> single = {1};
    quickSortClassic(single.data(), single.size());
    ASSERT_EQ(single[0], 1);

    std::vector<int> sorted = {1, 2, 3, 4, 5};
    quickSortClassic(sorted.data(), sorted.size());
    ASSERT_TRUE(isSorted(sorted));

    std::vector<int> reverse = {5, 4, 3, 2, 1};
    quickSortClassic(reverse.data(), reverse.size());
    ASSERT_TRUE(isSorted(reverse));

    std::vector<int> same(5, 1);
    quickSortClassic(same.data(), same.size());
    ASSERT_TRUE(isSorted(same));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}