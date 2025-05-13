#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comp) {
    std::deque<T> result;
    auto it1 = half1.cbegin();
    auto it2 = half2.cbegin();

    while (it1 != half1.cend() && it2 != half2.cend()) {
        if (comp(*it1, *it2)) {
            result.push_back(*it1);
            ++it1;
        } else {
            result.push_back(*it2);
            ++it2;
        }
    }

    result.insert(result.end(), it1, half1.cend());
    result.insert(result.end(), it2, half2.cend());

    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comp) {
    if (src.size() <= 1) {
        return src;
    }

    const auto middle = src.cbegin() + (src.size() / 2);
    std::deque<T> half1(src.cbegin(), middle);
    std::deque<T> half2(middle, src.cend());

    return Merge(MergeSort(half1, comp), MergeSort(half2, comp), comp);
}
