#ifndef CODA_EXPORT_PATH
#define CODA_EXPORT_PATH

#include "../../models/shapes/path/path.h"
#include "../../models/shapes/path/path_element.h"
#include "../serde.h"
#include "export.h"

/**
 * Writes down the given move to path element.
 * @param move_to    the move to path element to export.
 * @param serdelizer the file accessor.
 * @return returns true if the operation suceeded.
 * @see move_to_t.
 * @see serdelizer_t.
 */
bool export_move_to(move_to_t *move_to, serdelizer_t *serdelizer);

/**
 * Writes down the given line to path element.
 * @param line_to    the line to path element to export.
 * @param serdelizer the file accessor.
 * @return returns true if the operation suceeded.
 * @see line_to_t.
 * @see serdelizer_t.
 */
bool export_line_to(line_to_t *line_to, serdelizer_t *serdelizer);

/**
 * Writes down the given horizontal line to path element.
 * @param horizontal_line_to the horizontal line to path element to export.
 * @param serdelizer         the file accessor.
 * @return returns true if the operation suceeded.
 * @see horizontal_line_to_t.
 * @see serdelizer_t.
 */
bool export_horizontal_line_to(horizontal_line_to_t *horizontal_line_to,
                               serdelizer_t *serdelizer);

/**
 * Writes down the given vertical line to path element.
 * @param vertical_line_to the vertical line to path element to export.
 * @param serdelizer         the file accessor.
 * @return returns true if the operation suceeded.
 * @see vertical_line_to_t.
 * @see serdelizer_t.
 */
bool export_vertical_line_to(vertical_line_to_t *vertical_line_to,
                             serdelizer_t *serdelizer);

/**
 * Writes down the given end of path path element.
 * @param end_of_path the end of path path element to export.
 * @param serdelizer  the file accessor.
 * @return returns true if the operation suceeded.
 * @see end_path_t.
 * @see serdelizer_t.
 */
bool export_end_of_path(end_path_t *end_of_path, serdelizer_t *serdelizer);

/**
 * Writes down the given cubic curve to path element.
 * @param cubic_curve_to the cubic curve to path element to export.
 * @param serdelizer     the file accessor.
 * @return returns true if the operation suceeded.
 * @see cubic_curve_to_t.
 * @see serdelizer_t.
 */
bool export_cubic_curve_to(cubic_curve_to_t *cubic_curve_to,
                           serdelizer_t *serdelizer);

/**
 * Writes down the given cubic curve to shorthand path element.
 * @param shorthand_cubic_curve_to the cubic curve to shorthand path element to
 * export.
 * @param serdelizer               the file accessor.
 * @return returns true if the operation suceeded.
 * @see shorthand_cubic_curve_to_t.
 * @see serdelizer_t.
 */
bool export_cubic_curve_to_shorthand(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to,
    serdelizer_t *serdelizer);

/**
 * Writes down the given quadratic curve to path element.
 * @param quadratic_curve_to the quadratic curve to path element to export.
 * @param serdelizer     the file accessor.
 * @return returns true if the operation suceeded.
 * @see quadratic_curve_to_t.
 * @see serdelizer_t.
 */
bool export_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to,
                               serdelizer_t *serdelizer);

/**
 * Writes down the given quadratic curve to shorthand path element.
 * @param shorthand_quadratic_curve_to the quadratic curve to shorthand path
 * element to export.
 * @param serdelizer               the file accessor.
 * @return returns true if the operation suceeded.
 * @see shorthand_quadratic_curve_to_t.
 * @see serdelizer_t.
 */
bool export_quadratic_curve_to_shorthand(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to,
    serdelizer_t *serdelizer);

/**
 * Writes down the given path element.
 * @param path_element the path element to export.
 * @param serdelizer   the file accessor.
 * @return returns true if the operation succeeded.
 * @see path_element_t.
 * @see serdelizer_t.
 */
bool export_path_element(path_element_t *path_element,
                         serdelizer_t *serdelizer);

/**
 * Writes down the given path element linked list.
 * @param path_elements the path element linked list to export.
 * @param serdelizer    the file accessor.
 * @param config        the export configs.
 * @param depth         the amount of spacing to write before writing the path
 * element linked list.
 * @return returns true if the operation succeeded.
 * @see path_element_t.
 * @see path_element_node_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_path_elements(path_element_node_t *path_elements,
                          serdelizer_t *serdelizer, export_config_t *config,
                          int depth);

#endif
