#ifndef CODA_COLORS
#define CODA_COLORS

#include <stdbool.h>

/**
 * Represents an RGBA color.
 * @param red        [0-255] red quantity value.
 * @param green      [0-255] green quatity value.
 * @param blue       [0-255] blue quatity value.
 * @param tranparent [0-255] transparency quatity value.
 */
typedef struct color_s {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char transparent;
} color_t;

/**
 * Creates a new color.
 * Note that this function allocates memory.
 * @param red        [0-255] red quantity value.
 * @param green      [0-255] green quatity value.
 * @param blue       [0-255] blue quatity value.
 * @param tranparent [0-255] transparency quatity value.
 * @return the new color's pointer.
 * @see color_t.
 */
color_t *new_color(unsigned char red, unsigned char green, unsigned char blue,
                   unsigned char transparent);

/**
 * Creates a default color. Returns a black transparent color (0, 0, 0, 0).
 * Note that this function allocates memory.
 * @return the new color's pointer.
 * @see color_t.
 */
color_t *new_default_color();

/**
 * Duplicates the given color.
 * Note that this function allocates memory.
 * @param color the color to be duplicated.
 * @return the duplicated color's pointer.
 * @see color_t.
 */
color_t *clone_color(color_t *color);

/**
 * Destroys the given color.
 * Note that this function frees memory.
 * @param color the color to be destroyed.
 * @see color_t.
 */
void free_color(color_t *color);

/**
 * Prints out the given color.
 * Note that this function is for debug purposes only.
 * @param color the color to be printed out.
 * @see color_t.
 */
void print_color(color_t *color);

#endif
