**Title:** Exponential Approximation of e

**Description:**

This code implements two methods for approximating the mathematical constant e:

1. **Limit Expansion:** This method uses the limit definition of e, which is the limit of (1 + 1/n)^n as n approaches infinity.
2. **Factorial Expansion:** This method uses the factorial series definition of e, which is the sum of 1/n! for all non-negative integers n.

The code also compares the approximations with the value returned by the standard library function `exp(1)`.

**Includes:**

```c++
#include <iostream>
#include <cmath>
#include <iomanip>
#include <climits>
```

**Functions:**

* `limit_expansion()`: This function approximates e using the limit definition. It calculates (1 + 1/n)^n where n is set to a large value (2^52 in this case).

* `factorial_expansion(precision)`: This function approximates e using the factorial series definition. It takes an optional precision argument (default 20) which specifies the number of terms to use in the summation. The function calculates the sum of 1/n! for n from 1 to precision.

* `main()`: This function is the entry point of the program. It calls the `factorial_expansion` and `limit_expansion` functions to calculate the approximations of e. It then prints the approximations along with the value from the standard library function `exp(1)`.

**Compiling and Running:**

This code can be compiled and run using a C++ compiler. Here's an example using g++:

```bash
g++ main.cpp -o exp_approx
./exp_approx
```

This will print the following output:

```
Factorial expansion:2.71828182845904553488480814849027
Limit expansion: 2.71828182845904509079559829842765
Standard Library: 2.71828182845904509079559829842765
```

**Note:**

The accuracy of the approximations will increase with higher precision in the `factorial_expansion` function. However, calculating the factorial can become computationally expensive for very high precision values.

Due to the fact that `exp(1)` is equal with `limit_expansion` we can assume the implementations are similar
