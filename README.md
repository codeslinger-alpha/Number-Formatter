# Description of the C Program

### Overview
This program contains two primary functions:

1. `getfrac`: A function to approximate a floating-point number as a rational number (fraction) within a given maximum denominator.
2. `format`: A utility function to format a number, representing it as either a decimal number, a fraction, a square root, or a multiple of π (pi) depending on the input and tolerance.

### `getfrac` Function

**Purpose:**  
The `getfrac` function takes a floating-point number `n` and attempts to approximate it as a fraction `numerator/denominator`, with the denominator constrained by the maximum value `maxden`.

**Parameters:**
- `n` (double): The number to approximate.
- `maxden` (long long): The maximum allowed denominator for the fraction.
- `numerator` (long long*): Pointer to store the computed numerator.
- `denominator` (long long*): Pointer to store the computed denominator.

**Core Logic:**  
1. Initializes a 2x2 matrix `m` used for storing intermediary results in the approximation process.
2. The algorithm runs in a loop, finding terms for numerator and denominator until the denominator exceeds the `maxden` constraint.
3. Two potential approximations are computed:
   - `err1` for the fraction from the initial matrix.
   - `err2` for a second fraction obtained by adjusting the initial matrix.
4. The function returns the error (difference between the original number and the approximation), and the better of the two approximations is used.

**Usage:**  
This function is used to convert a floating-point number into a rational approximation when exact representation is not possible.

---

### `format` Function

**Purpose:**  
The `format` function attempts to represent a given number in a readable format, such as a fraction, square root, or multiple of π. It can handle cases where the input number is close to a whole number or fits a specific format within the tolerance provided.

**Parameters:**
- `N` (double): The number to be formatted.
- `TOL` (double): The tolerance used to determine if two values are considered equal.
- `res` (char*): A string buffer to store the result of the formatted number.

**Core Logic:**  
1. Handles special cases like `NaN` (not a number) and numbers that are extremely large or small.
2. If the number is an integer within the given tolerance, it is printed as an integer.
3. The function attempts to:
   - Represent the number as a fraction.
   - Check if the square of the number can be expressed as a fraction.
   - Check if the number can be represented as a multiple of π.
4. The function selects the representation with the smallest error compared to the original number.
5. If none of the special formats (fraction, square root, or multiple of π) fit within the tolerance, the function outputs the number in decimal format.

**Usage:**  
The `format` function is useful in situations where mathematical expressions (such as fractions or multiples of π) need to be output in a readable way, especially in computational tools or symbolic computation environments.

---

### Example Usage

```c
#include<stdio.h>
#include "math_utils.h"
int main() {
  double n;

  printf("Enter the floating-point number (in standard form): ");
  scanf("%lf", &n);

  long long num, den;
  /*double err = getfrac(n, 1000, &num, &den);
  printf("The fraction is %lld/%lld,   error=%e\n", num, den, err);*/

  char res[1000];
  format(n, 1e-12, res);
  printf("Formatted text: %s\n", res);

  return 0;
}
