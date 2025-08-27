---
marp: true
math: katex
---

# Concrete Mathematics

---

## 1 Recurrent Problems

There are recurrences that don't have simple closed forms. When such recurrences turn out to be important, because they **arise repeatedly**, we add new operations to our repertoire; this can **greatly extend the range** of problems solvable in "simple" closed form.

---

### 1.1 The Tower of Hanoi

We are given a tower of eight disks, initially stacked in decreasing size on one of three pegs. The objective is to transfer the entire tower to one of the other pegs, moving only one disk at a time and never moving a larger one onto a smaller. Let $T_n$ be the minimum number of moves that will transfer $n$ disks from one peg to another under Lucas's rules. Then

$$
\begin{array}{rcl}
T_0 & = & 0;\\
T_n & = & 2T_{n−1} + 1 , \; \text{for} \; n > 0.
\end{array}
$$

One way is to guess the correct solution by looking at small cases, then to prove that our guess is correct using mathematical induction. The anwser is

$$
T_n = 2^n − 1, \; \text{for} \; n \ge 0.
$$

---

Q1.1 - Assuming that there are n different sizes of disks and exactly $m_k$ disks of size $k$. Determine $A(m_1, \ldots , m_n)$, the minimum number of moves needed to transfer a tower when equal-size disks are considered to be indistinguishable.

Q1.2 - Find the minimum number of moves $F(k, n)$ that will transfer $n$ disks from one peg to another if there are $k$ pegs.

---

### 1.2 Lines in the Plane

How many slices of pizza can a person obtain by making $n$ straight cuts with a pizza knife? After some thought we realize that the $n$th line increases the number of regions by $k$ if and only if it splits $k$ of the old regions. The recurrence is therefore

$$
\begin{array}{rcl}
T_0 & = & 0;\\
T_n & = & T_{n−1} + n, \; \text{for} \; n > 0.
\end{array}
$$

We can use a trick that Gauss reportedly when he was nine years old, which is merely adding the numbers to its reversal. The solution is

$$
T_n = \frac{n(n+1)}{2} + 1, \; \text{for} \; n \ge 0.
$$

---

Q2.1 - What's the maximum number of regions definable by n zig-zag lines, each of which consists of two parallel infinite half-lines joined by a straight segment?

Q2.2 - Find a recurrence relation for $P(n, d)$, the maximum number of $d$-dimensional subspaces that can be defined by $n$ different hyperplanes.

---

### 1.3 The Josephus Problem

We start with n people numbered $1$ to $n$ around a circle, and we eliminate every second remaining person until only one survives. The problem: Determine the survivor's number, $J(n)$. Because J(n) always seems to be odd, we condider the even case and the odd case respectively. The recurrence is

$$
\begin{array}{rcl}
J(1) & = & 1;\\
J(2n) & = & 2J(n) - 1, \; \text{for} \; n \ge 1;\\
J(2n + 1) & = & 2J(n) + 1, \; \text{for} \; n \ge 1.
\end{array}
$$

The solution to the recurrence is

$$
J(2^m + l) = 2l + 1, \; \text{for} \; m \ge 0 \; \text{and} \; 0 \le l < 2^m.
$$

Suppose $n$'s binary expansion is $n = (b_m b_{m−1} \ldots b_1 b_0)_2$, we have

$$
J\left((b_m b_{m−1} \ldots b_1 b_0)_2\right) = (b_{m−1} \ldots b_1 b_0 b_m)_2.
$$

---

If we let $\beta_0 = \beta$ and $\beta_1 = \gamma$, we can rewrite the generalized recurrence

$$
\begin{array}{rcl}
f(1) & = & \alpha;\\
f(2n + j) & = & 2f(n) + \beta_j, \; \text{for} \; j = 0, 1 \; \text{and} \; n \ge 1.
\end{array}
$$

Let $f(n) = A(n)\alpha + B(n)\beta + C(n)\gamma$ and $n = 2^m + l$, where $m \ge 0$ and $0 \le l < 2^m$. Using the **repertoire method**, plugging $f(n) = 1$, $f(n) = n$, $f(n) = n^2$ into $f(0), f(1), f(2)$, we have

$$
\begin{array}{rcl}
A(n) & = & 2^m;\\
B(n) & = & 2^m - 1 - l;\\
C(n) & = & l.
\end{array}
$$

Suppose we now relax the radix $2$ notation to allow arbitrary digits instead of just $0$ and $1$, we have
$$
f\left((b_m b_{m−1} \ldots b_1 b_0)_2\right) = (\alpha \beta_{b_{m−1}} \beta_{b_{m−2}} \ldots \beta_{b_{1}} \beta_{b_{0}})_2.
$$

---

Consider a even more generalized recurrence

$$
\begin{array}{rcll}
f(j) & = & \alpha_j & \text{for} \; 1 \le j < d;\\
f(dn + j) & = & cf(n) + \beta_j,& \text{for} \; 0 \le j < d \; \text{and} \; n \ge 1.
\end{array}
$$

If we start with numbers in radix $d$ and produce values in radix $c$, we have

$$
f\left((b_m b_{m−1} \ldots b_1 b_0)_d\right) = (\alpha_{b_m} \beta_{b_{m−1}} \beta_{b_{m−2}} \ldots \beta_{b_{1}} \beta_{b_{0}})_c.
$$

---

Q3.1 - Suppose there are $2n$ people in a circle; the first $n$ are "good guys" and the last $n$ are "bad guys". Show that there is always an integer $m$ (depending on $n$) such that, if we go around the circle executing every $m$th person, all the bad guys are first to go.

Q3.2 - Suppose that Josephus finds himself in a given position $j$, but he has a chance to name the elimination parameter $q$ such that every $q$th person is executed. Can he always save himself?

Q3.3 - Let's say that a Josephus subset of $\{1, 2, . . . , n\}$ is a set of $k$ numbers such that, for some $q$, the people with the other $n−k$ numbers will be eliminated first. Are non-Josephus subsets rare for large $n$?

---

## 2 Sums

---

### 2.1 Sums and Recurrences

Consider a recurrence of the form

$$
a_nT_n = b_nT_{n−1} + c_n.
$$

Let $s_nb_n = s_{n−1}a_{n−1}$ and $S_n = s_n a_n T_n$. We have a sum-recurrence $S_n = S_{n−1} + s_nc_n = s_1b_1T_0 +
 \sum_{k=1}^n s_k c_k$. Hence the solution is

$$
T_n = \frac{1}{s_n a_n} \left(s_1b_1T_0 + \sum_{k=1}^n s_k c_k \right).
$$

This idea can be used to find the solution of a recurrence that arises in the study of "quick-sort," one of the most important methods for sorting data inside a computer.

---

### 2.2 Manipulation of Sums

There are three simple rules: distributive law, associative law, commutative law. These rules can be used to compute the general sum of an arithmetic progression, $\sum_{k=0}^{n}(a + bk) = (a + \frac{1}{2}b_n)(n + 1)$.

The operation of splitting off a term is the basis of a perturbation method that allow us to find the sum of a general geomeric progression, $\sum_{0\le k\le n} ax^k=a\frac{1-x^{n+1}}{1-x}$ and $\sum_{0\le k\le n} kx^k=x\frac{1 - x^{n+1}-(n+1)x^{n}(1-x)}{(1-x)^2}$, for $x \ne 1$ (more connections between calculus and discrete mathematics).

---

### 2.3 Multiple Sums

For two or more indices, there are a general associative law and a general distributive law. We have an interesting formula:

$$
\left(\sum_{k=1}^n a_k\right) \left(\sum_{k=1}^n b_k\right) = n \sum_{k=1}^n a_k b_k - \sum_{1\le j<k\le n}^n (a_k - a_j)(b_k - b_j),
$$

which yields Chebyshev's monotonic inequalities as a special case.

Here is an example of multiple sums $S_n = \sum_{1 \le j < k \le n} \frac{1}{k-j}$. We can evaluate this sum in two ways, one algebraic and one geometric, which gives us a further identity

$$
S_n = \sum_{0 \le k < n} H_k = n H_n - n.
$$

---

### 2.4 General Methods

There are at least eight methods to solve the the sum of the first $n$ squares

$$
S^{(2)}_n = \sum_{0 \le k \le n} k^2, \; \text{for} \; n \ge 0.
$$

**Method 0**: Look it up.

Handbook of Integer Sequences, Sloane, 1973. Sequence number 1574, and it's called the sequence of "square pyramidal numbers".

**Method 1**: Guess the answer, prove it by induction.

Suppose the equivalent formula is $S^{(2)}_n = \frac{n(n + \frac{1}{2})(n+1)}{3}$. We can prove our conjectures using  Mathematical induction.

---

**Method 2**: Perturb the sum.

Using the perturbation method on $S^{(2)}_n$ reveals a way to sum the first $n$ integers in closed form, $2 \sum_{0 \le k \le n} k = (n+1)^2 - (n+1)$. We can probably get an expression for the integers squared if we start to perturb $S^{(3)}_n = \sum_{0 \le k \le n} k^3$, for $n \ge 0$.

**Method 3**: Build a repertoire.

The solution to $R_0 = \alpha$; $R_n = R_{n−1} + \beta + \gamma n + \delta n^2$, for $n > 0$ will be of the general form $R_n = A(n)\alpha + B(n)\beta + C(n)\gamma + D(n)\delta$. Plugging $f(n) = 1$, $f(n) = n$, $f(n) = n^2$, $f(n) = n^3$ into $f(0), f(1), f(2), f(3)$, we will get the answer.

---

**Method 4**: Replace sums by integrals.

The area under the curve $f(x)=x^2$ is $\int_0^n x^2 dx = \frac{1}{3}n^3$; therefore we know that $S^{(2)}_n$ is approximately $\frac{1}{3}n^3$. 1) One way to use this fact is to examine the error in the approximation $E_n = S^{(2)}_n - \frac{1}{3}n^3$. We find that $E_n = E_{n-1} + n - \frac{1}{3}$. 2) Another way to pursue the integral approach is to find a formula for $E_n$ by summing the areas of the wedge-shaped error terms. Then we get the answer.

---

**Method 5**: Expand and contract. Consider another geometric perspective.

$$
\begin{array}{rcll}
S^{(2)}_n & = & \sum_{1\le k\le n}k^2 = \sum_{1\le j\le k\le n}k\\
& = & \sum_{1\le j\le n} \sum_{1\le k\le n}k\\
& = & \sum_{1\le j\le n} \left(\frac{j+n}{2}\right)(n - j + 1)\\
& = & \frac{1}{2}\sum_{1\le j\le n} \left(n(n+1) + j - j^2\right)\\
& = & \frac{1}{2}n^2(n+1) + \frac{1}{4}n(n+1) - \frac{1}{2}S^{(2)}_n.
\end{array}
$$

**Method 6**: Use finite calculus.

**Method 7**: Use generating functions.

---

**Method 8**: Use telescoping sum. Method of differences.

$$
\begin{array}{rcll}
S^{(2)}_n + S^{(1)}_n & = & \sum_{1\le k\le n}k(k+1)\\
& = & \sum_{1\le k\le n}k(k+1) \cdot \frac{1}{3}\left((k+2) - (k-1)\right)\\
& = & \frac{1}{3} \sum_{1\le k\le n}\left(k(k+1)(k+2) - (k-1)k(k+1)\right)\\
& = & \frac{1}{3} \sum_{1\le k\le n}k(k+1)(k+2) - \frac{1}{3} \sum_{0\le k\le n-1}k(k+1)(k+2)\\
& = & \frac{1}{3} n(n+1)(n+2).
\end{array}
$$

---

### 2.5 Finite and Infinite Calculus

Finite calculus is based on the properties of the difference operator $\Delta$, defined by

$$
\Delta f(x) = f(x + 1) − f(x).
$$

The quantity $x^{\underline{m}}=x(x-1)\cdots(x-m+1)$ is called "x to the m falling"; similarly, $x^{\overline{m}}=x(x+1)\cdots(x+m-1)$ is "x to the m rising". These functions are also called **falling factorial powers** and **rising factorial powers**. Falling powers $x^{\underline{m}}$ are especially nice with respect to $\Delta$. We have

$$
\Delta x^{\underline{m}} = m x^{\underline{m-1}}.
$$

---

$\Delta$ has as an inverse, the anti-difference (or summation) operator $\sum$; and there's another Fundamental Theorem:

$$
g(x) = \Delta f(x) \quad \text{if and only if} \quad \sum g(x) \delta x = f(x) + C.
$$

Finite calculus has definite sums: If $g(x) = \Delta f(x)$, then

$$
\sum_a^b g(x) \delta x = f(x) \bigg|_a^b = f(b) − f(a).
$$

When $a$ and $b$ are integers with $b \ge a$:

$$
\sum_a^b g(x) \delta x = \sum_{k=a}^{b-1} g(x) = \sum_{a \le k < b} g(k).
$$

---

Deffinite summation gives us a simple way to compute sums of falling powers:

$$
\sum_{0 \le k < n} k^{\underline{m}} = \frac{k^{\underline{m+1}}}{m+1} \bigg|_0^{n} = \frac{n^{\underline{m+1}}}{m+1} \; \text{for integers} \; m,n \ge 0.
$$

 A simple calculation shows that $k^3 = k^{\underline{3}} + 3k^{\underline{2}} + k^{\underline{1}}$. Thus

$$
\sum_{a\le k < b}k^3 = \frac{k^{\underline{4}}}{4} + k^{\underline{3}} + \frac{k^{\underline{1}}}{2} \bigg|_a^b.
$$

---

Our general deffinition for negative falling powers is

$$
x^{\underline{-m}} = \frac{1}{(x+1)(x+2)\cdots(x+m-1)}, \; \text{for} \;m>0.
$$

With this definition, we have a falling-power version of the general law of exponents:

$$
x^{\underline{m+n}} = x^{\underline{m}} (x-m)^{\underline{n}}.
$$

We can now give a complete description of the sums of falling powers:

$$
\sum_a^b x^{\underline{m}} \delta x =
\left\{
\begin{array}{ll}
\frac{x^{\underline{m+1}}}{m+1}\bigg|_a^b, & \text{if} \; m \ne -1;\\
H_x \bigg|_a^b, & \text{if} \; m = -1.
\end{array}
\right.
$$

---

The difference of a discrete exponential function $c^x$ is

$$
\Delta (c^x) = (c-1)c^x.
$$

Using the shift operator $Ef(x) = f(x+1)$, we get  a compact rule for the difference of a product:

$$
\Delta(uv) = u \Delta v + Ev \Delta u
$$

Taking the indefinite sum on both sides of this equation, and rearranging its terms, yields the advertised rule for summation by parts:

$$
\sum u\Delta v = uv - \sum Ev \Delta u,
$$

This rule is useful when the sum on the left is harder to evaluate than the one on the right. For example, it can be used to evaluate the sum $\sum_{k=0}^n k 2^k$.

---

### 2.6 Infinite Sums

Any real number $x$ can be written as the difference of its positive and negative parts, $x = x^+ + x^-$, where $x^+ = x \cdot [x > 0]$ and $x^- = -x \cdot [x < 0]$.

Let $A^+ = \sum_{k\in K} a_k^+$ and $A^− = a_k^-$. If $A^+$ and $A^−$ are both finite, the sum $\sum_{k\in K} a_k$ is said to **converge absolutely** to the value $A = A^+ − A^−$.

Each of our transformation rules preserves the value of all absolutely convergent sums.

* The distributive law.
* The associative law.
* The commutative law.
* The fundamental principle of multiple sums: absolutely convergent sums over two or more indices can always be summed first with respect to any one of those indices.

---

## 3 Integer Functions

---

### 3.1 Floors and Ceilings

The floor (greatest integer) and ceiling (least integer) functions:

$$
\lfloor x \rfloor = \text{the greatest integer less than or equal to} \; x;\\
\lceil x \rceil = \text{the greatest integer less than or equal to} \; x.
$$

We have

$$
x − 1 < \lfloor x \rfloor \le x \le \lceil x \rceil < x + 1.
$$

The difference between $x$ and $\lfloor x \rfloor$ is called the fractional part of $x$, and it arises often enough in applications to deserve its own notation:

$$
\{ x \} = x - \lfloor x \rfloor.
$$

---

### 3.2 Floor/Ceiling Applications

The length of $n$ written in binary is $\lceil \log (n+1) \rceil$.

Let $f(x)$ be any continuous, monotonically increasing function with the property that $f(x) = \text{integer} \Longrightarrow x = \text{integer}$. Then we have

$$
\lfloor f(x) \rfloor = \lfloor f(\lfloor x \rfloor) \rfloor \quad \text{and} \quad \lceil f(x) \rceil = \lceil f(\lceil x \rceil) \rceil.
$$

An important special case of this theorem is

$$
\lfloor \frac{x+m}{n} \rfloor = \lfloor \frac{\lfloor x \rfloor+m}{n} \rfloor \quad \text{and} \quad \lceil \frac{x+m}{n} \rceil = \lceil \frac{\lceil x \rceil+m}{n} \rceil.
$$

---

**Level 4 - "must do" problems**: given an explicit set $X$ and an explicit property $P(x)$, find a necessary and sufficient condition $Q(x)$ that $P(x)$ is true.
**Level 5 - "pure research" problems**: given an explicit set $X$, find an interesting property $P(x)$ of its elements.

$$
\,\\
\,\\
$$

**Dare to pose level 5 problems**: this is real mathematics.

---

What is a necessary and sufficient condition that $\lceil \sqrt{\lfloor x \rfloor} \rceil = \lceil \sqrt{x} \rceil$? The answer is when $x = 0$ or $m^2 + 1 \le x \le (m + 1)^2$, we get equality.

How many integers are contained in these intervals? We have the following facts:

$$
\begin{array}{ccc}
\text{interval} & \text{integers contained} & \text{restrictions}\\
[\alpha, \beta] & \lfloor \beta \rfloor - \lceil \alpha \rceil + 1 & \alpha \le \beta,\\
[\alpha, \beta) & \lceil \beta \rceil - \lceil \alpha \rceil & \alpha \le \beta,\\
(\alpha, \beta] & \lfloor \beta \rfloor - \lfloor \alpha \rfloor & \alpha \le \beta,\\
(\alpha, \beta) & \lceil \beta \rceil - \lfloor \alpha \rfloor - 1 & \alpha < \beta.
\end{array}
$$

How many integers $n$, where $1 \le n \le N$, satisfy the relation $\lfloor \sqrt[3]{n} \rfloor \; \backslash \; n$? The answer is

$$
W = \lfloor N/K \rfloor + \frac{1}{2}K^2 + \frac{5}{2}K - 3, \quad K = \lfloor \sqrt[3]{N} \rfloor.
$$

---

We define the spectrum of a real number $\alpha$ to be an inffinite multiset of integers:

$$
\text{Spec}(\alpha) = \{ \lfloor \alpha \rfloor, \lfloor 2\alpha \rfloor, \ldots \}.
$$

The number of elements in $\text{Spec}(\alpha)$ that are $\le n$ is

$$
N(\alpha, n) = \lceil (n+1) / \alpha \rceil.
$$

The positive integers are the disjoint union of $\text{Spec}(\sqrt{2})$ and $\text{Spec}(2+\sqrt{2})$ because of the neat identity $\frac{1}{\sqrt{2}} + \frac{1}{2+\sqrt{2}} = 1$. We say that these spectra form a partition of the positive integers.

---

### 3.3 Floor/Ceiling Recurrences

A more authentic Josephus problem is to eliminate every $q$-th person. The survivor $J_q(n)$ is $qn + 1 − D^{(q)}_k$, where $k$ is as small as possible such that $D^{(q)}_k > (q − 1)n$ and

$$
\begin{array}{l}
D^{(q)}_0 = 1;\\
D^{(q)}_n = \lceil \frac{q}{q-1} D^{(q)}_{n-1} \rceil \quad \text{for} \quad n > 0.
\end{array}
$$

---

### 3.4 'mod': The Binary Operation

We define 'mod' as a binary operation:

$$
x \mod y = x − y \lceil x/y \rceil, \; \text{for} \; y \ne 0.
$$

The partition of $n$ into $m$ as-equal-as-possible parts in nondecreasing order is:

$$
n = \lfloor \frac{n}{m} \rfloor + \lfloor \frac{n+1}{m} \rfloor + \cdots + \lfloor \frac{n + m - 1}{m} \rfloor.
$$

If we replace $n$ by $\lfloor x \rfloor$, we get an identity that holds for all real $x$:

$$
\lfloor mx \rfloor = \lfloor x \rfloor + \lfloor x + \frac{1}{m} \rfloor + \cdots + \lfloor x + \frac{m - 1}{m} \rfloor.
$$

---

### 3.5 Floor/Ceiling Sums

 If $\alpha$ is irrational then the fractional parts $\{n \alpha\}$ are very uniformly distributed between $0$ and $1$, as $n \rightarrow \infty$:

$$
\lim_{n \rightarrow \infty} \frac{1}{n} \sum_{1 \le k < n} f\left(\{ k \alpha \}\right) = \int_0^1 f(x) dx.
$$

We define the discrepancy $D(\alpha, n)$ to be the maximum absolute value, over all $0 \le v \le 1$, of the sum

$$
s(\alpha, n, v) = \sum_{0\le k<n} \left( \left[ \{ k\alpha \} < v \right] - v \right).
$$

$D(\alpha, n)$ is much smaller than $n$, when $n$ is sufficiently large. The idea is that a certain sum $s(\alpha, n, v)$ of $n$ terms can be reduced to a similar sum of at most $\lceil \alpha n \rceil$ terms.

---

We can prove a "reciprocity law" for all real $x$:

$$
\sum_{0 \le k < m} \lfloor \frac{n k + x}{m} \rfloor = d \lfloor \frac{x}{d} \rfloor  + \frac{(m-1)(n-1)}{2} + \frac{d-1}{2} = \sum_{0 \le k < n} \lfloor \frac{m k + x}{n} \rfloor.
$$

---

## 4 Number Theory

---

### 4.1 Divisibility

We say that $m$ divides $n$ (or $n$ is divisible by $m$) if $m$ > 0 and the ratio $n/m$ is an integer:

$$
m \backslash n \iff m > 0 \; \text{and} \; n = mk \; \text{for some integer} \; k.
$$

The **greatest common divisor** of two integers $m$ and $n$ is the largest integer that divides them both:

$$
\gcd(m, n) = \max \{ k | k \backslash m \; \text{and} \; k \backslash n \}.
$$

The **least common multiple** of two integers $m$ and $n$ is

$$
\text{lcm}(m, n) = \min \{ k | k > 0, m \backslash k \; \text{and} \; n \backslash k \}.
$$

---

One of the nicest properties of the gcd is that it is easy to compute, using a 2300-year-old method called Euclid's algorithm（辗转相除）:

$$
\begin{array}{l}
\gcd(0, n) = n ;\\
\gcd(m, n) = \gcd(n \mod m, m), \; \text{for} \; m > 0.
\end{array}
$$

---

### 4.2 Primes

A positive integer $p$ is called **prime** if it has just two divisors, namely $1$ and $p$. The numbers that have three or more divisors are called **composite**.

Any positive integer $n$ can be written as a product of primes, which is called the Fundamental Theorem of Arithmetic:

$$
n = p_1 \cdots p_m = \prod_{k=1}^m p_k, \quad p_1 \le \cdots \le p_m.
$$

---

### 4.3 Prime Examples

Euclid numbers:

$$
e_n = e_1e_2 \cdots e_{n-1} + 1, \; n \ge 1.
$$

Mersenne numbers:

$$
2^p - 1, \; p \; \text{is prime}.
$$

The prime number theorem:

$$
\pi(x) \sim \frac{x}{\ln x},
$$

where $\pi(x)$ denotes the number of primes not exceeding $x$. One simple way to calculate all $\pi(x)$ primes $\le x$ is to form the so-called sieve of Eratosthenes.

---

### 4.4 Factorial Factors

To approximate $n!$ more accurately for large $n$ we can use Stirling's
formula,

$$
n! \sim \sqrt{2\pi n}\left(\frac{n}{e}\right)^n.
$$

For any given prime $p$, we denote the largest power of $p$ that divides $n!$ by $\epsilon_p(n!)$. We have

$$
\epsilon_p(n!) = n - \nu_p(n),
$$

where $\nu_p(n)$ is the number of $1$'s in the $p$-ary representation of $n$.

---

### 4.5 Relative Primality

When $\gcd(m,n) = 1$, the integers $m$ and $n$ have no prime factors in common and we say that they're relatively prime, $m \perp n$.

The Farey series of order $N$, denoted by $\mathcal{F}_N$, is the set of all reduced fractions between $0$ and $1$ whose denominators are $N$ or less, arranged in increasing order. $\mathcal{F}_N$ defines a subtree of the **Stern-Brocot tree**.

We can regard the tree as a number system for representing rational numbers. Let's use the letters $L$ and $R$ to stand for going down to the left or right branch; then a string of $L$'s and $R$'s uniquely identities a number.

---

$e$'s representation has a regular pattern in the Stern-Brocot system:

$$
e = RL^0RLR^2LRL^4RLR^6LRL^8RLR^{10}LRL^{12}RL \ldots.
$$

There's an intimate relationship between Euclid's algorithm and the Stern-Brocot representations of rationals. Given $\alpha = \frac{m}{n}$, we get $\lfloor \frac{m}{n} \rfloor$ $R$'s, then $\lfloor \frac{n}{m \mod n} \rfloor$ $L$'s, then $\lfloor \frac{m \mod n}{n \mod (m \mod n)} \rfloor$ $R$'s, and so on. These numbers $m \mod n$, $n \mod (m \mod n)$ are just the values examined in Euclid's algorithm.

---

### 4.6 'MOD': The Congruence Relation

Modular arithmetic is one of the main tools provided by number theory.

$$
a \equiv b \; (\mod m) \iff a \mod m = b \mod m.
$$

Congruence is an equivalence relation, it satisfies the reflexive law, the symmetric law, and the transitive law. Most of the algebraic operations that we customarily do with equations can also be done with congruences, such as addition, subtraction and multiplication. The operation of division is conspicuously absent.

$$
ad \equiv bd \iff a = b (\mod \frac{m}{\gcd(m, d)}).
$$

Finding $d'$ and $m'$ such that $d'd + m'm = 1$. We call $d'$ the "inverse of $d$ modulo $m$".

---

A special case of the **Chinese Remainder Theorem** is that if $m \perp n$, then

$$
a \equiv b (\mod mn) \iff a \equiv b (\mod m) \; \text{and} \; a \equiv b (\mod n).
$$

Congruences modulo powers of primes are the building blocks for all congruences modulo integers.

$$
a \equiv b (\mod m) \iff a \equiv b (\mod p^{m_p})
$$

for all $p$, if the prime factorization of $m$ is $\prod_p p^{m_p}$.

---

### 4.7 Independent Residues

One of the important applications of congruences is a **residue number system**, in which an integer $x$ is represented as a sequence of residues with respect to moduli that are prime to each other:

$$
\text{Res}(x) = (x \mod m_1, \ldots, x \mod m_r), \; \text{if} \; m_j \perp m_k \; \text{for} \; 1 \le j < k \le r.
$$

---

How to get from a given sequence of residues ($x \mod m_1, \ldots, x \mod m_r$) back to $x \mod m$, where $m=m_1 \cdots m_r$?

* The key idea is to solve the problem in the two cases $(1, 0)$ and $(0, 1)$; for if $(1, 0) = a$ and $(0, 1) = b$, then $(x, y) = (ax + by) \mod m n$.
* The way to find numbers $a$ and $b$ is to using Euclid's algorithm to first find $m_0$ and $n_0$ such that $m'n + mn' = 1$ and taking $a = n'n$ and $b = m'm$.

---

How many solutions are there to the congruence $x^2 \equiv 1 (\mod m)$?

* First consider the case that $m$ is a prime power, $p^k$, where $k > 0$.
* If $p > 2$, there are exactly two solutions, $x \equiv +1$ and $x \equiv -1$.
* If $p = 2$, there are four solutions when $k \ge 3$, namely $x \equiv \plusmn 1$ and $x \equiv 2^{k-1} \plusmn 1$.

---

### 4.8 Additional Applications

If $m \perp n$ and $j \in [0, m)$, the solution of the congruence $kn \equiv j (\mod m)$ is $k = j n' \mod m$, where $m'm + n'n = 1$.

Fermat's Little Theorem.

$$
n^{p-1} \equiv 1 (\mod p), \; \text{if} \; n \perp p.
$$

Wilson's theorem.

$$
(n - 1)! \equiv -1 (\mod n) \iff n \; \text{is prime, if} \; n > 1.
$$

---

### 4.9 Phi and Mu

The $\phi$ function is called Euler's totient function, which means the number of integers $\{0, 1, \ldots, m-1\}$ that are relatively prime to $m$.

Fermat's theorem can be generalized to nonprime moduli:

$$
n^{\phi(m)} \equiv 1, \; \text{if} \; n \perp m.
$$

* If $m$ is a prime power $p^k$, $\phi(p^k) = p^k - p^{k-1}$.
* If $m > 1$ is not a prime power, $\phi(m) = \phi(m_1) \phi(m_2)$, where $m = m_1m_2$ and $m_1 \perp m2$.

The value of Euler's totient function for general $m$:

$$
\phi(m) = \prod_{p \backslash m} (p^{m_p} - p^{m_p-1}) = m \prod_{p \backslash m} \left(1 - \frac{1}{p}\right).
$$

---

The M$\"o$bius function $\mu(m)$ can be defined for all integers $m \ge 1$ by the equation

$$
\sum_{d \backslash m} \mu(d) = \left[ m = 1\right].
$$

Inversion principle.

$$
g(m) = \sum_{d \backslash m} f(d) \iff f(m) = \sum_{d \backslash m} \mu(d) g(\frac{m}{d}).
$$

We have the general formula

$$
\mu(m) = \prod_{p \backslash m} \mu(p^{m_p}) = \left\{ \begin{array}{ll}
(-1)^{r}, & \text{if} \; m = p_1 p_2 \cdots p_r;\\
0, & \text{if} \; m \; \text{is divisible by some} \; p^2.
\end{array} \right.
$$

---

Let $\Phi(x) = \sum_{1 \le k \le x} \phi(k)$ be number of reduced fractions in $[0, 1]$ whose denominators do not exceed $n$, we have $\sum_{d \ge 1}\Phi(\frac{x}{d}) = \frac{1}{2} \lfloor x \rfloor \lfloor x + 1\rfloor$. By using another property of the M$\"o$bius function, we have

$$
\Phi(x) = \frac{1}{2}\sum_{d \ge 1} \mu(d) \lfloor \frac{x}{d} \rfloor \lfloor \frac{x}{d} + 1\rfloor.
$$

---

## 5 Binomial Coefficients

$\big(\begin{smallmatrix}n\\k\end{smallmatrix}\big)$ can be read "$n$ choose $k$".

---

### 5.1 Basic Identities

Eq. 1 - Factorial expansion.

$$
\begin{pmatrix}n\\k\end{pmatrix} = \left\{ \begin{array}{ll}
\frac{n(n-1)\cdots(n-k+1)}{k(k-1)\cdots 1} = \frac{n^{\underline{k}}}{k!} = \frac{n!}{k!(n-k)!}, & n \ge k \ge 0;\\
0, & k < 0 \; \text{or} \; k > n.
\end{array} \right.
$$

Eq.2 - Symmetry.

$$
\begin{pmatrix}n\\k\end{pmatrix} = \begin{pmatrix}n\\n - k\end{pmatrix}.
$$

Eq. 3 - Absorption.

$$
k \begin{pmatrix}r\\k\end{pmatrix} = r \begin{pmatrix}r - 1\\k - 1\end{pmatrix}.
$$

---

Eq. 4 - Addition. What is the interpretation?

$$
\begin{pmatrix}r\\k\end{pmatrix} = \begin{pmatrix}r - 1\\k\end{pmatrix} + \begin{pmatrix}r - 1\\k - 1\end{pmatrix}.
$$

Eq. 5 - Upper negation.

$$
\begin{pmatrix}r\\k\end{pmatrix} = (-1)^k \begin{pmatrix}k - r - 1\\k\end{pmatrix}.
$$

---

Eq. 6 - Multinomial Theorem & multinomial revision.

$$
\begin{array}{rcl}
 & & (x_1 + x_2 + \cdots + x_m)^n\\
 & = & \sum_{\substack{a_1 \le a_2 \le \cdots \le a_m \\ a_1 + a_2 + \cdots + a_m = n}}x_1^{a_1}x_2^{a_2}\cdots x_m^{a_m}\cdot\begin{pmatrix}a_1+a_2+\cdots+a_m\\a_1,a_2,\ldots,a_m\end{pmatrix}\\
 & = & \sum_{\substack{a_1 \le a_2 \le \cdots \le a_m \\ a_1 + a_2 + \cdots + a_m = n}}x_1^{a_1}x_2^{a_2}\cdots x_m^{a_m}\cdot\frac{(a_1 + a_2 + \cdots + a_m)!}{a_1!a_2!\cdots a_m!}\\
 & = & \sum_{\substack{a_1 \le a_2 \le \cdots \le a_m \\ a_1 + a_2 + \cdots + a_m = n}}x_1^{a_1}x_2^{a_2}\cdots x_m^{a_m}\cdot\begin{pmatrix}a_1+a_2+\cdots+a_m\\a_2+\cdots+a_m\end{pmatrix}\cdots \begin{pmatrix}a_{m-1}+a_m\\a_m\end{pmatrix}.
\end{array}
$$

---

Eq. 7 - Binomial Theorem.

$$
(x+y)^r = \sum_{k} \begin{pmatrix}r\\k\end{pmatrix}x^r y^{r-k}.
$$

 We can do columns, but there is no closed form for the partial sum of a row of Pascal's triangle (except the entries have been given alternating signs or been multiplied by their distance from the center). The relation between these partial sums is analogous to the relation between the integrals (why?)

$$
\int^\alpha_{-\infty} x e^{-x^2} dx = -\frac{1}{2} e^{-\alpha^2} \; \text{and} \; \int^\alpha_{-\infty} e^{-x^2} dx.
$$

A curious relationship.

$$
\sum_{k \le m} \begin{pmatrix}m+r\\k\end{pmatrix}x^r y^{m-k} = \sum_{k \le m} \begin{pmatrix}-r\\k\end{pmatrix}(-x)^k (x+y)^{m-k}.
$$

---

Eq. 8 - Parallel summation. What is the interpretation?

$$
\sum_{k \le n} \begin{pmatrix}r+k\\k\end{pmatrix} = \begin{pmatrix}r+n+1\\n\end{pmatrix}.
$$

Eq. 9 - Upper summation. What is the interpretation?

$$
\sum_{0 \le k \le n} \begin{pmatrix}k\\m\end{pmatrix} = \begin{pmatrix}n+1\\m+1\end{pmatrix}.
$$

---

Eq. 10 - Chu-Vandermonde formula. What is the interpretation? 四元玉鉴·果垛叠藏.

$$
\sum_k \begin{pmatrix}r\\m+k\end{pmatrix} \begin{pmatrix}s\\n-k\end{pmatrix} = \begin{pmatrix}r+s\\m+n\end{pmatrix}.
$$

The hairiest sum of binomial coefficients.

$$
\sum_{k_{ij}} (-1)^{\sum_{i<j}k_{ij}} \prod_{1 \le i < j < n} \begin{pmatrix}a_i+a_j\\a_j + k_{ij}\end{pmatrix} \prod_{1 \le j < n} \begin{pmatrix}a_j + a_n\\a_n + \sum_{i<j}k_{ij} - \sum_{i>j}k_{ij}\end{pmatrix} = \begin{pmatrix}a_1+\cdots+a_n\\a_1,\ldots,a_n\end{pmatrix}.
$$

---

### 5.2 Basic Practice

---

Problem 1: A sum of ratios. Multinomial revision.

$$
\sum_{k=0}^m \frac{\begin{pmatrix}m\\k\end{pmatrix}}{\begin{pmatrix}n\\k\end{pmatrix}} = \frac{n+1}{n+1-m}, \; n \ge m \ge 0.
$$

---

Problem 2: From the literature of sorting. Absorption identity.

$$
T = \sum_{k=0}^n k\frac{\begin{pmatrix}m-k-1\\m-n-1\end{pmatrix}}{\begin{pmatrix}m\\n\end{pmatrix}} = \frac{n}{m-n+1}, \; m > n \ge 0.
$$

---

Problem 3: From an old exam. Recurrence, periodic.

$$
R_n = \sum_{k \le n} \begin{pmatrix}n - k\\k\end{pmatrix}(-1)^k = \left\{ \begin{array}{ll}
R_1 = 1, & \text{if} \; n - 1;\\
R_2 = 0, & \text{if} \; n \; \text{is odd};\\
R_4 = -1, & \text{if} \; n > 0 \; \text{is even}.
\end{array} \right..
$$

---

Problem 4: A sum involving two binomial coefficients. Handled in the general form.

$$
\sum_{k=0}^n \begin{pmatrix}k\\1\end{pmatrix} \begin{pmatrix}m - k - 1\\m - n - 1\end{pmatrix} = \begin{pmatrix}m\\m - n + 1\end{pmatrix}.
$$

---

Problem 5: A sum with three factors. Absorption identity.

$$
\sum_{k} \begin{pmatrix}n\\k\end{pmatrix} \begin{pmatrix}s\\k\end{pmatrix} k = s\begin{pmatrix}n+s-1\\n-1\end{pmatrix}.
$$

---

Problem 6: A sum with menacing characteristics. Remove $k$.

$$
\sum_{k \ge 0} \begin{pmatrix}n+k\\2k\end{pmatrix} \begin{pmatrix}2k\\k\end{pmatrix} \frac{(-1)^k}{k+1} = 0.
$$

---

Problem 7: A new obstacle.

$$
\sum_{k \ge 0} \begin{pmatrix}n+k\\m+2k\end{pmatrix} \begin{pmatrix}2k\\k\end{pmatrix} \frac{(-1)^k}{k+1}.
$$

---

Problem 8: A different obstacle.

$$
\sum_{k \ge 0} \begin{pmatrix}n+k\\2k\end{pmatrix} \begin{pmatrix}2k\\k\end{pmatrix} \frac{(-1)^k}{k+1+m} = (-1)^n m^{\underline{n}}m^{\underline{-n-1}}.
$$

---

### 5.3 Tricks of the Trade

---

Trick 1: Going halves.

$$
\begin{pmatrix}-1/2\\n\end{pmatrix}=\left(\frac{-1}{4}\right)^n\begin{pmatrix}2n\\n\end{pmatrix}.
$$

Trick 2: High-order differences. Newton series.

$$
f(x) = \Delta^df(0)\begin{pmatrix}x\\d\end{pmatrix} + \Delta^{d-1}f(0)\begin{pmatrix}x\\d-1\end{pmatrix} + \cdots + f(0)\begin{pmatrix}x\\0\end{pmatrix}.
$$

Trick 3: Inversion. Rather like the M$\"{o}$bius inversion formulas.

---

### 5.4 Generating Functions

---

An inffinite sequence $<a_0, a_1, a_2, \ldots>$ can be represented as a power series in an auxiliary variable $z$,

$$
A(z) = \sum_{z \ge 0}a_k z^k.
$$

The binomial theorem.

$$
(1+z)^r = \sum_{k \ge 0} \begin{pmatrix}r\\k\end{pmatrix} z^k.
$$

---

Let $A(z)$ be the generating function for $<a_0, a_1, a_2, \ldots>$, and let $B(z)$ be the generating function for another sequence $<b_0, b_1, b_2, \ldots>$. Then $A(z)B(z)$ is the generating function for the sums $<c_0, c_1, c_2, \ldots>$ where $c_n = \sum_{k=0}^n a_k b_{n-k}$.

If $A(z)$ is the generating function for the summands $<a_0, a_1, a_2, \ldots>$, then $A(z)/(1 - z)$ is the generating function for the sums $<c_0, c_1, c_2, \ldots>$ where $c_n = \sum_{k=0}^n a_k$.

---

The generalized binomial series:

$$
\mathcal{B}_t(z) = \sum_{k \ge 0}(tk)^{\underline{k-1}}\frac{z^k}{k!}.
$$

A relation that shows further connections between the functions $\mathcal{B}_{-1}(z)$ and $\mathcal{B}_{2}(z)$:

$$
\begin{array}{rcl}
\frac{\mathcal{B}_{-1}(z)^{n+1}-(-z)^{n+1}\mathcal{B}_2(-z)^{n+1}}{\sqrt{1+4z}} & = & \sum_{k
\le n} \begin{pmatrix}n-k\\k\end{pmatrix} z^k.\\
\end{array}
$$

---

$$
\begin{array}{rcl}
\mathcal{B}_2(z) & = & \sum_k \begin{pmatrix}2k+1\\k\end{pmatrix} \frac{1}{1+2k}z^k = \frac{1-\sqrt{1-4z}}{2z}.\\
\mathcal{B}_2(z)^r & = & \sum_k \begin{pmatrix}2k+r\\k\end{pmatrix} \frac{1}{r+2k}z^k.\\
\frac{\mathcal{B}_2(z)^r}{\sqrt{1-4z}} & = & \sum_k \begin{pmatrix}2k+r\\k\end{pmatrix} z^k.\\
\mathcal{B}_{-1}(z) & = & \sum_k \begin{pmatrix}1-k\\k\end{pmatrix} \frac{1}{1-k}z^k = \frac{1+\sqrt{1+4z}}{2z}.\\
\mathcal{B}_{-1}(z)^r & = & \sum_k \begin{pmatrix}r-k\\k\end{pmatrix} \frac{r}{r-k}z^k.\\
\frac{\mathcal{B}_{-1}(z)^r}{\sqrt{1+4z}} & = & \sum_k \begin{pmatrix}r-k\\k\end{pmatrix} z^k.\\
\end{array}
$$

---

The generalized exponential series:

$$
\mathcal{E}_t(z) = \sum_{k \ge 0}(tk+1)^{k-1}\frac{z^k}{k!}.
$$

The coefficients $(\begin{smallmatrix}2n\\n\end{smallmatrix})\frac{1}{n+1}$ of $B_2(z)=\frac{1-\sqrt{1-4z}}{2z}$ are called the Catalan numbers $C_n$.

---

### 5.5 Hypergeometric Functions

---

The general hypergeometric series is a power series in $z$ with $m + n$
parameters.

$$
F\left(\begin{matrix}a_1,\ldots,a_m\\b_1,\ldots,b_n\end{matrix}\middle|z\right) = \sum_{k \ge 0} \frac{a_1^{\overline{k}} \cdots a_m^{\overline{k}}}{b_1^{\overline{k}} \cdots b_n^{\overline{k}}} \frac{z^k}{k!}.
$$

---

Many important functions occur as special cases of the general hypergeometric.

$$
F\left(\begin{matrix}a\\b\end{matrix}\middle|z\right) = M(a,b,z),\\
F\left(\begin{matrix}a,1\\1\end{matrix}\middle|z\right) = \frac{1}{(1-z)^a},\\
F\left(\begin{matrix}1\\b,1\end{matrix}\middle|z\right) = I_{b-1}(2\sqrt{z})\frac{(b-1)!}{z^{(b-1)/2}},\\
$$

where $M$ is called a "confluent hypergeometric series", $I_{b-1}$ is called a "modified Bessel function" of order $b - 1$.

---

The Gaussian hypergeometric:

$$
F\left(\begin{matrix}a,b\\c\end{matrix}\middle|z\right) = \sum_{k \ge 0} \frac{a^{\overline{k}} b^{\overline{k}}}{c^{\overline{k}}} \frac{z^k}{k!}.
$$

Gauss's hypergeometric series can be written in the recursively factored form

$$
F\left(\begin{matrix}a,b\\c\end{matrix}\middle|z\right) = 1 + \frac{a}{1} \frac{b}{c} z\left(1 + \frac{a+1}{2}\frac{b+1}{c+1}z \left(1+\frac{a+2}{3}\frac{b+2}{c+2}z(1+\cdots) \right) \right).
$$

---

A general identity of Vandermonde's convolution.

$$
F\left(\begin{matrix}a,b\\c\end{matrix}\middle|1\right) = \frac{\Gamma(c-a-b)\Gamma(c)}{\Gamma(c-a)\Gamma(c-b)},
$$

where integer $b \le 0$ or $\mathcal{R}c>\mathcal{R}a+\mathcal{R}b$.

Dixon's formula.

$$
F\left(\begin{matrix}a,b,c\\1+c-a,1+c-b\end{matrix}\middle|1\right) = \frac{(c/2)!}{c!}\frac{(c-a)^{\underline{c/2}}(c-b)^{\underline{c/2}}}{(c-a-b)^{\underline{c/2}}},
$$

where integer $c \le 0$ or $\mathcal{R}c/2 + 1>\mathcal{R}a+\mathcal{R}b$.

---

### 5.6 Hypergeometric Transformations

---

Pfaff's reflection law:

$$
\frac{1}{(1-z)^a} F\left(\begin{matrix}a,b\\c\end{matrix}\middle|\frac{-z}{1-z}\right) = F\left(\begin{matrix}a,c-b\\c\end{matrix}\middle|z\right).
$$

---

The general hypergeometric function $F\left(\begin{matrix}a_1,\ldots,a_m\\b_1,\ldots,b_n\end{matrix}\middle|z\right)$ satisfies the differential equation

$$
D(\vartheta+b_1-1) \ldots D(\vartheta+b_n-1)F = (\vartheta+a_1) \ldots (\vartheta+a_m)F,
$$

where $D$ is the operator $\frac{d}{dz}$, $\vartheta$ is the operator $z\frac{d}{dz}$.

---

### 5.7 Partial Hypergeometric Sums

---

Gosper discovered a beautiful way to find indefinite sums $\sum t(k) \delta k$ whenever $t$ belong to hypergeometric terms.

* Step 1: express the term ratio in the special form $\frac{t(k+1)}{t(k)} =\frac{p(k+1)}{p(k)}\frac{q(k)}{r(k+1)}$, where $p$, $q$, and $r$ are polynomials subject to the following condition: $(k + \alpha) \backslash q(k)$ and $(k + \beta) \backslash r(k) \Longrightarrow \alpha - \beta$ is not a positive integer.
* Step 2: find a hypergeometric term $T(k)$ such that $t(k) = T(k+1) - T(k)$, where $T(k) = \frac{r(k)s(k)t(k)}{p(k)}$. If we can find a polynomial $s(k)$ satisfying $p(k) = q(k)s(k + 1) - r(k)s(k)$ we've found $\sum t(k) \delta k$; otherwise, there's no $T$.

---

Marko Petkov$\v{s}$ek has found a nice way to generalize Gosper's algorithm to more complicated inversion problems, by showing how to determine all hypergeometric terms $T(k)$ that satisfy the $l$th-order recurrence

$$
t(k) = p_l(k)T(k+l) + \cdots + p_0(k)T(k).
$$

---

### 5.8 Mechanical Summation

---

The Gosper-Zeilberger algorithm.

![bg right:66% fit](Concrete_Mathematics/Algorithm_Gosper-Zeilberger.png)

---

The Gosper-Zeilberger algorithm is guaranteed to succeed in an enormous number of cases, namely whenever the summand $t(n, k)$ is a so-called **proper term** - a term that can be written in the form

$$
t(n,k)=f(n,k)\frac{(a_1n+a_1'k+a_1'')!\ldots(a_pn+a_p'k+a_p'')!}{(b_1n+b_1'k+b_1'')!\ldots(b_qn+b_q'k+b_q'')!}w^nz^k,
$$

where $a_1,a_1',\ldots,a_p,a_p',b_1,b_1',\ldots,b_q,b_q'$ are integer constants.

---

The French mathematician **Roger Ap$\'e$ry** solved a long-standing problem in 1978 when he proved that the number $\zeta(3) = 1+2^{-3}+3^{-3}+4^{-3}+\cdots$ is irrational. One of the main components of his proof involved the binomial sums

$$
A_n = \sum_k \begin{pmatrix}n\\k\end{pmatrix}^2 \begin{pmatrix}n+k\\k\end{pmatrix}^2.
$$

With the **Gosper-Zeilberger** method, we are able to get Ap$\'e$ry's once-incredible recurrence

$$
(n + 1)^3A_n + (n + 2)^3A_{n+2} = (2n + 3)(17n^2+51n+39)A_{n+1}.
$$

---

## 6 Special Numbers

---

### 6.1 Stirling Numbers

---

Stirling numbers of the first kind: $\big[\begin{smallmatrix}n\\k\end{smallmatrix}\big]$ counts the number of ways to arrange $n$ objects into $k$ cycles, which can be read "$n$ cycle $k$". What is the interpretation of the following recurrence?

$$
\begin{bmatrix}n\\k\end{bmatrix} = (n-1)\begin{bmatrix}n-1\\k\end{bmatrix} + \begin{bmatrix}n-1\\k-1\end{bmatrix}.
$$

$\begin{bmatrix}n\\k\end{bmatrix}$ is the number of permutations of $n$ objects that contain exactly $k$ cycles.

$$
\sum_k \begin{bmatrix}n\\k\end{bmatrix} = n!.
$$

Stirling cycle numbers are the coefficients of ordinary powers that yield factorial powers.

$$
x^{\overline{n}} = \sum_k \begin{bmatrix}n\\k\end{bmatrix} x^{k}.
$$

---

Stirling numbers of the second kind: $\big\{\begin{smallmatrix}n\\k\end{smallmatrix}\big\}$ stands for the number of ways to partition a set of $n$ things into $k$ nonempty subsets, which can be read "$n$ subset $k$". What is the interpretation of the following recurrence?

$$
\begin{Bmatrix}n\\k\end{Bmatrix} = k\begin{Bmatrix}n-1\\k\end{Bmatrix} + \begin{Bmatrix}n-1\\k-1\end{Bmatrix}.
$$

Stirling subset numbers are the coefficients of factorial powers that yield ordinary powers, why?

$$
x^n = \sum_k \begin{Bmatrix}n\\k\end{Bmatrix} x^{\underline{k}}.
$$

---

Inversion formulas:

$$
\sum_{k} \begin{bmatrix}n\\k\end{bmatrix} \begin{Bmatrix}k\\m\end{Bmatrix}(-1)^{n-k} = \sum_{k} \begin{Bmatrix}n\\k\end{Bmatrix}\begin{bmatrix}k\\m\end{bmatrix}(-1)^{n-k} = [m=n].
$$

The two kinds of Stirling numbers are related by an extremely simple law

$$
\begin{bmatrix}n\\k\end{bmatrix} = \begin{Bmatrix}-k\\-n\end{Bmatrix}.
$$

---

### 6.2 Eulerian Numbers

---

Eulerian numbers: $\left< \begin{matrix}n\\k\end{matrix} \right>$ is the number of permutations $\pi_1\pi_2 \cdots \pi_n$ of $\{1, 2, \ldots, n\}$ that have $k$ ascents, namely, $k$ places where $\pi_j < \pi_{j+1}$.

The symmetry law:

$$
\left< \begin{matrix}n\\k\end{matrix} \right> = \left< \begin{matrix}n\\n-1-k\end{matrix} \right>.
$$

The recurrence:

$$
\left< \begin{matrix}n\\k\end{matrix} \right> = (k+1)\left< \begin{matrix}n-1\\k\end{matrix} \right> + (n-k)\left< \begin{matrix}n-1\\k-1\end{matrix} \right>.
$$

---

Worpitzky's identity: an unusual connection between ordinary powers and consecutive binomial coefficients

$$
x^n = \sum_k \left< \begin{matrix}n\\k\end{matrix} \right> \begin{pmatrix}x+k\\n\end{pmatrix}.
$$

---

### 6.3 Harmonic Numbers

---

Given $n$ cards and a table, what is the largest possible overhang by stacking the cards up over the table's edge, subject to the laws of gravity? A similar problem is called the "worm on the rubber band".

$$
H_n = \sum_{k=1}^n \frac{1}{k}.
$$

Riemann's zeta function:

$$
\zeta(r) = H_\infty^{(r)} = \sum_{k \ge 1}\frac{1}{k^r}.
$$

Euler's constant:

$$
\gamma = \lim_{n \rightarrow \infty} (H_n - \ln n).
$$

---

### 6.4 Harmonic Summation

---

A more general sum:

$$
\sum_{0 \le k < m}\begin{pmatrix}k\\m\end{pmatrix} H_k = \begin{pmatrix}n\\m+1\end{pmatrix}(H_n - \frac{1}{n+1}).
$$

A much more general sum:

$$
U_n(x, y) = \sum_{k \ge 1} \begin{pmatrix}n\\k\end{pmatrix} \frac{(-1)^{k-1}}{k}(x+ky)^n = x^n H_n + nx^{n-1}y.
$$

---

### 6.5 Bernoulli Numbers

---

The formulas for sums of $m$th powers:

$$
S_m(n) = \sum_{k=0}^{n-1} k^m = H_{n-1}^{(-m)} = \frac{1}{m+1}\sum_{k=0}^m \begin{pmatrix}m+1\\k\end{pmatrix} B_k n^{m+1-k}.
$$

Bernoulli numbers are defined by an implicit recurrence relation

$$
\sum_{j=0}^m \begin{pmatrix}m+1\\j\end{pmatrix} B_j = [m=0].
$$

Bernoulli numbers are the coefficients of the power series

$$
\frac{z}{e^z - 1} = \sum_{n \ge 0} B_n \frac{z^n}{n!}.
$$

---

Two remarkable formulas for $z \cot z$ are

$$
z \cot z = 1 - 2 \sum_{k \ge 1}\frac{z^2}{k^2 \pi^2 - z^2} = 1 - 2 \sum_{j \ge 1} \frac{z^{2j}}{\pi^{2j}} H_\infty^{(2j)},
$$

$$
z \cot z = iz \coth iz = \frac{2iz}{e^{2iz}-1} + \frac{2iz}{2} = \sum_{n \ge 0}(-4)^n B_{2n} \frac{z^{2n}}{(2n)!},
$$

which gives us an almost miraculous closed form for infinitely many infinite sums:

$$
\zeta (2n) = H_\infty^{(2n)} = (-1)^{n-1}\frac{2^{2n-1}\pi^{2n}B_{2n}}{(2n)!}.
$$

---
Bernoulli numbers also appear in the coeficients of the tangent function:

$$
\tan z = \sum_{n \ge 0} T_{2n-1} \frac{z^{2n-1}}{(2n-1)!} = \sum_{n \ge 0} (-1)^{n-1} \frac{4^n(4^n-1)}{2n} B_{2n} \frac{z^{2n-1}}{(2n-1)!}.
$$

Bernoulli numbers are related to the constant terms in the Stirling polynomials:

$$
\frac{B_{m}}{m!} = -m \sigma_m(0).
$$

---

### 6.6 Fibonacci Numbers

Leonardo Fibonacci, 1202.

---

Fibonacci numbers are often found in nature: the bee-tree law, the florets of sunflower, reflections.

Jean-Dominique Cassini's identity is the basis of a geometrical paradox that was one of Lewis Carroll's favorite puzzles:

$$
F_{n+1}F_{n-1} - F_n^2 = (-1)^n.
$$

The divisibility property.

$$
\gcd(F_m, F_n) = F_{\gcd(m, n)}.
$$

One of the most important property is Zeckendorf's theorem, every positive integer has a unique representation of the form

$$
n = F_{k_1} + F_{k_2} + \cdots + F_{k_r}, \quad k_{i+1} \ge k_i + 2,
$$

which leads to the Fibonacci number system.

---

The generating function of the Fibonacci numbers

$$
F(z) = \sum_{n \ge 0} F_n z^n = \frac{z}{1-z-z^2} = \frac{1}{\sqrt{5}}\left( \frac{1}{1-\phi z} - \frac{1}{1-\hat{\phi}z} \right),
$$

where $\phi=\frac{1+\sqrt{5}}{2}$ is the golden ratio, $\hat{\phi}=\frac{1-\sqrt{5}}{2}$.

The closed form for the coefficient of $z^n$ is

$$
F_n = \frac{1}{\sqrt{5}} \left( \phi^n - \hat{\phi}^n\right)=\lfloor \frac{\phi^n}{\sqrt{5}} + \frac{1}{2}\rfloor.
$$

---

### 6.7 Continuants

The continuant polynomial $K_n$ is defined by the following recurrence:

$$
\begin{array}{rcl}
K_0() & = & 1;\\
K_1(x_1) & = & x_1;\\
K_n(x_1,\ldots,x_n) & = & K_{n-1}(x_1,\ldots,x_{n-1})x_n+K_{n-2}(x_1,\ldots,x_{n-2}).
\end{array}
$$

---

A Morse code sequence of length $n$ that has $k$ dashes has $n-2k$ dots and $n - k$ symbols altogether:

$$
K_n(z,\ldots,z) = \sum_{k=0}^n \begin{pmatrix}n-k\\k\end{pmatrix} z^{n-2k}.
$$

We have the identity

$$
F_{n+1} = K_n(z,\ldots,z)|_{z=1} = \sum_{k=0}^n \begin{pmatrix}n-k\\k\end{pmatrix}.
$$

A remarkable law:

$$
K_{m+n}(x_1, \ldots, x_{m+n}) K_k(x_{m+1}, \ldots, x_{m+k})\\
= K_{m+k}(x_1, \ldots, x_{m+k}) K_n(x_{m+1}, \ldots, x_{m+n})\\
+ (-1)^k K_{m-1}(x_1, \ldots, x_{m-1})K_{n-k-1}(x_{m+k+2}, \ldots, x_{m+n}).
$$

---

If Euclid's algorithm finds the greatest common divisor $d$ in $k$ steps, after computing the sequence of quotients $q_1, \ldots q_k$, then the starting numbers were $K(q_1, q_2, \ldots, q_k)d$ and $K(q_2, \ldots, q_k)d$.

Continuants are closely connected with the Stern-Brocot tree:

$$
f(R^{a_1}\cdots L^{a_{n-1}}) = \frac{K_{n+1}(a_0, a_1, \ldots, a_{n-1}, 1)}{K_{n}(a_1, \ldots, a_{n-1}, 1)}.
$$

A remarkable identity:

$$
\frac{z^{F_1}}{1+\frac{z^{F_2}}{1+\frac{z^{F_3}}{\ddots}}} = (1-z)\sum_{n \ge 1} z^{\lfloor n \phi \rfloor}.
$$

---

## 7 Generating Functions

To manipulate infinite series that "generate" those sequences.

---

### 7.1 Domino Theory and Change

---

Q1 - How many ways $T_n$ are there to completely cover a $2 \times n$ rectangle with $2 \times 1$ dominoes?

$T$ are called generating functions, because they generate the coefficients of interest:

$$
T
= \frac{\begin{smallmatrix}┃\\┃\end{smallmatrix}}{\begin{smallmatrix}┃\\┃\end{smallmatrix}-\begin{smallmatrix}┏┓\\┃┃\\┗┛\end{smallmatrix}-\begin{smallmatrix}┏━┓\\┣━┫\\┗━┛\end{smallmatrix}}
= \frac{\begin{smallmatrix}┃\\┃\end{smallmatrix}}{\begin{smallmatrix}┃\\┃\end{smallmatrix}-\begin{smallmatrix}┏┓\\┃┃\\┗┛\end{smallmatrix}-\begin{smallmatrix}\hphantom{┏}\hphantom{┏}\hphantom{┏}\\┏━┓\\┗━┛\end{smallmatrix}^2}
= \frac{1}{1-z-z^2}.
$$

$$
T_n = \sum_{m} \begin{pmatrix}n-m\\m\end{pmatrix} = F_{n+1}.
$$

Thus domino tilings are closely related to the continuant polynomials.

---

Q2 - How many ways $T_n$ are there to completely cover a $3 \times n$ rectangle with $2 \times 1$ dominoes?

$$
U = \begin{smallmatrix}┃\\┃\\┃\end{smallmatrix} + \begin{smallmatrix}┏┓\hphantom{┏}\\┃┃\hphantom{┏}\\┣┻┓\\┗━┛\end{smallmatrix}V + \begin{smallmatrix}┏━┓\\┣┳┛\\┃┃\hphantom{┏}\\┗┛\hphantom{┏}\end{smallmatrix}\Lambda + \begin{smallmatrix}┏━┓\\┣━┫\\┣━┫\\┗━┛\end{smallmatrix}U,
$$

$$
V = \begin{smallmatrix}┏┓\\┃┃\\┗┛\\\hphantom{┏}\hphantom{┏}\end{smallmatrix}U + \begin{smallmatrix}┏━┓\hphantom{┏}\\┣━┫\hphantom{┏}\\┗┳┻┓\\\hphantom{┏}┗━┛\end{smallmatrix}V,
$$

$$
\Lambda = \begin{smallmatrix}\hphantom{┏}\hphantom{┏}\\┏┓\\┃┃\\┗┛\end{smallmatrix}U + \begin{smallmatrix}\hphantom{┏}┏━┓\\┏┻┳┛\\┣━┫\hphantom{┏}\\┗━┛\hphantom{┏}\end{smallmatrix}\Lambda.
$$

---

The final equation can be solved for $U$:

$$
\begin{array}{rcl}
U & = &\frac{\begin{smallmatrix}┃\\┃\\┃\end{smallmatrix}}{\begin{smallmatrix}┃\\┃\\┃\end{smallmatrix} - \begin{smallmatrix}┏┓\hphantom{┏}\\┃┃\hphantom{┏}\\┣┻┓\\┗━┛\end{smallmatrix}\left(\begin{smallmatrix}┃\\┃\\┃\end{smallmatrix} - \begin{smallmatrix}┏━┓\hphantom{┏}\\┣━┫\hphantom{┏}\\┗┳┻┓\\\hphantom{┏}┗━┛\end{smallmatrix} \right)^{-1} \begin{smallmatrix}┏┓\\┃┃\\┗┛\\\hphantom{┏}\hphantom{┏}\end{smallmatrix} - \begin{smallmatrix}┏━┓\\┣┳┛\\┃┃\hphantom{┏}\\┗┛\hphantom{┏}\end{smallmatrix} \left(\begin{smallmatrix}┃\\┃\\┃\end{smallmatrix} - \begin{smallmatrix}\hphantom{┏}┏━┓\\┏┻┳┛\\┣━┫\hphantom{┏}\\┗━┛\hphantom{┏}\end{smallmatrix} \right)^{-1} \begin{smallmatrix}\hphantom{┏}\hphantom{┏}\\┏┓\\┃┃\\┗┛\end{smallmatrix} - \begin{smallmatrix}┏━┓\\┣━┫\\┣━┫\\┗━┛\end{smallmatrix}}\\
 & = & \frac{\begin{smallmatrix}┃\\┃\end{smallmatrix} - \begin{smallmatrix}\hphantom{┏}\hphantom{┏}\hphantom{┏}\\┏━┓\\┗━┛\end{smallmatrix}^3}{\left( \begin{smallmatrix}┃\\┃\end{smallmatrix} - \begin{smallmatrix}\hphantom{┏}\hphantom{┏}\hphantom{┏}\\┏━┓\\┗━┛\end{smallmatrix}^3 \right)^2 - 2 \begin{smallmatrix}┏┓\\┃┃\\┗┛\end{smallmatrix}^2 \begin{smallmatrix}\hphantom{┏}\hphantom{┏}\hphantom{┏}\\┏━┓\\┗━┛\end{smallmatrix}}\\
 & = & \frac{1 - z^3}{1 - 4z^3 + z^6}.
\end{array}
$$

The total number of $3 \times n$ tilings is

$$
U_n = \sum_m \begin{pmatrix}n-m\\m\end{pmatrix} 2^{\frac{n}{2} - m}.
$$

---

Q3 - How many ways are there to pay 50 cents?

Let $P$, $N$, $D$, $Q$, and $C$ be the generating functions of the numbers of ways to pay n cents when we're allowed to use coins that are worth at most 1, 5, 10, 25, and 50 cent, we have

$$
P = \emptyset + \textcircled{\scriptsize 1} + \textcircled{\scriptsize 1}^2 + \cdots,
$$

$$
N = (\emptyset + \textcircled{\scriptsize 5} + \textcircled{\scriptsize 5}^2 + \cdots)P,
$$

$$
D = (\emptyset + \textcircled{\scriptsize 10} + \textcircled{\scriptsize 10}^2 + \cdots)N,
$$

$$
Q = (\emptyset + \textcircled{\scriptsize 25} + \textcircled{\scriptsize 25}^2 + \cdots)D,
$$

$$
C = (\emptyset + \textcircled{\scriptsize 50} + \textcircled{\scriptsize 50}^2 + \cdots)Q.
$$

---

Multiplying the equations together gives us the compact expression

$$
C = \frac{1}{1-z}\frac{1}{1-z^5}\frac{1}{1-z^{10}}\frac{1}{1-z^{25}}\frac{1}{1-z^{50}}.
$$

The corresponding generating function is an inffinite product of fractions,

$$
P = \frac{1}{1-z}\frac{1}{1-z^2}\frac{1}{1-z^{3}}\cdots,
$$

and the coefficient of $z^n$ when these factors are fully multiplied out is called $p(n)$, the number of partitions of $n$.

---

### 7.2 Basic Maneuvers

---

$G(z) = g_0 + g_1 z^ + \cdots = \sum_{n \ge 0}g_n z^n$ is the generating function for the sequence $\langle g_0, g_1, g_2, \ldots \rangle$.

The coefficient of $z^n$ was then the number of combinatorial objects having $n$ occurrences of that feature.

---

Generating functions for simple sequences.

![bg right:66% fit](Concrete_Mathematics/Table_generating_functions_for_simple_sequences.png)

---

Reshaping generating functions.

$$
\alpha F(z) + \beta G(z) = \sum_n (\alpha f_n + \beta g_n) z^n;
$$

$$
z^m G(z) = \sum_n (g_{n-m}) z^n, \quad \text{integer} \; m > 0;
$$

$$
G(cz) = \sum_n c^n g_{n} z^n;
$$

$$
G'(z) = \sum_n (n+1) g_{n+1} z^n;
$$

$$
\int_0^z G(t) dt = \sum_{n \ge 1} \frac{1}{n} g_{n-1} z^n;
$$

$$
F(z)G(z) = \sum_{n} \left( \sum_{k} f_k g_{n-k} \right) z^n;
$$

---

### 7.3 Solving Recurrences

---

Given a sequence $\langle g_{n_i} \rangle$ that satisffies a given recurrence, we seek a closed form for $g_n$ in terms of $n$. A solution  via generating functions proceeds in four steps:

* Step 1. Write down a single equation that expresses $g_n$ in terms of other elements of the sequence.
* Step 2. Multiply both sides of the equation by $z^n$ and sum over all $n$.
* Step 3. Solve the resulting equation, getting a closed form for $G(z)$.
* Step 4. Expand G(z) into a power series and read off the coefficient of $z^n$.

---

Rational Expansion Theorem for Distinct Roots.

If $R(z) = P(z) / Q(z)$, where $Q(z) = q_0(1 - \rho_1 z) \cdots (1 - \rho_l z)$ and the numbers $(\rho_1, \ldots, \rho_l)$ are distinct, and if $P(z)$ is a polynomial of degree less than $l$, then

$$
[z^n] R(z) = a_1 \rho_1^n + \cdots + a_l \rho_l^n,
$$
where

$$
a_k = \frac{-\rho_k P(1/\rho_k)}{Q'(1/\rho_k)}.
$$

---

Example 1: Fibonacci numbers.

* Step 1. $g_0 = g_{n-1} + g_{n-2} + [n=1] = \begin{cases}0 & n \le 0\\1 & n = 1\\g_{n-1} + g_{n-2} & n \ge 2\end{cases}$.
* Step 2. $G(z) = \sum_n g_n z^n = \sum_n g_{n-1} z^n + \sum_n g_{n-2} z^n + \sum_n [n=1] z^n = z G(z) + z^2 G(z) + z$.
* Step 3. $G(z) = \frac{z}{1 - z - z^2}$.
* Step 4. According to Rational Expansion Theore for Distinct Roots, $a(\rho)=\frac{-\rho P(1/\rho)}{Q'(1/\rho)} = \frac{\rho}{\rho + 2}$, $a(\phi) = 1 / \sqrt{5}$, $a(\hat{\phi}) = -1 / \sqrt{5}$, so that $F_n = (\phi^n - \hat{\phi}^n) / \sqrt{5}$.

---

General Expansion Theorem for Rational Generating Functions.

If $R(z) = P(z) / Q(z)$, where $Q(z) = q_0(1 - \rho_1 z)^{d_1} \cdots (1 - \rho_l z)^{d_l}$ and the numbers $(\rho_1, \ldots, \rho_l)$ are distinct, and if $P(z)$ is a polynomial of degree less than $d_1 + \cdots + d_l$, then

$$
[z^n] R(z) = f_1(n) \rho_1^n + \cdots + f_l(n) \rho_l^n, \quad \text{where},
$$

where each $f_k(n)$ is a polynomial of degree $d_k - 1$ with leading coefficient

$$
a_k = \frac{(-\rho_k)^{d_k} P(1/\rho_k) d_k}{Q^{(d_k)}(1/\rho_k)}.
$$

---

Example 2: A more-or-less random recurrence.

* Step 1. $g_0 = g_{n-1} + 2g_{n-2} + (-1)^n[n\ge 0]$.
* Step 2. $G(z) = \sum_n g_n z^n = \sum_n g_{n-1} z^n + 2 \sum_n g_{n-2} z^n + \sum_{n\ge 0} (-1)^n z^n + \sum_{n=1} z^n = z G(z) + 2z^2 G(z) + \frac{1}{1+z} + z$.
* Step 3. $G(z) = \frac{1+z+z^2}{(1 - 2z)(1+z)^2}$.
* Step 4. According to General Expansion Theorem for Rational Generating Functions, $\rho_1 = 2$, $\rho_2 = -1$, $g_n = a_1 2^n + (a_2 n + c)(-1)^n$, where $a_1=\frac{(-2)\left(1+1/2+(1/2)^2\right)}{(-2)(1+1/2)^2}=\frac{7}{9}$, $a_2=\frac{(1)^2\left(1+(-1)+(-1)^2\right)(2)}{(2)\left(1-2(-1)\right)}=\frac{1}{3}$. Plugging in $n = 0$ tells us that $c=\frac{2}{9}$, so that $g_n = \frac{7}{9} 2^n + \left(\frac{1}{3} n + \frac{2}{9}\right)(-1)^n$.

---

Example 3: Mutually recursive sequences - the problem of $3 \times n$ domino tilings.

$U_n$ is the total number of ways of $3 \times n$ domino tilings, $V_n$ is the number of ways to cover a $3 \times n$ rectangle-minus-corner, using $(3n - 1)/2$ dominoes.

* Step 1. $U_n = 2V_{n-1} + U_{n-2} + [n=0]$, $V_n = U_{n-1} + V_{n-2}$.
* Step 2. $U(z) = 2zV(z) + z^2U(z) + 1$, $V(z) = zU(z) + z^2 V(z)$.
* Step 3. $U(z) = \frac{1-z^2}{1 - 4z^2 + z^4}$, $V(z) = \frac{z}{1 - 4z^2 + z^4}$.
* Step 4. Consider the generating function $W(z)=\frac{1}{1-4z+z^2}$, we have $V(z) = zW(z^2)$ and $U(z) = (1 - z^2)W(z^2)$, hence $V_{2n+1} = W_n$ and $U_{2n} = W_n - W_{n-1}$. Thus we have

$$
V_{2n+1} = W_n = \frac{3+2\sqrt{3}}{6}(2+\sqrt{3})^n + \frac{3-2\sqrt{3}}{6}(2-\sqrt{3})^n;\\
U_{2n} = W_n - W_{n-1} = \frac{(2+\sqrt{3})^n}{3-\sqrt{3}} + \frac{(2-\sqrt{3})^n}{3+\sqrt{3}}=\left\lceil \frac{(2+\sqrt{3})^n}{3-\sqrt{3}} \right\rceil.
$$

---

Example 4: A closed form for change.

* Step 3. $C(z)=\frac{1}{1-z}\frac{1}{1-z^5}\frac{1}{1-z^{10}}\frac{1}{1-z^{25}}\frac{1}{1-z^{50}} = (1 + z + z^2 + z^3 + z^4) \check{C}(z^5)$, where $\check{C}(z)=\frac{1}{1-z}\frac{1}{1-z}\frac{1}{1-z^2}\frac{1}{1-z^{5}}\frac{1}{1-z^{10}}=\frac{A(z)}{(1-z^{10})^5}$, $A(z)=(1 + z + \cdots + z^9)^2(1 + z^2 + \cdots + z^8)(1 + z^5)$.
* Step 4. When $n = 10q + r$ and $0 \le r < 10$,

$$
\begin{array}{rcl}
\check{C}_{10q+r} &=& \sum_{j,k}A_j \begin{pmatrix}k+4\\4\end{pmatrix}[10q+r=10k+j]\\
&=& A_r \begin{pmatrix}q+4\\4\end{pmatrix} + A_{r+10} \begin{pmatrix}q+3\\4\end{pmatrix} + A_{r+20} \begin{pmatrix}q+2\\4\end{pmatrix} + A_{r+30} \begin{pmatrix}q+1\\4\end{pmatrix}.
\end{array}
$$

---

Example 5: A divergent series.

* Step 1. $g_n = ng_{n-1} + [n=0]$.
* Step 2. $G(z) = \sum_{n}n g_{n-1}z^n + \sum_{n=0}z^n = 1 + \sum_{n} (n+1)g_n z^{n+1} = 1 + z^2G'(z) + zG(z)$.
* Step 3. Taking the derivative of both sides, we have $G' = z^2G'' + 3zG' + G$, and rewrite this using the $\vartheta$ operator, where $\vartheta G = zG'$, $\vartheta^2 G = z^2 G'' + zG'$. Therefore $\vartheta G = z(\vartheta + 1)^2G$. According to Hypergeometric Transformations in Chapter 5, the solution with $g_0 = 1$ is the hypergeometric series $F\left(\begin{matrix}1,1\\\;\end{matrix}\middle|z\right)$.
* Step 4. $G(z) = F\left(\begin{matrix}1,1\\\;\end{matrix}\middle|z\right) = \sum_{n \ge 0} \frac{1^{\overline{n}}1^{\overline{n}}z^n}{n!} = \sum_{n \ge 0} n!z^n$.

---

Example 6: A recurrence that goes all the way back. How many spanning trees $f_n$ are in such a graph (a fan of order $n$)?

* Step 1. Consider (i) how the topmost vertex (vertex $n$) is connected to the rest of the spanning tree, and (ii) some number $k \le n$ such that vertices $n, n - 1, \ldots, k$ are connected directly but the edge between $k$ and $k - 1$ is not present. We have $f_n = f_{n-1} + \left( f_{n-1} + f_{n-2} + \cdots + f_1 + 1 \right) = f_{n-1} + \sum_{k<n} f_k + [n>0]$.
* Step 2. $F(z) = \sum_n f_n z^n = zF(z) + \sum_k f_kz^k \sum_n [n>k]z^{n-k} + \frac{z}{1 - z} = zF(z) + F(z)\frac{z}{1 - z} + \frac{z}{1 - z}$.
* Step 3. $F(z) = \frac{z}{1-3z+z^2}$.
* Step 4. $f_n = F_{2n}$, for $n \ge 0$.

---

### 7.4 Special Generating Functions

---

Generating functions for special numbers.

![bg right:66% fit](Concrete_Mathematics/Table_generating_functions_for_special_numbers.png)

---

### 7.5 Convolutions

---

Example 1: A Fibonacci convolution.

The sum $\sum_{k=0}^n F_n F_{n-k}$ is the coefficient of $z^n$ in $F(z)^2$, because it is the convolution of $\langle F_n \rangle$ with itself.

$$
\begin{array}{rcl}
F(z)^2 &=& \frac{1}{5} \sum_{n \ge 0} (n+1) \left(\phi^2 + \hat{\phi}^2\right) z^n - \frac{2}{5} \sum_{n \ge 0} F_{n+1} z^n\\
&=& \frac{1}{5} \sum_{n \ge 0} \left( 2nF_{n+1} - (n+1)F_n \right) z^n.
\end{array}
$$

We have

$$
\sum_{k=0}^n F_n F_{n-k} = \frac{1}{5} \left( 2nF_{n+1} - (n+1)F_n \right).
$$

---

Example 2: Harmonic convolutions.

The efficiency of samplesort (a generalization of quicksort) depends on the value of the sum $T_{m,n} = \sum_{0 \le k < n} \begin{pmatrix}k\\m\end{pmatrix} \frac{1}{n-k}$, which is the $n$th term in the convolution of $\left\langle \left(\begin{smallmatrix}i\\m\end{smallmatrix}\right) \right\rangle$ with $\left\langle \frac{i}{m} \right\rangle$, where $\sum_{n \ge 0} \begin{pmatrix}n\\m\end{pmatrix}z^n = \frac{z^m}{(1-z)^{m+1}}$ and $\sum_{n > 0}\frac{1}{n}z^n = \ln \frac{1}{1-z}$. Therefore,

$$
T_{m,n} = [z^n] \frac{z^m}{(1-z)^{m+1}} \ln \frac{1} {1-z} = (H_n - H_m) \begin{pmatrix}n\\n-m\end{pmatrix}.
$$

Because $\frac{1}{(1-z)^{r+1}} \ln \frac{1} {1-z} \cdot \frac{1}{(1-z)^{s+1}} = \frac{1}{(1-z)^{r+s+2}} \ln \frac{1} {1-z}$, we have

$$
\sum_k \begin{pmatrix}r+k\\k\end{pmatrix} \begin{pmatrix}s+n-k\\n-k\end{pmatrix} (H_{r+k} - H_r) = \begin{pmatrix}r+s+n+1\\n\end{pmatrix} (H_{r+s+n+1} - H_{r+s+1}).
$$

---

Example 3: Convolutions of convolutions.

The spans-of-fans problem. All possible ways to make certain blocks of adjacent vertices gives us the total number of spanning trees:

$$
f_n = \sum_{m>0} \sum_{\begin{smallmatrix}k_1 + \cdots + k_m = n\\k_1, \ldots, k_m>0\end{smallmatrix}} k_1 k_2 \cdots k_m,
$$

which is the sum of $m$-fold convolutions of the sequence $\langle 0, 1, 2, \ldots \rangle$ with the generating function $G(z)=\frac{z}{(1-z)^2}$. We have

$$
F(z) = G(z) + G(z)^2 + \cdots = \frac{G(z)}{1-G(z)} = \frac{z}{1-3z+z^2}.
$$

---

Example 4: A convoluted recurrence.

How many ways $C_n$ are there to insert parentheses into the product $x_0 \cdot x_1 \cdot \cdots \cdot x_n$ so that the order of multiplication is completely specified?

How many sequences $\langle a_0, a_1, a_2, \ldots, a_{2n}\rangle$ of $+1$'s and $-1$'s have the property that $a_0 + a_1 + \cdots + a_{2n} = 1$ and all the partial sums are positive?

* Step 1. $C_n = \sum_k C_k C_{n-1-k} + [n=0]$.
* Step 2. $C(z) = C(z) \cdot z C(z) + 1$.
* Step 3. $C(z) = \frac{1 \plusmn \sqrt{1-4z}}{2z}$, where the $+$ sign gives $C(0) = \infty$.
* Step 4. $[z^n]C(z) = [z^n]\sum_{n \ge 0} \begin{pmatrix}2n\\n\end{pmatrix}\frac{z^n}{n+1} = \begin{pmatrix}2n\\n\end{pmatrix}\frac{1}{n+1}$.

---

Example 5: A recurrence with m-fold convolution.

$m$-Raney sequences - How many sequences $\langle a_0, a_1, a_2, \ldots, a_{2n}\rangle$ of $+1$'s and $(1 - m)$'s whose partial sums are all positive and whose total sum is $+1$?

* Raney's lemma tells us that the answer is $\begin{pmatrix}mn+1\\n\end{pmatrix}\frac{1}{mn+1}$.
* We call this a Fuss-Catalan number $C^{(m)}_n$, and its generating function $G(z)$ satisfies $G(z) = z G(z)^m + 1$.
* Lambert's equation says that  $[z^n]\mathscr{B}_t(z)^r=\begin{pmatrix}tn+r\\n\end{pmatrix}\frac{r}{tn+r}$.

---

### 7.6 Exponential Generating Functions

---

Exponential generating functions have their own basic maneuvers.

* If we multiply the egf of $\langle g_n \rangle$ by $z$, we get the egf of $\langle 0, g_0, 2g_1, \ldots \rangle = \langle ng_{n-1} \rangle$.
* Differentiation on egf's corresponds to the left-shift operation $(G(z) - g_0) / z$ on ordinary gf's; Integration of an egf gives a right shift, the egf of $\langle 0, g_0, g_1, \ldots \rangle$.
* Multiplication, the binomial convolution of $\langle f_n \rangle$ and $\langle g_n \rangle$ is $\langle h_n \rangle$, where $h_n = \sum_k \begin{pmatrix}n\\k\end{pmatrix}f_k g_{n-k}$.

---

The egf for Bernoulli numbers

$$
\hat{B}(z) = \sum_{n \ge 0} B_n \frac{z^n}{n!} = \frac{z}{e^z - 1}.
$$

The egf for the sequence $\langle S_0(n); S_1(n); S_2(n), \ldots \rangle$ where $S_m(n) = \sum_{0 \le k < n}k^m$ is

$$
\hat{S}(z, n) = \sum_{m \ge 0}S_m(n)\frac{z^m}{m!} = \sum_{0 \le k < n} e^{kz} = \frac{e^{nz}-1}{e^z-1}.
$$

The general formula can be written as

$$
S_{m-1}(n) = \frac{1}{m}(B_m(n) - B_m(0)),
$$

where $B_m(x) = \sum_k \begin{pmatrix}m\\k\end{pmatrix}B_k x^{m-k}$ is the Bernoulli polynomial.

---

How many spanning trees are possible in the complete graph on $n$ vertices $\langle 1, 2, \ldots, n \rangle$?

$$
t_n = \sum_{m > 0} \frac{1}{m!} \sum_{k_1 + \cdots + k_m = n - 1} \begin{pmatrix}n-1\\k_1,k_2,\ldots,k_m\end{pmatrix} k_1 k_2\cdots k_m t_{k_1} t_{k_2} \cdots t_{k_m}.
$$

* There are $\begin{pmatrix}n-1\\k_1,k_2,\ldots,k_m\end{pmatrix}$ ways to assign $n-1$ elements to a sequence of m components of respective sizes $k_1, k_2, \ldots, k_m$.
* There are $t_{k_1} t_{k_2} \cdots t_{k_m}$ ways to connect up those individual components with spanning trees.
* There are $k_1 k_2\cdots k_m$ ways to connect vertex $n$ to those components.

---

Let $u_n = n t_n$, we have

$$
\frac{u_n}{n!} = \sum_{m > 0} \frac{1}{m!} \sum_{k_1 + \cdots + k_m = n - 1} \frac{u_{k_1}}{k_1!} \frac{u_{k_2}}{k_2!} \cdots \frac{u_{k_m}}{k_m!}.
$$

We have the equation

$$
\hat{U}(z) = z e^{\hat{U}(z)},
$$

and

$$
t_n = \frac{u_n}{n} = \frac{n!}{n}[z^n]\hat{U}(z) = n^{n-2}.
$$

---

### 7.7 Dirichlet Generating Functions

---

Any system of "kernel" functions $K_n(z)$ such that
$$
\sum_n g_n K_n(z) = 0 \Longrightarrow g_n = 0 \; \text{for all} \; n
$$

can be used to generate a sequence from a series.

* Ordinary generating functions use $K_n(z) = z^n$.
* Exponential generating functions use $K_n(z) = z^n / n!$.
* Dirichlet generating function (dgf) uses the kernel functions $K_n(z) = 1 / n^z$.

---

The product of Dirichlet generating functions corresponds to a special
kind of convolution

$$
\tilde{F}(z)\tilde{G}(z) = \sum_{n \ge 1} \frac{1}{n^z} \sum_{l, m \ge 1} f_l g_m [l \cdot m = n].
$$

* The dgf of $\langle 1, 1, \ldots \rangle$ is Riemann's zeta function $\zeta(z) = \sum_{n \ge 1} \frac{1}{n^z}$.
* The dgf of $\langle \mu(1), \mu(2), \ldots \rangle$ is $\zeta(z)^{-1}$.

---

Dirichlet generating functions are particularly valuable when the sequence $\langle g_1, g_2, \cdots \rangle$ is a multiplicative function.

* $\zeta(z) = \prod_{p \; \text{prime}}\frac{1}{1-p^{-z}}=$.
* $\tilde{M}(z) = \prod_{p \; \text{prime}}\left( 1-p^{-z} \right)$.
* $\tilde{\Phi}(z) = \prod_{p \; \text{prime}}\frac{1-p^{-z}}{1-p^{1-z}}$.

---

## 8 Discrete Probability

---

### 8.1 Definitions

---

A probability space is a set $\Omega$ ­of all things that can happen in a given problem together­.

* $Pr$ distributes a total probability of $1$ among the events $\omega \in \Omega$, and the condition $\sum_{\omega \in \Omega} Pr(\omega) = 1$ must hold.
* An event is a subset of ­$\Omega$. The probability of an event $A$ is defined by the formula $Pr(\omega \in A) = \sum_{\omega \in A} Pr(\omega)$.
* $X$ and $Y$ are independent random variables if $Pr(X=x \; \text{and} \; Y =y) = Pr(X=x) \cdot Pr(Y =y)$.

---

The expected value is the mean of a random variable

$$
EX = \sum_{\omega \in \Omega} X(\omega) Pr(\omega).
$$

* $E(X+Y) = EX + EY$;
* $E(\alpha X) = \alpha EX$;
* $E(XY) = (EX)(EY)$, if $X$ and $Y$ are independent.
  
---

### 8.2 Mean and Variance

---

The variance of a random variable is defined as the mean square deviation from the mean:

$$
VX = E\left((X - EX)^2\right) = E(X^2) - (EX)^2.
$$

* $V(X+Y) = VX + VY$;
* Chebyshev's inequality: $Pr((X-EX)^2 \ge \alpha) \le VX / \alpha$.

---

### 8.3 Probability Generating Functions

---

The probability generating function or pgf of $X$ is

$$
G_X(z) = \sum_{k \ge 0} Pr(X=k) z^k.
$$

* $EX = G'_X(1)$.
* $VX = G''_X(1) + G'_X(1) - G'_X(1)^2$.
* $G_{X+Y}(z) = G_X(z) G_Y(z)$, if $X$ and $Y$ are independent.

Three nicest things about pgf's.

* Simplify the computation of means and variances.
* They are comparatively simple functions of $z$, in many important cases.
* The product of pgf's corresponds to the sum of independent random variables.

---

There also are higher-order cumulants

$$
\ln G(e^t) = \frac{\kappa_1}{1!}t + \frac{\kappa_2}{2!}t + \cdots.
$$

$$
G(e^t) = \sum_{k,m} Pr(X=k)\frac{k^m t^m}{m!} = \sum_{k} \frac{\mu_k}{k!} t^k.
$$

$\kappa_1$ and $\kappa_2$ of a random variable are the mean and the variance. All cumulants of the sum of independent random variables are additive, which makes cumulants $\kappa$ more important than moments $\mu$.

* In the hats-off-to-football-victory problem, the mth cumulant $\kappa_m$ of this random variable is equal to $1$, hence we have $F_\infty(z) = e^z - 1$.

---

### 8.4 Flipping Coins

---

The pgf for the number of heads is

$$
H(z)^n = (q + pz)^n = \sum_{k \ge 0} \begin{pmatrix}n\\k\end{pmatrix}p^k q^{n-k} z^k.
$$

Let $X$ be a random variable with the binomial distribution. The mean of $X$ is $nH'(1) = np$, the variance is $n \left(H''(1) + H'(1) - H'(1)^2 \right) = npq$.

---

The pgf for the number of tosses when heads first turns up is

$$
\left( \frac{pz}{1-qz} \right)^n = p^n z^n \sum_{k} \begin{pmatrix}n + k - 1\\k\end{pmatrix} (qz)^k.
$$

let $Y$ be a random variable with the negative binomial distribution. The mean of $Y$ is $nq/p$ and the variance is $nq/p^2$.

---

How many times do we have to flip a coin until we get heads twice in a row?

* Lett $S$ be the infinite sum of all sequences of $H$'s and $T$'s that end with HH but have no consecutive $H$'s until the final position.
* There's a curious relation between $S$ and the sum of domino tilings.

$$
S = \left(1 - (T + HT) \right)^{-1} HH.
$$

* The probability generating function is

$$
G(z) = \left( 1 - (qz + pz \cdot qz)\right)^{-1} (pz)^2 = \frac{p^2 z^2}{1 - qz - pqz^2}.
$$

* The mean and variance of distribution $G(z)$ are $p^{-2} + p^{-1}$ and $p^{-4} + 2p^{-3} - 2p^{-2} - p^{-1}$. We can get them by calculating the mean and variance of this pseudo-pgf $F(z) = z^2 / G(z)$.

---

How many times do we have to flip a coin until the pattern THTTH is first obtained?

* We can obtain a formula for $S$ by considering it as a finite state language defined by an automation. Systems of this kind are called Markov processes, and the theory of their behavior is intimately related to the theory of linear equations.
* We can characterize S with only two equations in two unknowns. The trick is to consider the auxiliary sum of all flip sequences that don't contain any occurrences of the given pattern.
* The pgf is $G(z) = \frac{p^2 q^3 z^5}{p^2 q^3 z^5 + (1 + p q^2 z^3)(1-z)}$.
* The mean and variance are $EX = p^{-2} q^{-3} + p^{-1} q^{-1}$ and $VX = (EX)^2 - 9 p^{-2} q^{-3} - 3 p^{-1} q^{-1}$.

---

How about we are waiting for the first appearance of an arbitrary pattern $A$ of heads and tails?

* Let $S$ be the sum of all winning sequences of H's and T's, and we let $N$ be the sum of all sequences that haven't encountered the pattern $A$ yet.
* Equation 1: $1 + N(H + T) = N + S$.
* Equation 2: $NA = S(1 + A^{(1)}[A^{(m-1)}=A_{(m-1)}] + \cdots + A^{(m-1)}[A^{(1)}=A_{(1)}])$.

---

The Penney ante game.

* $A:B = \sum_{k=1}^{\min(l, m)} 2^{k-1}[A^{(k)} = B_{(k)}]$.
* The odds in Alice's favor are $\frac{S_A}{S_B} = \frac{B:B - B:A}{A:A - A:B}$.

---

### 8.5 Hashing

---

The general problem is to maintain a set of records that each contain a "key" value, $K$, and some data $D(K)$ about that key; we want to be able to find $D(K)$ quickly when $K$ is given.

---

Use $m$ separate lists instead of one giant list.

* Case 1: The key is not present. The mean and variance are $EP = \frac{n}{m}$ and $VP = n(m-1)/m^2$.
* Case 2: The key is present. The mean and variance are $EP = 1+m^{-1}Mean(S)$ and $VP = m^{-2}Var(S) + (m^{-1}+m^{-2})Mean(S)$.

Case 2, continued: Variants of the variance.

Case 1, again: Unsuccessful search revisited. If $m = n/\ln n$ and $n \rightarrow \infty$, we have

* $Mean(G_T) = \beta \ln n + \alpha + \delta / n + O\left((\log n)^2 / n^2\right)$;
* $Var(G_T)=\beta^2 \ln n - \left((\beta \ln n)^2 + 2 \beta \delta \ln n - \delta^2 \right) / n + O\left((\log n)^3 / n^2\right)$.

---

## 9 Asymptotics

Know the approximations and how to compare it with other closed forms.

---

### 9.1 A Hierarchy

---

Asymptotic growth ratios:

$$
f(n) \prec (n) \Longleftrightarrow \lim_{n \rightarrow \infty} \frac{f(n)}{g(n)} = 0.
$$

An asymptotic pecking order of lots of functions:

$$
1 \prec \log \log n \prec \log n \prec n^{\epsilon} \prec n^{c} \prec n^{\log n}  \prec c^n  \prec n^{n}  \prec c^{c^n}, \quad 0 < \epsilon < 1 < c.
$$

---

Hardy's main theorem about logarithmico-exponential functions.

* If $f(n)$ and $g(n)$ are any functions in $\mathscr{L}$, then either $f(n) \prec g(n)$, or $f(n) \prec g(n)$, or $f(n) \asymp g(n)$.

---

### 9.2 O Notation

introduced by Paul Bachmann in 1894.

---

$O(\alpha)$ stands for a number whose absolute value is at most a constant times $| \alpha |$.

* $O$ represents an undefined function and either one or two unspecified constants, depending on the environment.
* $O$ stands for the set of all functions.

$\Omega$ stands for lower bounds.

$\Theta$ specifies an exact order of growth.

---

### 9.3 O Manipulation

---

$f(n) + O(g(n))$ have absolute error $O(g(n))$

$$
H_n = \ln n + \gamma + \frac{1}{2n} - \frac{1}{12n^2} + \frac{1}{120n^4} + O\left(\frac{1}{n^6}\right).
$$

$f(n)(1 + O(g(n)))$ have relative error $O(g(n))$

$$
n! = \sqrt{2\pi n}\left( \frac{n}{e} \right)^n \left(1 + \frac{1}{12n} + \frac{1}{288n^2} - \frac{139}{51840n^3} + O\left(\frac{1}{n^4}\right) \right).
$$

---

Problem 1: Return to the Wheel of Fortune.

* If $\lfloor \sqrt[3]{n} \rfloor \backslash n$, then it's a winner and the house pays us $5; otherwise it's a loser and we must pay $1. The number of winners is $W = \lfloor N/K \rfloor + \frac{1}{2}K^2 + \frac{5}{2}K - 3$, where $K = \lfloor \sqrt[3]{N} \rfloor$.
* Replacing $K$ by $N^{1/3} + O(1)$, we have

$$
W = \frac{3}{2} N^{2/3} + O(N^{1/3}).
$$

---

Problem 2: Perturbation of Stirling’s formula.

$$
n! = \sqrt{2\pi n}\left( \frac{n}{e} \right)^n \left(1 + \frac{a}{n} + \frac{b}{n^2} + O\left(\frac{1}{n^3}\right) \right).
$$

* Replacing $n$ by $n - 1$, we have $a=\frac{1}{12}$.
* Replacing $O(n^{-3})$ by $cn^{-3}+O(n^{-4})$, we have $b=\frac{1}{288}$.

---

Problem 3: The $n$th prime number.

$$
P_n = n \ln n + n \ln \ln n + O(n);\\
P_n = n \ln n + n \ln \ln n - n + n \frac{\ln \ln n}{\ln n}+ O\left( \frac{n}{\log n} \right).
$$

---

Problem 4: A sum from an old final exam.

$$
S_n = H_{n^2 + n} - H_{n^2} = \frac{1}{n^2+1} + \frac{1}{n^2+2} + \cdots \frac{1}{n^2+n};\\
S_n = n^{-1} - \frac{1}{2}n^{-2} - \frac{1}{6}n^{-3} + \frac{1}{4}n^{-4} - \frac{2}{15}n^{-5} - \frac{1}{12}n^{-6} + O(n^{-7}).
$$

---

Problem 5: An infinite sum.

$$
S_n = \sum_{k \ge 1} \frac{1}{k N_n(k)^2},
$$

where $N_n(k)$ is the number of digits required to write $k$ in radix $n$ notation.

$$
S_n = \sum_{k \ge 1}H_{n^k-1}\left( \frac{1}{k^2} - \frac{1}{(k+1)^2} \right);\\
S_n = \frac{\pi^2}{6}\ln n + \gamma - \frac{3}{8n} + O\left( \frac{1}{n^2} \right).
$$

---

Problem 6: Big Phi.

$$
\Phi(n) = \sum_{k=1}^n \phi(k) = \frac{1}{2} \sum_{k \ge 1} \mu(k) \lfloor n / k \rfloor \lfloor 1 + n / k \rfloor.
$$

$$
\Phi(n) = \frac{3}{\pi^2}n^2 + O(n \log n).
$$

---

### 9.4 Two Asymptotic Tricks

---

Trick 1: Bootstrapping.

* Solve a recurrence asymptotically by starting with a rough estimate and plugging it into the recurrence.

---

$$
g_n = [z^n] \exp \left(\sum_{k \ge 1} \frac{z^k}{k^2} \right).
$$

Differentiating this equation and equating coefficients of $z^{n-1}$ on both sides gives

$$
n g_n = \sum_{0 \le k < n} \frac{g_k}{n-k}.
$$

Starting with $g_n = O(1)$ and plugging it in repeatedly yields

$$
g_n = \frac{e^{\pi^2/6}}{n^2} + O(\log n / n^3).
$$

---

Trick 2: Trading tails.

* Start with a finite sum but get an asymptotic value by considering an infinite sum.
* Step 1. First break the sum into two disjoint ranges, $D_n$ and $T_n$. The summation over $D_n$ should be the "dominant" part. The summation over the other range $T_n$ should be just the "tail" end.
* Step 2. Find an asymptotic estimate $a_k(n) = b_k(n) + O(c_k(n)) that is valid when $k \in D_n$.
* Step 3. Now prove that each of the following three sums is small: $\sum_{k \in T_n}a_k(n)$, $\sum_{k \in T_n}b_k(n)$ and $\sum_{k \in D_n} |c_k(n)|$.

---

---

$$
L_n = \sum_{k \ge 0} \frac{\ln(n + 2^k)}{k}.
$$

We can prove that $\ln(n + 2^k) = \ln n + \frac{2^k}{n} - \frac{2^{2k}}{2n^2} + O(\frac{2^{3k}}{n^3})$ holds for $0 \le k < \lfloor \lg n \rfloor$. Therefore we can apply the three-step method with

$$
\begin{array}{rcl}
a_k(n) & = & \ln (n + 2^k) / k!,\\
b_k(n) & = & (\ln n + 2^k / n - 4^k / 2n^2) / k!,\\
c_k(n) & = & 8^k / n^3 k!,\\
D_n & = & \{0, 1, \ldots, \lfloor \ln n \rfloor - 1 \},\\
T_n & = & \{ \lfloor \ln n \rfloor, \lfloor \ln n \rfloor + 1, \ldots \}.
\end{array}
$$

Finally,

$$
L_n = e \ln n + \frac{e^2}{n} - \frac{e^4}{2n^2} + O\left( \frac{1}{n^3} \right).
$$

---

### 9.5 Euler's Summation Formula

---

$$
\sum_{a \le k < b} f(k) = \int_a^b f(x) dx + \sum_{k=1}^m \frac{B_k}{k!} \left. f^{(k-1)}(x) \right|^b_a + R_m,
$$

where $R_m = (-1)^{m+1} \int_a^b \frac{B_m(\{x\})}{m!} f^{(m)}(x) dx$, $a \le b$, $m \ge 1$.

* The numbers $B_k$ are the Bernoulli numbers.
* The function $B_m(\{x\})$ is the Bernoulli polynomial.
* The notation $\{x\}$ stands for the fractional part $x - \lfloor x \rfloor$.

---

We can prove it by induction or from a high-level reasoning:

$$
\sum = \frac{B_0}{D} + \frac{B_1}{1!} + \frac{B_2}{2!}D + \cdots = \int + \sum_{k \ge 1} \frac{B_k}{k!} D^{k-1}.
$$

$B_m(x)$ can in fact be well approximated by a negative multiple of $cos(2 \pi x - \frac{1}{2} \pi m)$, with relative error $1/2^m$.

---

$$
\sum_{a \le k < b} k^{m-1} = \frac{1}{m} \sum_{k=0}^m \begin{pmatrix}m\\k\end{pmatrix} B_k \cdot (b^{m-k} - a^{m-k}).
$$

$$
\sum_{0 \le k < n} k^{2} = \frac{n^3}{3} - \frac{n^2}{2} + \frac{n}{6}.
$$

---

### 9.6 Final Summations

---

Summation 0: This one is too easy.

$$
S_n = \sum_{1 \le k < n} \frac{1}{k(k+1)}.
$$

$$
\begin{array}{rcl}
S_n & = & \ln \frac{2n}{n+1} - \sum_{k=1}^m (-1)^k \frac{B_k}{k} \left( \frac{1}{n^k} - \frac{1}{(n+1)^k} - 1 + \frac{1}{2^k} \right) + R_m(n)\\
 & = & C - n^{-1} + O(n^{-m-1}).
\end{array}
$$

---

Summation 1: Recapitulation and generalization.

$$
S_n = \sum_{1 \le k < n} f(k).
$$

$$
S_n = F(n) - F(1) + \sum_{k=1}^m (T_k(n) - T_k(1)) + R_m(n),
$$

where $F(x)$ was $\int f(x) dx$ and where $T_k(x)$ was a certain term involving $B_k$ and $f^{(k-1)}(x)$.

$$
S_n = F(n) + C + \sum_{k=1}^m T_k(n) - R'_m(n),
$$

where $R'_m(n) = O(n^{c+1-m})$.

---

Summation 2: Harmonic numbers harmonized.

$$
\sum_{1 \le k < n} \frac{1}{k} = \ln n + C + B_1 n^{-1} - \sum_{k=1}^m \frac{B_{2k}}{2kn^{2k}} - R'_{2m}(n).
$$

$$
H_n = \ln n + \gamma + \frac{1}{2n} - \sum_{k=1}^m \frac{B_{2k}}{2kn^{2k}} + \theta_{m,n}\frac{B_{2m+2}}{(2m+2)n^{2m+2}},
$$

where $\theta_{m,n}$ is some fraction between 0 and 1.

---

Summation 3: Stirling’s approximation.

$$
\sum_{1 \le k < n} \ln k = n \ln n - n + \sigma - \frac{\ln n}{2} + \sum_{k=1}^m \frac{B_{2k}}{2k(2k-1)n^{2k-1}} + \phi_{m,n} \frac{B_{2m+1}}{(2m+2)(2m+1)n^{2m+1}},
$$

where $\sigma$ is a certain constant, "Stirling's constant," and $0 < \phi_{m,n} < 1$. If $n$ is fixed and $m$ increases, the error bound decreases to a certain point and then begins to increase.

$$
\ln \alpha! = \alpha \ln \alpha - \alpha + \sigma - \frac{\ln n}{2} + \sum_{k=1}^m \frac{B_{2k}}{2k(2k-1)\alpha^{2k-1}} - \int_0^{\infty} \frac{B_{2m}(\{ x \})}{2m} \frac{dx}{(x + \alpha)^{2m}}.
$$

---

Summation 4: A bell-shaped summand.

$$
\Theta_n = \sum_k e^{-k^2 / n}.
$$

$$
\Theta_n = C \sqrt{n} + O(n^{(1-m)/2}) = \sqrt{\pi n} + O(n^{-M}).
$$

---

Summation 5: The clincher.

$$
A_n = \sum_k \begin{pmatrix}2n\\k\end{pmatrix}.
$$

$$
2^{2n} = \sum_k \begin{pmatrix}2n\\k\end{pmatrix} = \frac{\sqrt{2 \pi}}{e^{\sigma}}2^{2n} + O(2^{2n}n^{-\frac{1}{2}+3\epsilon}), \quad \text{if} \; 0 < \epsilon < \frac{1}{6}.
$$
