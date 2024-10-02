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