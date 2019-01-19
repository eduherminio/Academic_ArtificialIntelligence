#include "../header/dardos_pi.h"
#include <random>
#include <chrono>
#define PI 3.14159264

void Dardos_Pi::Calculate_Pi(const unsigned n_iterations)
{
	std::mt19937 rng;   // std::mersenne_twister_engine, pseudorandom number generator

	std::uniform_real_distribution<double> aleatorio(-1., 1.);   // [-1, 1)

	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	rng.seed(seed);

	double x, y;
	unsigned n_success = 0;

	for (size_t iter = 0; iter < n_iterations; ++iter)
	{
		x = aleatorio(rng);
		y = aleatorio(rng);
		if ((x*x + y * y) <= 1)
			n_success++;
	}

	pi_ = (double)n_success / n_iterations;
	pi_ = (double)4 * pi_;
}
