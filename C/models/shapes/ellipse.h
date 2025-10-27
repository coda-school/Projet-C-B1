#ifndef CODA_ELLIPSE
#define CODA_ELLIPSE

#include "../styles/style.h"
#include "shape.h"

/**
 * Creates a new ellipse.
 * Note that this function allocates memory.
 * Note that this function wraps the new ellipse in the shape_t structure.
 * @param center_x the ellipse center's X coordinate.
 * @param center_y the ellipse center's Y coordinate.
 * @param radius_x the ellipse's width.
 * @param radius_y the ellipse's height.
 * @param styles   the ellipse's styles.
 * @return the new ellipse's pointer.
 * @see style_t.
 * @see ellipse_t.
 * @see shape_t.
 */
shape_t *new_ellipse(int center_x, int center_y, int radius_x, int radius_y,
                     style_t *styles);

/**
 * Destroys the given ellipse.
 * Note that this function frees memory.
 * @param ellipse the ellipse to be destroyed.
 * @see ellipse_t.
 */
void free_ellipse(ellipse_t *ellipse);

/**
 * Prints out the given ellipse.
 * Note that this function is for debug purposes only.
 * @param ellipse the ellipse to be printed out.
 * @see ellipse_t.
 */
void print_ellipse(ellipse_t *ellipse);

/**
 * Converts the given ellipse to a string.
 * Note that this function allocates memory.
 * @param ellipse the ellipse to be converted.
 * @return a string.
 * @see ellipse_t.
 */
char *ellipse_to_string(ellipse_t *ellipse);

#endif
