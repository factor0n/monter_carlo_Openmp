#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <omp.h>  //  OpenMP

double myFunction(double x);
void monteCarloEstimateSTD(double lowBound, double upBound, int iterations, double mcStats[]);

int main()
{
    double lowerBound, upperBound;
    int iterations;

    lowerBound = 1;
    upperBound = 5;

    double mcStats[2]; // position 0: estimate, position 1: STD

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL) ^ omp_get_thread_num());  // Graine différente pour chaque thread

    for(int i = 1; i < 6; i++)
    {
        iterations = 2 * pow(100, i);

        monteCarloEstimateSTD(lowerBound, upperBound, iterations, mcStats);

        printf("Estimate for %.1f -> %.1f is %.3f, STD = %.4f, (%i iterations)\n",
               lowerBound, upperBound, mcStats[0], mcStats[1], iterations);
    }

    return 0;
}
double myFunction(double x)
{
    return pow(x, 4) * exp(-x);
}
void monteCarloEstimateSTD(double lowBound, double upBound, int iterations, double statsArray[])
{
    double totalSum = 0;
    double totalSumSquared = 0;

    #pragma omp parallel reduction(+:totalSum,totalSumSquared)
    {
        // Each thread has its own random number generator
        unsigned int seed = time(NULL) ^ omp_get_thread_num();

        #pragma omp for
        for(int iter = 0; iter < iterations; iter++)
        {
            double randNum = lowBound + (double(rand_r(&seed))/RAND_MAX) * (upBound - lowBound);
            double functionVal = myFunction(randNum);

            totalSum += functionVal;
            totalSumSquared += pow(functionVal, 2);
        }
    }

    double estimate = (upBound - lowBound) * totalSum / iterations;
    double expected = totalSum / iterations;
    double expectedSquare = totalSumSquared / iterations;
    double std = (upBound - lowBound) * pow((expectedSquare - pow(expected, 2))/(iterations-1), 0.5);

    statsArray[0] = estimate;
    statsArray[1] = std;
}
