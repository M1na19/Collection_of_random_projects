## C++ Implementation of Taylor Series and CORDIC Algorithms (arctan, sin, cos, tan)

This repository contains a C++ program that implements two methods for calculating trigonometric functions (sine, cosine, tangent, and arctangent):

* **Taylor Series Expansion:** This method calculates the trigonometric functions by expanding them as Taylor series polynomials.
* **CORDIC Algorithm:** This is a more efficient iterative algorithm for trigonometric calculations.

**Features:**

* Calculates sine, cosine, tangent, and arctangent using both methods.
* Estimates the error between the standard library functions (e.g., `sin`, `cos`) and the implemented algorithms.

**Classes:**

* **TaylorExpansion:** Provides static methods for calculating arctangent, sine, cosine, and tangent using Taylor series expansion.
* **CORDIC:** Provides static methods for calculating sine and cosine using the CORDIC algorithm. This algorithm utilizes a constant value (`CORDIC_CONSTANT`) for efficient calculations.

**Error Function:**

* The `Error` function generates a random angle and calculates the absolute error between the standard library functions and the implemented algorithms for sine and cosine.

**Main Function:**

* The `main` function sets the random number seed, configures output precision (currently set to 10), and calls the `Error` function to estimate errors.

**How to Use:**

1. Clone the repository.
2. Compile the code using a C++ compiler (e.g., `g++ taylor_cordic.cpp -o taylor_cordic`).
3. Run the executable (`./taylor_cordic`).

**Output:**

The program will print the absolute errors between the standard library functions and the implemented algorithms for sine and cosine for a randomly generated angle.

**Notes:**

* The `precision` variable in the code controls the accuracy of the Taylor series expansion. Higher precision leads to smaller errors but also increases computation time.
* This is a basic implementation