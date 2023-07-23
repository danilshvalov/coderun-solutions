#pragma once

#include <gtest/gtest.h>

using Color = int64_t;

template <typename T>
std::pair<T, T> find_min_diff(
    const std::vector<T>& lhs,
    const std::vector<T>& rhs
);

struct MinDiffTestData {
    std::vector<Color> lhs;
    std::vector<Color> rhs;
    std::pair<Color, Color> expected;
};

class MinDiffTest : public testing::TestWithParam<MinDiffTestData> {};

TEST_P(MinDiffTest, ValidData) {
    const auto data = GetParam();
    const auto result = find_min_diff(data.lhs, data.rhs);
    ASSERT_EQ(result, data.expected);
}

INSTANTIATE_TEST_SUITE_P(
    ValidMinDiffTestData,
    MinDiffTest,
    testing::Values(
        MinDiffTestData{
            .lhs = {3, 4},
            .rhs = {1, 2, 3},
            .expected = {3, 3},
        },
        MinDiffTestData{
            .lhs = {3, 4},
            .rhs = {1, 2, 3},
            .expected = {3, 3},
        },
        MinDiffTestData{
            .lhs = {1, 2, 3, 4, 5},
            .rhs = {1, 2, 3, 4, 5},
            .expected = {1, 1},
        },
        MinDiffTestData{
            .lhs = {1, 2, 5, 8, 9},
            .rhs = {3, 4, 5, 6, 7},
            .expected = {5, 5},
        }
    )
);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
