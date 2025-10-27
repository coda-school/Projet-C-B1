#ifndef CODA_CLI_PATH
#define CODA_CLI_PATH

#include "../models/shapes/path/path.h"

/**
 * Displays a formatted version of the given move to path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * @param move_to the move to path element to be displayed.
 * @see move_to_t.
 */
void cli_print_move_to(move_to_t *move_to);

/**
 * Displays a formatted version of the given line to path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * @param line_to the line to path element to be displayed.
 * @see line_to_t.
 */
void cli_print_line_to(line_to_t *line_to);

/**
 * Displays a formatted version of the given vertical line to path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * @param vertical_line_to the vertical line to path element to be displayed.
 * @see vertical_line_to_t.
 */
void cli_print_vertical_line_to(vertical_line_to_t vertical_line_to);

/**
 * Displays a formatted version of the given horizontal line to path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * @param horizontal_line_to the horizontal line to path element to be
 * displayed.
 * @see horizontal_line_to_t.
 */
void cli_print_horizontal_line_to(horizontal_line_to_t horizontal_line_to);

/**
 * Displays a formatted version of the given cubic curve to path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * @param cubic_curve_to the cubic curve to path element to be displayed.
 * @see cubic_curve_to_t.
 */
void cli_print_cubic_curve_to(cubic_curve_to_t *cubic_curve_to);

/**
 * Displays a formatted version of the given cubic curve to shorthand path
 * element. It is expected that the path's tag and data parameter have already
 * been displayed and not closed.
 * @param cubic_curve_to_shorthand the cubic curve to shorthand path element to
 * be displayed.
 * @see shorthand_cubic_curve_to_t.
 */
void cli_print_cubic_curve_to_shorthand(
    shorthand_cubic_curve_to_t *cubic_curve_to_shorthand);

/**
 * Displays a formatted version of the given quadratic curve to path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * @param quadratic_curve_to the quadratic curve to path element to be
 * displayed.
 * @see quadratic_curve_to_t.
 */
void cli_print_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to);

/**
 * Displays a formatted version of the given quadratic curve to shorthand path
 * element. It is expected that the path's tag and data parameter have already
 * been displayed and not closed.
 * @param quadratic_curve_to_shorthand the quadratic curve to shorthand path
 * element to be displayed.
 * @see shorthand_quadratic_curve_to_t.
 */
void cli_print_quadratic_curve_to_shorthand(
    shorthand_quadratic_curve_to_t *quadratic_curve_to_shorthand);

/**
 * Displays a formatted version of the end of path path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * Note that this function has no paramter (is static) because the end_path_t
 * type is empty.
 * @see end_path_t.
 */
void cli_print_end_of_path();

/**
 * Displays a formatted version of given path path element.
 * It is expected that the path's tag and data parameter have already been
 * displayed and not closed.
 * @param path_element the path element to display.
 * @see path_element_t.
 */
void cli_print_path_element(path_element_t *path_element);

/**
 * Asks the user to update the given move to path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param move_to the move to path element to update.
 * @see move_to_t.
 */
void cli_edit_move_to(move_to_t *move_to);

/**
 * Asks the user to update the given line to path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param line_to the line to path element to update.
 * @see line_to_t.
 */
void cli_edit_line_to(line_to_t *line_to);

/**
 * Asks the user to update the given horizontal line to path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param horizontal_line_to the horizontal line to path element to update.
 * @see horizontal_line_to_t.
 */
void cli_edit_horizontal_line_to(horizontal_line_to_t *horizontal_line_to);

/**
 * Asks the user to update the given vertical line to path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param vertical_line_to the vertical line to path element to update.
 * @see vertical_line_to_t.
 */
void cli_edit_vertical_line_to(vertical_line_to_t *vertical_line_to);

/**
 * Asks the user to update the given cubic curve to path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param cubic_curve_to the cubic curve to path element to update.
 * @see cubic_curve_to_t.
 */
void cli_edit_cubic_curve_to(cubic_curve_to_t *cubic_curve_to);

/**
 * Asks the user to update the given cubic curve to shorthand path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param cubic_curve_to_shorthand the cubic curve to shorthand path element to
 * update.
 * @see shorthand_cubic_curve_to_t.
 */
void cli_edit_cubic_curve_to_shorthand(
    shorthand_cubic_curve_to_t *cubic_curve_to_shorthand);

/**
 * Asks the user to update the given quadratic curve to path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param quadratic_curve_to the quadratic curve to path element to update.
 * @see quadratic_curve_to_t.
 */
void cli_edit_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to);

/**
 * Asks the user to update the given quadratic curve to shorthand path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param quadratic_curve_to_shorthand the quadratic curve to shorthand path
 * element to update.
 * @see shorthand_quadratic_curve_to_t.
 */
void cli_edit_quadratic_curve_to_shorthand(
    shorthand_quadratic_curve_to_t *quadratic_curve_to_shorthand);

/**
 * Asks the user to update the given path element.
 * If the user submits an empty answer the function exists without performing
 * any updates.
 * @param path_element the path element to update.
 * @see path_element_t.
 */
void cli_edit_path_element(path_element_t *path_element);

/**
 * Creates a new move to path element. The calls the `cli_edit_move_to`
 * function. Note that this function allocates memory.
 * @return the new move to path element's pointer.
 * @see move_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_move_to();

/**
 * Creates a new line to path element. The calls the `cli_edit_line_to`
 * function. Note that this function allocates memory.
 * @return the new line to path element's pointer.
 * @see line_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_line_to();

/**
 * Creates a new vertical line to path element. The calls the
 * `cli_edit_vertical_line_to` function. Note that this function allocates
 * memory.
 * @return the new vertical line to path element's pointer.
 * @see vertital_line_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_vertical_line_to();

/**
 * Creates a new horizontal line to path element. The calls the
 * `cli_edit_horizontal_line_to` function. Note that this function allocates
 * memory.
 * @return the new horizontal line to path element's pointer.
 * @see horizontal_line_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_horizontal_line_to();

/**
 * Creates a new cubic curve to path element. The calls the
 * `cli_edit_cubic_curve_to` function. Note that this function allocates memory.
 * @return the new cubic curve to path element's pointer.
 * @see cubic_curve_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_cubic_curve_to();

/**
 * Creates a new cubic curve to shorthand path element. The calls the
 * `cli_edit_cubic_curve_to_shorthand` function. Note that this function
 * allocates memory.
 * @return the new cubic curve to shorthand path element's pointer.
 * @see shorthand_cubic_curve_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_cubic_curve_to_shorthand();

/**
 * Creates a new quadratic curve to path element. The calls the
 * `cli_edit_quadratic_curve_to` function. Note that this function allocates
 * memory.
 * @return the new quadratic curve to path element's pointer.
 * @see quadratic_curve_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_quadratic_curve_to();

/**
 * Creates a new cubic quadratic to shorthand path element. The calls the
 * `cli_edit_cubic_quadratic_to_shorthand` function. Note that this function
 * allocates memory.
 * @return the new cubic quadratic to shorthand path element's pointer.
 * @see shorthand_quadratic_curve_to_t.
 * @see path_element_t.
 */
path_element_t *cli_create_new_quadratic_curve_to_shorthand();

/**
 * Asks the user to select what path element to create.
 * If the users submit an empty answer, the function returns NULL.
 * Else the function calls the associated cli create function.
 * @return the new path element's pointer.
 * @see path_element_t.
 */
path_element_t *cli_new_path_element();

#endif
