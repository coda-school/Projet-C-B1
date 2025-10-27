#ifndef CODA_END_PATH
#define CODA_END_PATH

#include "path_element.h"

/**
 * Represents the end of path element.
 * Represents the SVG path element code Z.
 */
typedef struct end_path_s {
} end_path_t;

/**
 * Destroys the given end of path element.
 * Note that this function frees memory.
 * @param end_path the end of path element to be destroyed.
 * @see end_path_t.
 */
void free_end_path(end_path_t *end_path);

/**
 * Prints out the given end of path element.
 * Note that this function is for debug purposes only.
 * @param end_path the end of path element to be printed out.
 * @see end_path_t.
 */
void print_end_path(end_path_t *end_path);

/**
 * Creates a new end of path element.
 * Note that this function allocates memory.
 * This function wraps the end of path in the path element structure.
 * @see end_path_t.
 * @see path_element_t.
 */
path_element_t *new_end_path();

/**
 * Converts the end of path to a string.
 * Note that this function allocates memory.
 * This function is 'static' (no arguments) because the end_path_t type is
 * empty.
 * @return a string.
 * @see end_path_t.
 */
char *end_of_path_to_string();

#endif
