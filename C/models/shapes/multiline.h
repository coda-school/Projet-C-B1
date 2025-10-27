#ifndef CODA_MULTILINE
#define CODA_MULTILINE

#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"

/**
 * Creates a new multiline.
 * Note that this function allocates memory.
 * Note that this function wraps the new group in the shape_t structure.
 * @param points the multiline's points.
 * @param styles the multiline's styles.
 * @return the new multiline's pointer.
 * @see point_node_t.
 * @see style_t.
 * @see multiline_t.
 * @see shape_t.
 */
shape_t *new_multiline(point_node_t *points, style_t *styles);

/**
 * Destroys the given multiline.
 * Note that this function frees memory.
 * @param multiline the multiline to be destroyed.
 * @see multiline_t.
 */
void free_multiline(multiline_t *multiline);

/**
 * Prints out the given multiline.
 * Note that this function is for debug purposes only.
 * @param multiline the multiline to be printed out.
 * @see multiline_t.
 */
void print_multiline(multiline_t *multiline);

#endif
