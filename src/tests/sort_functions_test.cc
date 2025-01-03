// Copyright 2023 DeepMind Technologies Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ==============================================================================

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

#include "gtest/gtest.h"
#include "../algorithms/sorting_networks.h"

using TestCases = std::vector<std::pair<std::vector<int>, std::vector<int>>>;

TestCases GenerateSortTestCases(int items_to_sort) {
  TestCases test_cases;
  auto add_all_permutations = [&test_cases](const std::vector<int>& initial) {
    std::vector<int> perm(initial);
    do {
      std::vector<int> expected = perm;
      std::sort(expected.begin(), expected.end());
      test_cases.push_back({perm, expected});
    } while (std::next_permutation(perm.begin(), perm.end()));
  };
  // Loop over all possible configurations of binary relations on sorted items.
  // Between each two consecutive items we can insert either '==' or '<'. Then,
  // for each configuration we generate all possible permutations.
  for (int i = 0; i < 1 << (items_to_sort - 1); ++i) {
    std::vector<int> relation = {1};
    for (int mask = i, j = 0; j < items_to_sort - 1; mask /= 2, ++j) {
      relation.push_back(mask % 2 == 0 ? relation.back() : relation.back() + 1);
    }
    add_all_permutations(relation);
  }
  return test_cases;
}

TestCases GenerateVariableSortTestCases(int max_items_to_sort) {
  TestCases test_cases;
  for (int num_items = 1; num_items <= max_items_to_sort; ++num_items) {
    TestCases base_test_cases = GenerateSortTestCases(num_items);
    for (auto [input, expected] : base_test_cases) {
      input.insert(input.begin(), num_items);
      expected.insert(expected.begin(), num_items);
      test_cases.push_back({input, expected});
    }
  }
  return test_cases;
}

void VerifyFunction(const TestCases& test_cases, std::function<void(int*)> fn) {
  for (const auto& [input, expected_output] : test_cases) {
    std::vector<int> output = input;
    fn(&output[0]);
    EXPECT_EQ(output, expected_output);
  }
}

TEST(SortingFunctionsTest, VerifyTestCases) {
  TestCases expected_test_cases = {
      {{1, 1, 1}, {1, 1, 1}},  //
      {{1, 2, 2}, {1, 2, 2}},  //
      {{2, 1, 2}, {1, 2, 2}},  //
      {{2, 2, 1}, {1, 2, 2}},  //
      {{1, 1, 2}, {1, 1, 2}},  //
      {{1, 2, 1}, {1, 1, 2}},  //
      {{2, 1, 1}, {1, 1, 2}},  //
      {{1, 2, 3}, {1, 2, 3}},  //
      {{1, 3, 2}, {1, 2, 3}},  //
      {{2, 1, 3}, {1, 2, 3}},  //
      {{2, 3, 1}, {1, 2, 3}},  //
      {{3, 1, 2}, {1, 2, 3}},  //
      {{3, 2, 1}, {1, 2, 3}},  //
  };
  EXPECT_EQ(expected_test_cases, GenerateSortTestCases(3));
}

TEST(SortingFunctionsTest, TestSort3AlphaDev) {
  VerifyFunction(GenerateSortTestCases(3), Sort3AlphaDev);
}

TEST(SortingFunctionsTest, TestSort4AlphaDev) {
  VerifyFunction(GenerateSortTestCases(4), Sort4AlphaDev);
}

TEST(SortingFunctionsTest, TestSort5AlphaDev) {
  VerifyFunction(GenerateSortTestCases(5), Sort5AlphaDev);
}

TEST(SortingFunctionsTest, TestSort6AlphaDev) {
  VerifyFunction(GenerateSortTestCases(6), Sort6AlphaDev);
}

TEST(SortingFunctionsTest, TestSort7AlphaDev) {
  VerifyFunction(GenerateSortTestCases(7), Sort7AlphaDev);
}

TEST(SortingFunctionsTest, TestSort8AlphaDev) {
  VerifyFunction(GenerateSortTestCases(8), Sort8AlphaDev);
}

TEST(VariableSortingFunctionsTest, VerifyTestCases) {
  TestCases expected_test_cases = {
      {{1, 1}, {1, 1}},
      {{2, 1, 1}, {2, 1, 1}},
      {{2, 1, 2}, {2, 1, 2}},
      {{2, 2, 1}, {2, 1, 2}},
      {{3, 1, 1, 1}, {3, 1, 1, 1}},
      {{3, 1, 2, 2}, {3, 1, 2, 2}},
      {{3, 2, 1, 2}, {3, 1, 2, 2}},
      {{3, 2, 2, 1}, {3, 1, 2, 2}},
      {{3, 1, 1, 2}, {3, 1, 1, 2}},
      {{3, 1, 2, 1}, {3, 1, 1, 2}},
      {{3, 2, 1, 1}, {3, 1, 1, 2}},
      {{3, 1, 2, 3}, {3, 1, 2, 3}},
      {{3, 1, 3, 2}, {3, 1, 2, 3}},
      {{3, 2, 1, 3}, {3, 1, 2, 3}},
      {{3, 2, 3, 1}, {3, 1, 2, 3}},
      {{3, 3, 1, 2}, {3, 1, 2, 3}},
      {{3, 3, 2, 1}, {3, 1, 2, 3}},
  };
  EXPECT_EQ(expected_test_cases, GenerateVariableSortTestCases(3));
}

TEST(VariableSortingFunctionsTest, TestVarSort3AlphaDev) {
  VerifyFunction(GenerateVariableSortTestCases(3), VarSort3AlphaDev);
}

TEST(VariableSortingFunctionsTest, TestVarSort4AlphaDev) {
  VerifyFunction(GenerateVariableSortTestCases(4), VarSort4AlphaDev);
}

TEST(VariableSortingFunctionsTest, TestVarSort5AlphaDev) {
  VerifyFunction(GenerateVariableSortTestCases(5), VarSort5AlphaDev);
}