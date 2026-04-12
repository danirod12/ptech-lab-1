#ifndef PTECH_MISC_HPP
#define PTECH_MISC_HPP
#include <ctime>

/**
 * Measure the execution time of a function that takes a vector as an argument
 *
 * @tparam F Function type to be measured
 * @tparam T Type of the elements in the vector to be sorted
 * @param func Function to be measured
 * @param data First parameter type of the function to be measured (vector of T which is being copied)
 * @return Time taken by the function to execute in milliseconds
 */
template<typename F, typename T>
double measure_func(F func, std::vector<T>& data) {
    timespec start, end;

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start) != 0) {
        return -1.0;
    }

    func(data);

    if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end) != 0) {
        return -1.0;
    }

    double start_ms = (double)start.tv_sec * 1e3 + (double)start.tv_nsec / 1e6;
    double end_ms   = (double)end.tv_sec * 1e3 + (double)end.tv_nsec / 1e6;

    return end_ms - start_ms;
}

#endif //PTECH_MISC_HPP
