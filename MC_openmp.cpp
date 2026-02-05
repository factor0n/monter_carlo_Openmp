#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

typedef struct {
    double estimate;
    double std;
} MonteCarloStats;

/* Function to integrate */
double my_function(double x)
{
    return pow(x, 4) * exp(-x);
}

/* Monte Carlo estimation with standard deviation */
MonteCarloStats monte_carlo_integral(double lower, double upper, int n_samples)
{
    double sum = 0.0;
    double sum_sq = 0.0;

    #pragma omp parallel reduction(+:sum,sum_sq)
    {
        unsigned int seed = time(NULL) ^ omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i < n_samples; i++) {
            double u = (double) rand_r(&seed) / RAND_MAX;
            double x = lower + u * (upper - lower);

            double fx = my_function(x);
            sum += fx;
            sum_sq += fx * fx;
        }
    }

    double mean = sum / n_samples;
    double variance = (sum_sq / n_samples) - mean * mean;

    MonteCarloStats stats;
    stats.estimate = (upper - lower) * mean;
    stats.std = (upper - lower) * sqrt(variance / n_samples);

    return stats;
}

int main(void)
{
    double lower = 1.0;
    double upper = 5.0;

    int n_samples = 200;

    printf("Monte Carlo integration with OpenMP\n");
    printf("Integrating f(x) = x^4 * exp(-x) on [%.1f, %.1f]\n\n", lower, upper);

    for (int i = 1; i <= 5; i++) {
        n_samples *= 100;

        MonteCarloStats stats = monte_carlo_integral(lower, upper, n_samples);

        printf("Samples: %d | Estimate: %.6f | STD: %.6e\n",
               n_samples, stats.estimate, stats.std);
    }

    return 0;
}
