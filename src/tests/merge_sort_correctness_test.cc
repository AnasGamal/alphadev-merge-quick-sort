#include "../algorithms/merge_sort_variants.h"
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

TEST(MergeSortCorrectnessTest, Classic) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Classic Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSortClassic, size);
    }
}

TEST(MergeSortCorrectnessTest, Network3To8) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3-8 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSort3To8, size);
    }
}

TEST(MergeSortCorrectnessTest, Network3) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSort3, size);
    }
}

TEST(MergeSortCorrectnessTest, Network3To4) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3-4 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSort3To4, size);
    }
}

TEST(MergeSortCorrectnessTest, Network3To5) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Network 3-5 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSort3To5, size);
    }
}

TEST(MergeSortCorrectnessTest, Even) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Even Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSortEven, size);
    }
}

TEST(MergeSortCorrectnessTest, Odd) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Odd Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSortOdd, size);
    }
}

TEST(MergeSortCorrectnessTest, PowerOf2) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("Power of 2 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSortPowerOf2, size);
    }
}

TEST(MergeSortCorrectnessTest, VarSort3) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("VarSort3 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSortVarSort3, size);
    }
}

TEST(MergeSortCorrectnessTest, VarSort4) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("VarSort4 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSortVarSort4, size);
    }
}

TEST(MergeSortCorrectnessTest, VarSort5) {
    for (int size : {10, 100, 1000, 10000}) {
        SCOPED_TRACE("VarSort5 Merge Sort, size=" + std::to_string(size));
        testSortCorrectness(mergeSortVarSort5, size);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
