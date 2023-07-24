#pragma once

#include <gtest/gtest.h>

using Weight = int32_t;

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
std::vector<size_t> find_graph_cycle(const Matrix<T>& adjacencies);

struct GraphCycleTestData {
    Matrix<Weight> adjacencies;
    std::vector<size_t> expected;
};

class GraphCycleTest : public testing::TestWithParam<GraphCycleTestData> {};

TEST_P(GraphCycleTest, ValidData) {
    const auto data = GetParam();
    const auto result = find_graph_cycle(data.adjacencies);
    ASSERT_EQ(result, data.expected);
}

INSTANTIATE_TEST_SUITE_P(
    ValidGraphCycleTestData,
    GraphCycleTest,
    testing::Values(
        GraphCycleTestData{
            .adjacencies =
                {
                    {0, 1, 1},
                    {1, 0, 1},
                    {1, 1, 0},
                },
            .expected = {2, 1, 0},
        },
        GraphCycleTestData{
            .adjacencies =
                {
                    {0, 0, 1, 0},
                    {0, 0, 0, 1},
                    {1, 0, 0, 0},
                    {0, 1, 0, 0},
                },
            .expected = {},
        },
        GraphCycleTestData{
            .adjacencies =
                {
                    {0, 1, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                    {0, 0, 0, 1, 1},
                    {0, 0, 1, 0, 1},
                    {0, 0, 1, 1, 0},
                },
            .expected = {4, 3, 2},
        }
    )
);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
