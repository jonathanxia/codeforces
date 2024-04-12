#pragma once
#include <lib/common.h>

namespace algo {
    template <typename T>
    long long mergeAndCountInversions(std::vector<T>& arr, std::size_t low, std::size_t mid, std::size_t high) {
        std::vector<T> temp(high - low + 1);
        long long inversions = 0;

        std::size_t i = low; // Index for the left subarray
        std::size_t j = mid + 1; // Index for the right subarray
        std::size_t k = 0; // Index for the merged array

        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                // If arr[i] > arr[j], it means there are (mid - i + 1) inversions
                inversions += mid - i + 1;
                temp[k++] = arr[j++];
            }
        }

        // Copy the remaining elements of left subarray, if any
        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        // Copy the remaining elements of right subarray, if any
        while (j <= high) {
            temp[k++] = arr[j++];
        }

        // Copy the merged elements back to the original array
        for (i = low, k = 0; i <= high; ++i, ++k) {
            arr[i] = temp[k];
        }

        return inversions;
    }

    template <typename T>
    long long count_inversions(std::vector<T> arr) {
        std::size_t n = arr.size();
        long long inversions = 0;

        for (std::size_t size = 1; size < n; size *= 2) {
            for (std::size_t left = 0; left < n - 1; left += 2 * size) {
                std::size_t mid = std::min(left + size - 1, n - 1);
                std::size_t right = std::min(left + 2 * size - 1, n - 1);

                inversions += mergeAndCountInversions(arr, left, mid, right);
            }
        }

        return inversions;
    }
};
