licenses(["notice"])

exports_files(["LICENSE"])

package(
    default_visibility = ["//visibility:private"],
)

cc_library(
    name = "sorting_networks",
    srcs = ["src/algorithms/sorting_networks.cc"],
    hdrs = ["src/algorithms/sorting_networks.h"],
    copts = ["-std=c++17"],
    deps = [
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "merge_sort_variants",
    srcs = ["src/algorithms/merge_sort_variants.cc"],
    hdrs = ["src/algorithms/merge_sort_variants.h"],
    copts = ["-std=c++17"],
    deps = [":sorting_networks"],
)

cc_library(
    name = "quick_sort_variants",
    srcs = ["src/algorithms/quick_sort_variants.cc"],
    hdrs = ["src/algorithms/quick_sort_variants.h"],
    copts = ["-std=c++17"],
    deps = [":sorting_networks"],
)

cc_library(
    name = "bitonic_sort",
    srcs = ["src/algorithms/bitonic_sort.cc"],
    hdrs = ["src/algorithms/bitonic_sort.h"],
    copts = ["-std=c++17"],
    deps = [":sorting_networks"],
)

cc_binary(
    name = "benchmark",
    srcs = ["src/benchmark/benchmark.cc"],
    copts = ["-std=c++17"],
    deps = [
        ":merge_sort_variants",
        ":quick_sort_variants",
        ":bitonic_sort",
        "@com_github_google_benchmark//:benchmark",
    ],
)

cc_binary(
    name = "benchmark_bitonic",
    srcs = ["src/benchmark/benchmark_bitonic.cc"],
    copts = ["-std=c++17"],
    deps = [":bitonic_sort"],
)

cc_test(
    name = "sort_functions_test",
    srcs = ["src/tests/sort_functions_test.cc"],
    copts = ["-std=c++17"],
    deps = [
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
        ":sorting_networks",
    ],
)

cc_test(
    name = "merge_sort_correctness_test",
    srcs = ["src/tests/merge_sort_correctness_test.cc"],
    copts = ["-std=c++17"],
    deps = [
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
        ":merge_sort_variants",
    ],
)

cc_test(
    name = "quick_sort_correctness_test",
    srcs = ["src/tests/quick_sort_correctness_test.cc"],
    copts = ["-std=c++17"],
    deps = [
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
        ":quick_sort_variants",
    ],
)

cc_binary(
    name = "merge_sort_demo",
    srcs = ["src/benchmark/merge_sort_demo.cc"],
    deps = [":merge_sort"],
)