/*
 **Author: Dipjyoti Das
 **Parts of the getfrac function were inspired by a solution from Stack Overflow.
 */
#include "math_utils.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include<stdio.h>
double getfrac(double n, long long maxden, long long *numerator,
               long long *denominator) {

  long long m[2][2];
  const double startx = n;

  /* Initialize matrix */
  m[0][0] = m[1][1] = 1;
  m[0][1] = m[1][0] = 0;

  /* Loop finding terms until denom gets too big */
  while (m[1][0] * (long long)n + m[1][1] <= maxden) {
    long long t;
    t = m[0][0] * (long long)n + m[0][1];
    m[0][1] = m[0][0];
    m[0][0] = t;
    t = m[1][0] * (long long)n + m[1][1];
    m[1][1] = m[1][0];
    m[1][0] = t;
    if (n == (double)(long long)n)
      break; // Division by zero
    n = 1 / (n - (double)(long long)n);
    if (n > (double)0x7FFFFFFF)
      break; // Representation failure
  }

  /* Now remaining n is between 0 and 1/ai */
  /* Approximate as either 0 or 1/m where m is max that will fit in maxden */
  /* First try zero */

  double err1 = startx - ((double)m[0][0] / (double)m[1][0]);

  long long num1 = m[0][0], den1 = m[1][0];

  /* Now try other possibility */
  long long ai = (maxden - m[1][1]) / m[1][0];
  m[0][0] = m[0][0] * ai + m[0][1];
  m[1][0] = m[1][0] * ai + m[1][1];

  double err2 = startx - ((double)m[0][0] / (double)m[1][0]);
  long long num2 = m[0][0], den2 = m[1][0];

  if (fabs(err1) < fabs(err2)) {
    (*numerator) = num1;
    (*denominator) = den1;
    return err1;
  } else {
    (*numerator) = num2;
    (*denominator) = den2;
    return err2;
  }
}

char* format(double N, double TOL, char *res1) {
  char* res = res1 ? res1 : (char *)malloc(150);
  	
  if (isnan(N)) {
    
	strcpy(res, "NaN");
    
	return res; // Not a  number
  }
  // Change the sign of n to positive, so that the numerator is printed with neg
  // sign, not the denom
  short int neg = 0;

  if (N < 0) {
    neg = 1;
    N = -1.0 * N;
  }
  const double n = N;

  

  long long num, den;
  double err2 = TOL + 1, err3 = TOL + 1, err_crnt = TOL + 1;
  short int min = -1;
  // Huge or very small number
  if ((long long)log10(n) + 1 > 9 || (long long)log10(n) - 1 <= -9) {
    snprintf(res, 100, "%s%.9e", neg == 1 ? "-" : "", n);
    return res;
  }
  // Int within tolerance
  if (fabs(n - (long long)n) < TOL) {
    snprintf(res, 100, "%s%lld", neg == 1 ? "-" : "", (long long)n);
    return res;
  }
  const double PI =3.1415926535897932384626433832795028841971693993751058209749;
  const double n2 = n / PI;
  char temp[3][105];
  // convert to fraction(Rational)
  if ((err_crnt = (const double)fabs(getfrac(n, 999, &num, &den))) < TOL) {
    min = 0;
    if(den==1) snprintf(temp[0], 100, "%s%lld", neg?"-": "" ,num);
    else snprintf(temp[0], 100, "%s%lld/%lld", neg ? "-" : "", num, den);
  }
  // Calculate if the square of n if rational

  
    getfrac(n * n, 1e4, &num, &den);
    err2 = (const double)fabs(n - sqrt((double)num / (double)den));
    if (err2 < TOL) {
      if (err2 >= err_crnt)
        goto chk;
      err_crnt = (const double)err2;
      min = 1;

      char NUM[50], DEN[50];

      if (fabs(sqrt(num) - (long long)sqrt(num)) < TOL)
        snprintf(NUM, 50, "%s%lld", neg == 1 ? "-" : "", (long long)sqrt(num));
      else
        snprintf(NUM, 50, "%ssqrt(%lld)", neg == 1 ? "-" : "", num);
      if (den == 1) {

        strcpy(temp[1], NUM);
      } else {
        if (fabs(sqrt(den) - (long long)sqrt(den)) < TOL)
          snprintf(DEN, 50, "%lld", (long long)sqrt(den));
        else
          snprintf(DEN, 50, "sqrt(%lld)", den);

        snprintf(temp[1], 100, "%s/%s", NUM, DEN);
      }
    }
chk:
  // Check if it can be represented as a multiple of PI
  
  
  if ((err3 = (const double)fabs(getfrac(n2, 999, &num, &den))) < TOL) {
    if (err3 >= err_crnt)
      goto chk2;
    err_crnt = (const double)err3;
    min = 2;
    if (den == 1)
      snprintf(temp[2], 100, "%s%lld*pi", neg ? "-" : "", num);
    else
      snprintf(temp[2], 100, "%s%lld*pi/%lld", neg ? "-" : "", num, den);
  }

  
chk2:
  if (min == -1) {
    snprintf(res, 100, "%s%.9lf", neg ? "-" : "", n);
    return res; // formatting failed
  }

  strcpy(res, temp[min]);
  return res;
}
