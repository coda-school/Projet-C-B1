#ifndef CODA_LINE
#define CODA_LINE

#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"

/**
 * Creates a new line.
 * Note that this function allocates memory.
 * Note that this function wraps the new group in the shape_t structure.
 * @param start  the line's start position.
 * @param end    the line's end position.
 * @param styles the line's styles.
 * @return the new line's pointer.
 * @see point_t.
 * @see style_t.
 * @see line_t.
 * @see shape_t.
 */
shape_t *new_line(point_t *start, point_t *end, style_t *styles);

/**
 * Prints out the given line.
 * Note that this function is for debug purposes only.
 * @param line the line to be printed out.
 * @see line_t.
 */
void print_line(line_t *line);

/**
 * Destroys the given line.
 * Note that this function frees memory.
 * @param line the line to be destroyed.
 * @see line_t.
 */
void free_line(line_t *line);

/**
 * Converts the given line to a string.
 * Note that this function allocates memory.
 * @param line the line to be converted.
 * @return a string.
 * @see line_t.
 */
char *line_to_string(line_t *line);

#endif
