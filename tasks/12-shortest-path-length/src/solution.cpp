#include <iostream>
#include <queue>
#include <vector>
#include <limits>

#ifdef TESTING
#include "tests.hpp"
#endif

using Weight = int64_t;

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
T find_min_path_length(
    const Matrix<T>& adjacencies,
    size_t start_vertex,
    size_t end_vertex
) {
    std::vector<T> distances(adjacencies.size(), std::numeric_limits<T>::max());
    distances[start_vertex] = 0;

    std::queue<size_t> next_vertices;
    next_vertices.push(start_vertex);

    while (!next_vertices.empty()) {
        size_t current_vertex = next_vertices.front();
        next_vertices.pop();

        for (size_t vertex = 0; vertex < adjacencies.size(); ++vertex) {
            const Weight weight = adjacencies[current_vertex][vertex];

            if (weight == 0) {
                continue;
            }

            const Weight new_weight = distances[current_vertex] + weight;
            if (distances[vertex] > new_weight) {
                distances[vertex] = new_weight;
                next_vertices.push(vertex);
            }
        }
    }

    return distances[end_vertex];
}

#ifndef TESTING
int main() {
    size_t matrix_size;
    std::cin >> matrix_size;

    Matrix<Weight> adjacencies;
    adjacencies.reserve(matrix_size);

    for (size_t row = 0; row < matrix_size; ++row) {
        std::vector<Weight> row_cols;
        row_cols.reserve(matrix_size);

        for (size_t col = 0; col < matrix_size; ++col) {
            Weight weight;
            std::cin >> weight;
            row_cols.push_back(weight);
        }

        adjacencies.push_back(std::move(row_cols));
    }

    size_t start_vertex, end_vertex;
    std::cin >> start_vertex >> end_vertex;

    --start_vertex;
    --end_vertex;

    std::cout << find_min_path_length(adjacencies, start_vertex, end_vertex)
              << std::endl;
}
#endif
