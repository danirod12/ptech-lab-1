#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <semaphore>

#include "misc.hpp"
#include "sorts.hpp"
#include "taxpayer.hpp"

/**
 * Main function to compare sorting algorithms
 *
 * This function reads data from CSV files, runs different sorting algorithms on the data,
 * measures their execution time, and writes the results to a new CSV file. It uses multithreading
 * to run multiple sorting algorithms in parallel while limiting the number of concurrent threads
 * to avoid overloading the system.
 *
 * @return 0 on success
 */
int main() {
    std::vector<int> sizes = {
        100, 250, 500, 750, 1500, 2500, 5000, 7500, 10000,
        15000, 25000, 50000, 75000, 100000, 125000, 150000
    };

    unsigned int cores = std::thread::hardware_concurrency();
    std::counting_semaphore sem(std::max(1u, cores - 2));

    std::ofstream results("sorting_times.csv");
    results << "Size,Selection,Bubble,Insertion,StdSort\n";
    std::mutex file_mtx;
    std::vector<std::thread> main_tasks;

    for (const int n : sizes) {
        main_tasks.emplace_back([&, n]() {
            std::string input_file = "./data/data_" + std::to_string(n) + ".csv";
            std::vector<Taxpayer> original = readData(input_file);
            if (original.empty()) return;

            auto run_with_sem = [&](auto sort_func) {
                return std::async(std::launch::async, [&sem, sort_func, original]() mutable {
                    sem.acquire();
                    double t = measure_func(sort_func, original);
                    sem.release();
                    return t;
                });
            };

            auto f1 = run_with_sem(selectionSort<Taxpayer>);
            auto f2 = run_with_sem(bubbleSort<Taxpayer>);
            auto f3 = run_with_sem(insertionSort<Taxpayer>);
            auto f4 = run_with_sem([](auto& v){ std::sort(v.begin(), v.end()); });

            double r1 = f1.get();
            double r2 = f2.get();
            double r3 = f3.get();
            double r4 = f4.get();

            std::sort(original.begin(), original.end());

            std::lock_guard<std::mutex> lock(file_mtx);
            results << n << "," << r1 << "," << r2 << "," << r3 << "," << r4 << std::endl;
            std::cout << "[DONE] Size: " << n << std::endl;

            writeData("./sorted/sorted_" + std::to_string(n) + ".csv", original);
        });
    }

    for (auto& t : main_tasks) {
        t.join();
    }
    return 0;
}
