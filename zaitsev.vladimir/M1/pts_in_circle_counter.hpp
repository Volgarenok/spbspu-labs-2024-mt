#ifndef PTS_IN_CIRCLE_COUNTER
#define PTS_IN_CIRCLE_COUNTER
#include <vector>
#include <random>
#include "lrnd32.hpp"

void pts_in_circle_counter(size_t radius, size_t iters_nmb, lrnd32 generator, std::vector< size_t >::iterator it);
#endif
