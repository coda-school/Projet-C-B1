#ifndef CODA_RECTANGLE
#define CODA_RECTANGLE

#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"

/**
 * Creates a new rectangle.
 * Note that this function allocates memory.
 * Note that this function wraps the new group in the shape_t structure.
 * @param x      the rectangle's top left corner's X coordinate.
 * @param y      the rectangle's top left corner's Y coordinate.
 * @param width  the rectangle's width.
 * @param height the rectangle's height.
 * @param styles the rectangle's styles.
 * @return the new rectangle's pointer.
 * @see style_t.
 * @see rectangle_t.
 * @see shape_t.
 */
shape_t *new_rectangle(int x, int y, int width, int height, style_t *styles);

/**
 * Destroys the given rectangle.
 * Note that this function frees memory.
 * @param rectangle the rectangle to be destroyed.
 * @see rectangle_t.
 */
void free_rectangle(rectangle_t *rectangle);

/**
 * Prints out the given rectangle.
 * Note that this function is for debug purposes only.
 * @param rectangle the rectangle to be printed out.
 * @see rectangle_t.
 */
void print_rectangle(rectangle_t *rectangle);

/**
 * Converts the given rectangle to a string.
 * Note that this function allocates memory.
 * @param rectangle the rectangle to be converted.
 * @return a string.
 * @see rectangle_t.
 */
char *rectangle_to_string(rectangle_t *rectangle);

#endif
