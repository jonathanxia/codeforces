#pragma once
#include <lib/common.h>

// You should use TopKTrackerWithCounts unless you are memory constrained
template <typename T, std::size_t K>
struct TopKTracker {
    std::array<T, K> topKElements;
    int size;

    TopKTracker() : size(0) {}

    void addElement(T element) {
        if (containsElement(element)) {
            // If the element is already in the top K, do nothing
            return;
        }

        if (size < K) {
            topKElements[size++] = element;
            manualInsertionSort();
        } else if (element > topKElements[K - 1]) {
            topKElements[K - 1] = element;
            manualInsertionSort();
        }
    }

    TopKTracker operator+(const TopKTracker& other) const {
        TopKTracker result = *this;

        for (std::size_t i = 0; i < other.size; ++i) {
            result.addElement(other.topKElements[i]);
        }

        return result;
    }

    void manualInsertionSort() {
        for (std::size_t i = size - 1; i > 0 && topKElements[i] > topKElements[i - 1]; --i) {
            std::swap(topKElements[i], topKElements[i - 1]);
        }
    }

    bool containsElement(T element) const {
        return std::find(topKElements.begin(), topKElements.begin() + size, element) != topKElements.begin() + size;
    }
};

template <typename T, std::size_t K>
struct TopKTrackerWithCounts {
    // An array where each element is a pair {element, count}
    // This array is sorted in decreasing order, so topKElements[0] is the largest
    std::array<pair<T, ll>, K> topKElements;
    int size;

    TopKTrackerWithCounts() : size(0) {}

    void addElement(T element, ll count) {
        // Determine if element is inside
        FOR(i, 0, size - 1) {
            if (topKElements[i].first == element) {
                topKElements[i].second += count;
                return;
            }
        }
        if (size < K) {
            topKElements[size++] = mp(element, count);
            manualInsertionSort();
        } else if (element > topKElements[K - 1]) {
            topKElements[K - 1] = mp(element, count);
            manualInsertionSort();
        }
    }

    TopKTracker operator+(const TopKTracker& other) const {
        TopKTracker result = *this;

        for (std::size_t i = 0; i < other.size; ++i) {
            result.addElement(other.topKElements[i]);
        }

        return result;
    }

    void manualInsertionSort() {
        for (std::size_t i = size - 1; i > 0 && topKElements[i] > topKElements[i - 1]; --i) {
            std::swap(topKElements[i], topKElements[i - 1]);
        }
    }
};