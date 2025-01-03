#include <benchmark/benchmark.h>
#include <vector>
#include <random>
#include "../algorithms/merge_sort_variants.h"
#include "../algorithms/bitonic_sort.h"
#include "../algorithms/quick_sort_variants.h"

static std::vector<int> generateRandomArray(size_t size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000000, 1000000);
    
    for(size_t i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

static std::vector<int> generateSortedArray(int size) {
    std::vector<int> arr(size);
    for(int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

static std::vector<int> generateNearlySortedArray(int size) {
    auto arr = generateSortedArray(size);
    int swaps = size * 0.05;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1);
    
    for(int i = 0; i < swaps; i++) {
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        std::swap(arr[idx1], arr[idx2]);
    }
    return arr;
}

#define BENCHMARK_MERGESORT(NAME, FUNC) \
static void BM_##NAME##_Random(benchmark::State& state) { \
    const size_t size = state.range(0); \
    for (auto _ : state) { \
        state.PauseTiming(); \
        auto arr = generateRandomArray(size); \
        state.ResumeTiming(); \
        FUNC(arr.data(), size); \
    } \
    state.SetComplexityN(state.range(0)); \
} \
\
static void BM_##NAME##_Sorted(benchmark::State& state) { \
    const size_t size = state.range(0); \
    for (auto _ : state) { \
        state.PauseTiming(); \
        auto arr = generateSortedArray(size); \
        state.ResumeTiming(); \
        FUNC(arr.data(), size); \
    } \
    state.SetComplexityN(state.range(0)); \
} \
\
static void BM_##NAME##_NearlySorted(benchmark::State& state) { \
    const size_t size = state.range(0); \
    for (auto _ : state) { \
        state.PauseTiming(); \
        auto arr = generateNearlySortedArray(size); \
        state.ResumeTiming(); \
        FUNC(arr.data(), size); \
    } \
    state.SetComplexityN(state.range(0)); \
}

#define BENCHMARK_QUICKSORT(NAME, FUNC) \
static void BM_##NAME##_Random(benchmark::State& state) { \
    const size_t size = state.range(0); \
    for (auto _ : state) { \
        state.PauseTiming(); \
        auto arr = generateRandomArray(size); \
        state.ResumeTiming(); \
        FUNC(arr.data(), size); \
    } \
    state.SetComplexityN(state.range(0)); \
} \
\
static void BM_##NAME##_Sorted(benchmark::State& state) { \
    const size_t size = state.range(0); \
    for (auto _ : state) { \
        state.PauseTiming(); \
        auto arr = generateSortedArray(size); \
        state.ResumeTiming(); \
        FUNC(arr.data(), size); \
    } \
    state.SetComplexityN(state.range(0)); \
} \
\
static void BM_##NAME##_NearlySorted(benchmark::State& state) { \
    const size_t size = state.range(0); \
    for (auto _ : state) { \
        state.PauseTiming(); \
        auto arr = generateNearlySortedArray(size); \
        state.ResumeTiming(); \
        FUNC(arr.data(), size); \
    } \
    state.SetComplexityN(state.range(0)); \
}

BENCHMARK_MERGESORT(MergeSortClassic, mergeSortClassic)
BENCHMARK_MERGESORT(MergeSort3To8, mergeSort3To8)
BENCHMARK_MERGESORT(MergeSort3, mergeSort3)
BENCHMARK_MERGESORT(MergeSort3To4, mergeSort3To4)
BENCHMARK_MERGESORT(MergeSort3To5, mergeSort3To5)
BENCHMARK_MERGESORT(MergeSortEven, mergeSortEven)
BENCHMARK_MERGESORT(MergeSortOdd, mergeSortOdd)
BENCHMARK_MERGESORT(MergeSortPowerOf2, mergeSortPowerOf2)
BENCHMARK_MERGESORT(MergeSortVarSort3, mergeSortVarSort3)
BENCHMARK_MERGESORT(MergeSortVarSort4, mergeSortVarSort4)
BENCHMARK_MERGESORT(MergeSortVarSort5, mergeSortVarSort5)

BENCHMARK_MERGESORT(QuickSortClassic, quickSortClassic)
BENCHMARK_MERGESORT(QuickSort3To8, quickSort3To8)
BENCHMARK_MERGESORT(QuickSort3, quickSort3)
BENCHMARK_MERGESORT(QuickSort3To4, quickSort3To4)
BENCHMARK_MERGESORT(QuickSort3To5, quickSort3To5)
BENCHMARK_MERGESORT(QuickSortEven, quickSortEven)
BENCHMARK_MERGESORT(QuickSortOdd, quickSortOdd)
BENCHMARK_MERGESORT(QuickSortPowerOf2, quickSortPowerOf2)
BENCHMARK_MERGESORT(QuickSortVarSort3, quickSortVarSort3)
BENCHMARK_MERGESORT(QuickSortVarSort4, quickSortVarSort4)
BENCHMARK_MERGESORT(QuickSortVarSort5, quickSortVarSort5)

#define REGISTERBENCHMARK(NAME)                                  \
    BENCHMARK(BM##NAME##Random)                                  \
        ->RangeMultiplier(2)                                     \
        ->Range(1 << 10, 1 << 20)                                \
        ->Unit(benchmark::kNanosecond)                          \
        ->UseRealTime()                                         \
        ->ReportAggregatesOnly(true);                           \
    BENCHMARK(BM##NAME##Sorted)                                  \
        ->RangeMultiplier(2)                                     \
        ->Range(1 << 10, 1 << 20)                                \
        ->Unit(benchmark::kNanosecond)                          \
        ->UseRealTime()                                         \
        ->ReportAggregatesOnly(true);                           \
    BENCHMARK(BM##NAME##_NearlySorted)                           \
        ->RangeMultiplier(2)                                     \
        ->Range(1 << 10, 1 << 20)                                \
        ->Unit(benchmark::kNanosecond)                          \
        ->UseRealTime()                                         \
        ->ReportAggregatesOnly(true);
       
REGISTER_BENCHMARK(MergeSortClassic)
REGISTER_BENCHMARK(MergeSort3To8)
REGISTER_BENCHMARK(MergeSort3)
REGISTER_BENCHMARK(MergeSort3To4)
REGISTER_BENCHMARK(MergeSort3To5)
REGISTER_BENCHMARK(MergeSortEven)
REGISTER_BENCHMARK(MergeSortOdd)
REGISTER_BENCHMARK(MergeSortPowerOf2)
REGISTER_BENCHMARK(MergeSortVarSort3)
REGISTER_BENCHMARK(MergeSortVarSort4)
REGISTER_BENCHMARK(MergeSortVarSort5)

REGISTER_BENCHMARK(QuickSortClassic)
REGISTER_BENCHMARK(QuickSort3To8)
REGISTER_BENCHMARK(QuickSort3)
REGISTER_BENCHMARK(QuickSort3To4)
REGISTER_BENCHMARK(QuickSort3To5)
REGISTER_BENCHMARK(QuickSortEven)
REGISTER_BENCHMARK(QuickSortOdd)
REGISTER_BENCHMARK(QuickSortPowerOf2)
REGISTER_BENCHMARK(QuickSortVarSort3)
REGISTER_BENCHMARK(QuickSortVarSort4)
REGISTER_BENCHMARK(QuickSortVarSort5)

BENCHMARK_MAIN();