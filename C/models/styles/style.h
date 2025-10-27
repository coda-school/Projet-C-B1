#ifndef CODA_STYLE
#define CODA_STYLE

#include "../styles/color.h"
#include "../styles/rotate.h"
#include "../utils/point.h"

/**
 * Represents shape's style.
 * @param fill the fill color.
 * @param outline the outline color.
 * @param translate the translate transformation.
 * @param rotate the rotate transformation.
 * @see color_t.
 * @see rotate_t.
 * @see point_t.
 */
typedef struct style_s {
  color_t *fill;
  color_t *outline;
  point_t *translate;
  rotate_t *rotate;
} style_t;

/**
 * Creates a new style.
 * This function allocates memory.
 * @param fill the fill color.
 * @param outline the outline color.
 * @param translate the translate transformation.
 * @param the rotate transformation value.
 * @return the new style's pointer.
 * @see color_t.
 * @see rotate_t.
 * @see point_t.
 * @see style_t.
 */
style_t *new_style(color_t *fill, color_t *outline, point_t *translate,
                   rotate_t *rotate);

/**
 * Creates a default styles.
 * Note that this function allocates memory.
 * The fill color will be the default color.
 * The outline color will be the default color.
 * The translate will be set to (0, 0).
 * The rotate will be set to circular(0).
 * @return the new style's pointer.
 * @see color_t.
 * @see rotate_t.
 * @see point_t.
 * @see style_t.
 */
style_t *new_default_style();

/**
 * Duplicates the given styles.
 * Note that this function allocates memory.
 * @param style the style to be duplicated.
 * @return the duplicated style's pointer.
 * @see color_t.
 * @see rotate_t.
 * @see point_t.
 * @see style_t.
 */
style_t *clone_style(style_t *style);

/**
 * Destroys the given style.
 * Note that this function frees memory.
 * @param the style to be destroyed.
 * @see color_t.
 * @see rotate_t.
 * @see point_t.
 * @see style_t.
 */
void free_style(style_t *style);

/**
 * Prints out the given style.
 * Note that this function is for debug purposes only.
 * @param style the style to be printed out.
 * @see color_t.
 * @see rotate_t.
 * @see point_t.
 * @see style_t.
 */
void print_style(style_t *style);

#endif
