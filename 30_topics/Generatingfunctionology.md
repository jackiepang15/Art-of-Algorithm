---
marp: true
math: katex
---

# Generatingfunctionology

---

## 1 Introductory Ideas and Examples

Generating function allow you to do almost anything:

* Find an exact formula for the members of your sequence;
* Find a recurrence formula;
* Find averages and other statistical properties of your sequence;
* Find asymptotic formulas for your sequence;
* Prove unimodality, convexity, etc.;
* Prove identities;
* Other.

---

### 1.1 An easy two term recurrence

Find the sequence which satisfies the conditions

$$
a_{n+1} = 2a_n + 1 \quad (n \ge 0; a_0 = 0).
$$

Let’s find the generating function $A(x) = \sum_{n \ge 0} a_n x^n$.

* Left side, $\sum_{n \ge 0} a_{n + 1} x^n = A(x) / x$, since $a_0 = 0$.
* Right side, $\sum_{n \ge 0} (2a_{n} + 1) x^n = 2A(x) + \sum_{n \ge 0}x^n = 2A(x) + \frac{1}{x-1}$.

If we equate the results, we find that $A(x) = \frac{x}{(1-x)(1-2x)}$. Then we can expand $A(x)$ in a series to find an explicit formula for the $a_n$’s

$$
A(x) = x \left( \frac{2}{1-2x} - \frac{1}{1-x} \right) = (2-1)x + (2^2 - 1)x^2 + \cdots.
$$

---

### 1.2 A slightly harder two term recurrence

Find the sequence which satisfies the conditions

$$
a_{n+1} = 2a_n + n \quad (n \ge 0; a_0 = 1).
$$

The same way to find the generating function $A(x) = \sum_{n \ge 0} a_n x^n$.

* Left side, $\sum_{n \ge 0} a_{n + 1} x^n = (A(x) - 1) / x$, since $a_0 = 1$.
* Right side, $\sum_{n \ge 0} (2a_{n} + n) x^n = 2A(x) + \sum_{n \ge 0}n x ^n$.

By using the derivative of the geometric series, we have $\sum_{n \ge 0}n x ^n = x \cdot \left(\frac{d}{dx}\right) \sum_{n \ge 0} x^n = x \left(\frac{d}{dx}\right) \frac{1}{1-x} = \frac{x}{(1-x)^2}$.

Then we find that $A(x) = \frac{(1-2x+2x^2)}{(1-x)^2(1-2x)} = \frac{2}{1-2x} + \frac{-1}{(1-x)^2}$ and $a_n = 2^{n+1} - n - 1$.

---

A summary of ***The Method*** of generating functions.

1. Make sure that the set of values of the free variable for which the given recurrence relation is true, is clearly delineated.
2. Give a name to the generating function that you will look for, and write out that function in terms of the unknown sequence.
3. Multiply both sides of the recurrence by $x_n$, and sum over all values of $n$ for which the recurrence holds.
4. Express both sides of the resulting equation explicitly in terms of your generating function $A(x)$.
5. Solve the resulting equation for the unknown generating function $A(x)$.
6. If you want an exact formula for the sequence that is defined by the given recurrence relation, then attempt to get such a formula by expanding $A(x)$ into a power series by any method you can think of.

---

### 1.3 A three term recurrence

Find the Fibonacci sequence which satisfies
$$
F_{n+1} = F_n + F_{n-1} \quad (n \ge 1; F_0 = 1, F_1 = 1).
$$

Following ***The Method***, we will solve the generating function $F(x) = \sum_{n \ge 0}F_n x^n$.

* Left side, $\sum_{n \ge 1} F_{n+1} x^n = \frac{F(x) - x}{x}$.
* Right side, $\sum_{n \ge 1} F_{n} x^n + \sum_{n \ge 1} F_{n-1} x^n = F(x) + x F(x)$.

It follows that $F(x) = \frac{x}{1-x-x^2}$. Therefore $F_n = \frac{1}{\sqrt{5}}(r^n_{+} + r^n_{-})$ where $r^n_{\pm} = (1 \pm \sqrt{5}) / 2$.

---

### 1.4 A three term boundary value problem

Suppose we are given a table of values $y_0, y_1, \ldots, y_n$ of some function $y(x)$, at a set of equally spaced points $t_i = t_0 + ih (0 \le i \le n)$. We want to construct a smooth function $S(x)$ that fits the data, subject to the following conditions:

* Within each interval $(t_i, t_{i+1}) (i = 0, \ldots, n − 1)$ our function $S(x)$ is to be a cubic polynomial;
* The functions $S(x)$, $S'(x)$ and $S''(x)$ are to be continuous on the whole interval $[t_0, t_n]$;
* $S(t_i) = y_i$ for $i = 0, \ldots, n$.

A function $S(x)$ that satisfies these conditions is called a cubic spline.

---

Suppose we are trying to fit the powers of $2$ by a cubic spline on the interval $[0, 5]$. Our input data are $y_i = 2^i$ for $i = 0, 1, \ldots, 5$, $h = 1$, and $n = 5$.

We first consider a slightly more general situation. It consists of the recurrence $au_{n+1} + bu_n + cu_{n−1} = d_n (n = 1, 2, \ldots, N − 1; u_0 = 0; u_N = 0)$ where the sequence $\{d_n\}^{N-1}_{n=1}$ are given in advance.

---

### 1.5 Two independent variables

---

### 1.6 Another 2-variable case

---

## 2 Series

---

### 2.1 Formal power series

---

### 2.2 The calculus of formal ordinary power series generating functions

---

### 2.3 The calculus of formal exponential generating functions

---

### 2.4 Power series, analytic theory

---

### 2.5 Some useful power series

---

### 2.6 Dirichlet series, formal theory

---

## 3 Cards, Decks, and Hands: The Exponential Formula

---

### 3.1 Introduction

---

### 3.2 Definitions and a question

---

### 3.3 Examples of exponential families

---

### 3.4 The main counting theorems

---

### 3.5 Permutations and their cycles

---

### 3.6 Set partitions

---

### 3.7 A subclass of permutations

---

### 3.8 Involutions, etc

---

### 3.9 2-regular graphs

---

### 3.10 Counting connected graphs

---

### 3.11 Counting labeled bipartite graphs

---

### 3.12 Counting labeled trees

---

### 3.13 Exponential families and polynomials of ‘binomial type.’

---

### 3.14 Unlabeled cards and hands

---

### 3.15 The money changing problem

---

### 3.16 Partitions of integers

---

### 3.17 Rooted trees and forests

---

### 3.18 Historical notes

---

## 4 Applications of generating functions

---

### 4.1 Generating functions find averages, etc

---

### 4.2 A generatingfunctionological view of the sieve method

---

### 4.3 The ‘Snake Oil’ method for easier combinatorial identities

---

### 4.4 WZ pairs prove harder identities

---

### 4.5 Generating functions and unimodality, convexity, etc

---

### 4.6 Generating functions prove congruences

---

### 4.7 The cycle index of the symmetric group

---

### 4.8 How many permutations have square roots?

---

### 4.9 Counting polyominoes

---

### 4.10 Exact covering sequences

---

## 5 Analytic and asymptotic methods

---

### 5.1 The Lagrange Inversion Formula

---

### 5.2 Analyticity and asymptotics (I): Poles

---

### 5.3 Analyticity and asymptotics (II): Algebraic singularities

---

### 5.4 Analyticity and asymptotics (III): Hayman’s method
