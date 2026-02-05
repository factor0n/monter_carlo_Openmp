# Monte Carlo Integration with OpenMP

This project implements a **parallel Monte Carlo method** to estimate a definite integral using **OpenMP**.
The goal is to demonstrate how random sampling techniques can be efficiently parallelized for numerical simulations.

---

## Problem Description

We estimate the integral:

\[
I = \int_{1}^{5} x^4 e^{-x} \, dx
\]

using the Monte Carlo method, based on random sampling and statistical averaging.

---

## Methodology

The Monte Carlo estimator is based on:

\[
I \approx (b - a)\frac{1}{N}\sum_{i=1}^{N} f(x_i)
\]

where:
- \( x_i \sim \mathcal{U}(a, b) \)
- \( N \) is the number of random samples

The **standard deviation** of the estimator is also computed to quantify the statistical error.

---

## Parallelization Strategy

- The main sampling loop is parallelized using **OpenMP**
- A `reduction` clause is used to safely accumulate partial sums
- Each thread uses an **independent random seed** to avoid correlation between samples

This makes the algorithm embarrassingly parallel and well-suited for HPC architectures.

---

## Code Structure

```text
.
├── monte_carlo.c      # Main source file
└── README.md
