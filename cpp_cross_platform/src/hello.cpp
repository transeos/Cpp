#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <random>
#include "hello.h"

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

void sampleParallelSort() {
    std::vector<int> data(1000000);
    std::iota(data.begin(), data.end(), 0); // Fill with increasing numbers

    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the data using std::shuffle
    std::shuffle(data.begin(), data.end(), g);

    // Sort the data in parallel
    std::sort(std::execution::par, data.begin(), data.end());

    std::cout << "First 10 elements after parallel sort: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}