#ifndef CODA_UTILS
#define CODA_UTILS

#include <stdbool.h>

/**
 * Returns the minimum value between a and b.
 * @param a an integer.
 * @param b an integer.
 * @return the minimum value between a and b.
 */
int min(int a, int b);

/**
 * Returns the maximum value between a and b.
 * @param a an integer.
 * @param b an integer.
 * @return the maximum value between a and b.
 */
int max(int a, int b);

/**
 * Checks if the given integer is greater than 0.
 * @param n an integer.
 * @return true if the integer is greater than 0.
 */
bool must_be_strict_positive(int n);

#endif
