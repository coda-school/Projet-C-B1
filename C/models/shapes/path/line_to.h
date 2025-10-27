#ifndef CODA_LINE_TO
#define CODA_LINE_TO

#include "../../utils/point.h"
#include "path_element.h"

/**
 * Represents a line to path element.
 * Represents the SVG path element code L <int> <int>.
 * Note that this function allocates memory.
 * @param point the line's destination.
 * @see point_t.
 */
struct line_to_s {
  point_t *point;
};

/**
 * Destroys the given line.
 * Note that this function frees memory.
 * @param line_to the line to be destroyed.
 * @see line_to_t.
 */
void free_line_to(line_to_t *line_to);

/**
 * Prints out the given line to path element.
 * Note that this function is for debug purposes only.
 * @param line_to the line to path element to be printed out.
 * @see line_to_t.
 */
void print_line_to(line_to_t *line_to);

/**
 * Creates a new line to line path element.
 * Note that this function allocates memory.
 * This function wraps the line to in the path element structure.
 * @param point the line's destination.
 * @return the new line's pointer.
 * @see point_t.
 * @see line_to_t.
 * @see path_element_t.
 */
path_element_t *new_line_to(point_t *point);

/**
 * Converts the given line to path element to a string.
 * Note that this function allocates memory.
 * @param line_to the line to be converted.
 * @return a string.
 * @see line_to_t.
 */
char *line_to_to_string(line_to_t *line_to);

/**
 * Prints out the given vertical line to path element.
 * Note that this function is for debug purposes only.
 * @param vertical_line_to the vertical line to path element to be printed out.
 * @see vertical_line_to_t.
 */
void print_vertical_line_to(vertical_line_to_t vertical_line_to);

/**
 * Creates a new vertical line to path element.
 * Represents the SVG path element code V <int>.
 * Note that this function allocates memory.
 * This function wraps the vertical line to in the path element structure.
 * @param position the vertical line's destination.
 * @return the new vertical line's pointer.
 * @see vertical_line_to_t.
 * @see path_element_t.
 */
path_element_t *new_vertical_line_to(int position);

/**
 * Converts the given vertical line to path element to a string.
 * Note that this function allocates memory.
 * @param vertical_line_to the vertical line to path element to be converted.
 * @return a string.
 * @see vertical_line_to_t.
 */
char *vertical_line_to_to_string(vertical_line_to_t vertical_line_to);

/**
 * Prints out the given horizontal line to path element.
 * Note that this function is for debug purposes only.
 * @param horizontal_line_to the horizontal line to path element to be printed
 * out.
 * @see horizontal_line_to_t.
 */
void print_horizontal_line_to(horizontal_line_to_t horizontal_line_to);

/**
 * Creates a new horizontal line to path element.
 * Represents the SVG path element code H <int>.
 * Note that this function allocates memory.
 * This function wraps the horizontal line to in the path element structure.
 * @param position the horizontal line's destination.
 * @return the new horizontal line's pointer.
 * @see horizontal_line_to_t.
 * @see path_element_t.
 */
path_element_t *new_horizontal_line_to(int position);

/**
 * Converts the given horizontal line to path element to a string.
 * Note that this function allocates memory.
 * @param horizontal_line_to the horizontal line to path element to be
 * converted.
 * @return a string.
 * @see horizontal_line_to_t.
 */
char *horizontal_line_to_to_string(horizontal_line_to_t horizontal_line_to);

#endif
