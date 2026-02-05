# Monte Carlo Integration with OpenMP

This project implements a parallel Monte Carlo method to estimate
a definite integral using OpenMP.

---

## Problem Description

We estimate the integral:

I = ∫₁⁵ x⁴ e⁻ˣ dx

using random sampling techniques.

---

## Methodology

The Monte Carlo estimator is given by:

I ≈ (b − a) · (1 / N) · Σ f(xᵢ)

where:
- xᵢ are uniformly distributed in [a, b]
- N is the number of random samples

The standard deviation is also computed to quantify the statistical error.

---

## Parallelization Strategy

- The sampling loop is parallelized using OpenMP
- A reduction clause is used to accumulate partial sums
- Each thread uses an independent random seed

---

## Compilation

```bash
gcc -O3 -fopenmp monte_carlo.c -lm -o monte_carlo
