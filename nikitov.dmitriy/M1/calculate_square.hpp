#ifndef CALCULATE_SQUARE_HPP
#define CALCULATE_SQUARE_HPP

#include <cstddef>

size_t countPart(int radius, int seed, int tries, size_t id);

double calculateSquare(int radius, int numberOfThreads, int seed, int tries);

#endif