#pragma once

#include <gtest/gtest.h>

using Weight = int64_t;

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
T find_min_path_length(
    const Matrix<T>& adjacencies,
    size_t start_vertex,
    size_t end_vertex
);

struct MinPathLengthTestData {
    Matrix<Weight> adjacencies;
    size_t start_vertex;
    size_t end_vertex;
    Weight expected;
};

class MinPathLengthTest :
    public testing::TestWithParam<MinPathLengthTestData> {};

TEST_P(MinPathLengthTest, ValidData) {
    const auto data = GetParam();
    const auto result = find_min_path_length(
        data.adjacencies,
        data.start_vertex,
        data.end_vertex
    );
    ASSERT_EQ(result, data.expected);
}

INSTANTIATE_TEST_SUITE_P(
    ValidMinPathLengthTestData,
    MinPathLengthTest,
    testing::Values(
        MinPathLengthTestData{
            .adjacencies =
                {
                    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                    {1, 0, 0, 1, 1, 0, 1, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
                    {0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
                    {0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                    {0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                    {0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
                    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                },
            .start_vertex = 4,
            .end_vertex = 3,
            .expected = 2,
        },
        MinPathLengthTestData{
            .adjacencies =
                {
                    {0, 1, 0, 0, 1},
                    {1, 0, 1, 0, 0},
                    {0, 1, 0, 0, 0},
                    {0, 0, 0, 0, 0},
                    {1, 0, 0, 0, 0},
                },
            .start_vertex = 2,
            .end_vertex = 4,
            .expected = 3,
        }
    )
);

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
