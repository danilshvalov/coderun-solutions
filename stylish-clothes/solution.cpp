#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#ifdef TESTING
#include "tests.hpp"
#endif

using Color = int64_t;

template <typename T>
std::pair<T, T> find_min_diff(
    const std::vector<T>& lhs,
    const std::vector<T>& rhs
) {
    const auto diff = [&](size_t left, size_t right) -> T {
        return std::abs(lhs[left] - rhs[right]);
    };

    size_t min_left = 0;
    size_t min_right = 0;

    size_t right = 0;
    for (size_t left = 0; left < lhs.size(); ++left) {
        while (right + 1 < rhs.size()
               && diff(left, right + 1) < diff(left, right)) {
            ++right;
        }

        if (diff(left, right) < diff(min_left, min_right)) {
            min_left = left;
            min_right = right;
        }
    }

    return {lhs[min_left], rhs[min_right]};
}

template <typename T>
std::vector<T> read_vector(std::istream& in = std::cin) {
    size_t size;
    in >> size;

    std::vector<T> result;
    for (size_t i = 0; i < size; ++i) {
        T value;
        in >> value;
        result.push_back(std::move(value));
    }

    return result;
}

#ifndef TESTING
int main(int argc, char** argv) {
    auto shirts = read_vector<Color>();
    auto pants = read_vector<Color>();
    auto [shirt_color, pants_color] = find_min_diff(shirts, pants);
    std::cout << shirt_color << ' ' << pants_color << std::endl;
}
#endif
