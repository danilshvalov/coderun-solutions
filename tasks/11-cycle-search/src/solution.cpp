#include <iostream>
#include <string>
#include <vector>
#include <stack>

#ifdef TESTING
#include "tests.hpp"
#endif

using Weight = int32_t;

template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
class GraphCycleFinder {
  public:
    explicit GraphCycleFinder(const Matrix<T>& adjacencies) :
        adjacencies_(adjacencies),
        states_(adjacencies.size(), VertexState::NotVisited),
        cycle_path_(adjacencies.size(), npos) {}

    std::vector<size_t> find_cycle() {
        for (size_t vertex = 0; vertex < adjacencies_.size(); ++vertex) {
            if (find_cycle_from(vertex)) {
                break;
            }
        }

        if (cycle_start_ == npos) {
            return {};
        }

        std::vector<size_t> result;
        for (size_t vertex = cycle_end_; vertex != cycle_start_;
             vertex = cycle_path_[vertex]) {
            result.push_back(vertex);
        }
        result.push_back(cycle_start_);
        return result;
    }

  private:
    inline static const size_t npos = static_cast<size_t>(-1);

    enum class VertexState {
        NotVisited,
        Visited,
        Exited,
    };

    bool find_cycle_from(size_t start_vertex, size_t prev_vertex = npos) {
        states_[start_vertex] = VertexState::Visited;

        for (size_t end_vertex = 0; end_vertex < adjacencies_.size();
             ++end_vertex) {
            const Weight weight = adjacencies_[start_vertex][end_vertex];

            if (weight == 0) {
                continue;
            }

            if (states_[end_vertex] == VertexState::NotVisited) {
                cycle_path_[end_vertex] = start_vertex;
                if (find_cycle_from(end_vertex, start_vertex)) {
                    return true;
                }
            } else if (states_[end_vertex] == VertexState::Visited && end_vertex != prev_vertex) {
                cycle_end_ = start_vertex;
                cycle_start_ = end_vertex;
                return true;
            }
        }

        states_[start_vertex] = VertexState::Exited;
        return false;
    }

    const Matrix<T>& adjacencies_;
    std::vector<VertexState> states_;
    std::vector<size_t> cycle_path_;
    size_t cycle_start_ = npos;
    size_t cycle_end_ = npos;
};

template <typename T>
std::vector<size_t> find_graph_cycle(const Matrix<T>& adjacencies) {
    return GraphCycleFinder<T>{adjacencies}.find_cycle();
}

#ifndef TESTING
int main(int argc, char** argv) {
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

    auto cycle = find_graph_cycle(adjacencies);
    if (cycle.empty()) {
        std::cout << "NO" << std::endl;
    } else {
        std::cout << "YES" << std::endl;
        std::cout << cycle.size() << std::endl;
        for (size_t vertex : cycle) {
            std::cout << vertex + 1 << ' ';
        }
    }
}
#endif
