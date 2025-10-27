#ifndef CODA_POLYGON
#define CODA_POLYGON

#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"

/**
 * Represents a polygon.
 * Note that this function allocates memory.
 * Note that this function wraps the new group in the shape_t structure.
 * @param points the polygon's corners.
 * @param styles the polygon's styles.
 * @return the new polygon's pointer.
 * @see point_node_t.
 * @see style_t.
 * @see polygon_t.
 * @see shape_t.
 */
shape_t *new_polygon(point_node_t *points, style_t *styles);

/**
 * Destroys the given polygon.
 * Note that this function frees memory.
 * @param polygon the polygon to be destroyed.
 * @see polygon_t.
 */
void free_polygon(polygon_t *polygon);

/**
 * Prints out the given polygon.
 * Note that this function is for debug purposes only.
 * @param polygon the polygon to be printed out.
 * @see polygon_t.
 */
void print_polygon(polygon_t *polygon);

#endif
