#ifndef CODA_CLI_STYLE
#define CODA_CLI_STYLE

#include "../models/styles/style.h"

/**
 * Displays a formatted version of the given style.
 * This function displays styles in xml format.
 * It is expected that the shape's tag has already been displayed and not
 * closed.
 * @param styles the styles to be displayed.
 * @see style_t.
 */
void cli_display_style(style_t *styles);

/**
 * Asks the user to update the given style's fill parameter.
 * If the user submits an empty answer, this function exits without performing
 * changes.
 * @param styles the styles to update.
 * @see color_t.
 * @see style_t.
 */
void cli_select_fill(style_t *styles);

/**
 * Asks the user to update the given style's outline parameter.
 * If the user submits an empty answer, this function exits without performing
 * changes.
 * @param styles the styles to update.
 * @see color_t.
 * @see style_t.
 */
void cli_select_outline(style_t *styles);

/**
 * Asks the user to update the given style's rotate parameter.
 * If the user submits an empty answer, this function exits without performing
 * changes.
 * @param styles the styles to update.
 * @see rotate_t.
 * @see style_t.
 */
void cli_select_rotate(style_t *styles);

/**
 * Asks the user to update the given style's translate X coordinate.
 * If the user submits an empty answer, this function exits without performing
 * changes.
 * @param styles the styles to update.
 * @see translate_t.
 * @see style_t.
 */
void cli_select_translate_x(point_t *point);

/**
 * Asks the user to update the given style's translate Y coordinate.
 * If the user submits an empty answer, this function exits without performing
 * changes.
 * @param styles the styles to update.
 * @see translate_t.
 * @see style_t.
 */
void cli_select_translate_y(point_t *point);

/**
 * Asks the user to update the given style's translate parameter.
 * If the users submits an empty answer, this function exits without performing
 * changes.
 * @param styles the styles to update.
 * @see translate_t.
 * @see style_t.
 */
void cli_select_translate(style_t *styles);

/**
 * Asks the user to update the given style's parameters.
 * If the users submits an empty answer, this function exits without performing
 * changes.
 * @param styles the styles to update.
 * @see style_t.
 */
void cli_edit_style(style_t *styles);

#endif
