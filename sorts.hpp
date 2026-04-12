#ifndef PTECH_SORTS_HPP
#define PTECH_SORTS_HPP
#include <vector>

/**
 * Sorting with selection algorithm
 *
 * @param arr Vector to be sorted
 */
template<typename T>
void selectionSort(std::vector<T> &arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        std::swap(arr[i], arr[min_index]);
    }
}

/**
 * Sorting with bubble algorithm
 *
 * @param arr Vector to be sorted
 */
template<typename T>
void bubbleSort(std::vector<T> &arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

/**
 * Sorting with simple insertions algorithm
 *
 * @param arr Vector to be sorted
 */
template<typename T>
void insertionSort(std::vector<T> &arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        T key = arr[i];
        size_t j = i;
        while (j >= 1 && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

#endif //PTECH_SORTS_HPP
