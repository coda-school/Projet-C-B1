#ifndef CODA_PARSE_PATH
#define CODA_PARSE_PATH

#include "../../models/shapes/path/path.h"
#include "../../models/shapes/path/path_element.h"
#include "../serde.h"

/**
 * Attempts to parse a move to path element.
 * Note that this function expects the first char ('m' or 'M') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the move to path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new move to path element's pointer.
 * @see move_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_move_to(serdelizer_t *serdelizer);

/**
 * Attempts to parse a line to path element.
 * Note that this function expects the first char ('l' or 'L') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the line to path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new line to path element's pointer.
 * @see line_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_line_to(serdelizer_t *serdelizer);

/**
 * Attempts to parse a horizontal line to path element.
 * Note that this function expects the first char ('h' or 'H') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the horizontal line to path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new horizontal line to path element's pointer.
 * @see horizontal_line_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_horizontal_line_to(serdelizer_t *serdelizer);

/**
 * Attempts to parse a vertical line to path element.
 * Note that this function expects the first char ('v' or 'V') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the vertical line to path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new vertical line to path element's pointer.
 * @see vertical_line_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_vertical_line_to(serdelizer_t *serdelizer);

/**
 * Attempts to parse a cubic curve to path element.
 * Note that this function expects the first char ('c' or 'C') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the cubic curve to path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new cubic curve to path element's pointer.
 * @see cubic_curve_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_cubic_curve_to(serdelizer_t *serdelizer);

/**
 * Attempts to parse a cubic curve to shorthand path element.
 * Note that this function expects the first char ('s' or 'S') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the cubic curve to shorthand path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new cubic curve to shorthand path element's pointer.
 * @see shorthand_cubic_curve_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_cubic_curve_to_shorthand(serdelizer_t *serdelizer);

/**
 * Attempts to parse a quadratic curve to path element.
 * Note that this function expects the first char ('q' or 'Q') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the quadratic curve to path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new quadratic curve to path element's pointer.
 * @see quadratic_curve_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_quadratic_curve_to(serdelizer_t *serdelizer);

/**
 * Attempts to parse a quadratic curve to shorthand path element.
 * Note that this function expects the first char ('t' or 'T') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the quadratic curve to shorthand path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new quadratic curve to shorthand path element's pointer.
 * @see shorthand_quadratic_curve_to_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_quadratic_curve_to_shorthand(serdelizer_t *serdelizer);

/**
 * Attempts to parse a end of path path element.
 * Note that this function expects the first char ('z' or 'Z') to already be
 * consumed. Note that this function allocates memory. If the function could not
 * parse the end of path path element it returns NULL.
 * @param serdelizer the file accessor.
 * @return the new end of path path element's pointer.
 * @see end_path_t.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_end_of_path(serdelizer_t *serdelizer);

/**
 * Attempts to parse a path element.
 * Note that this function expects the last consumed char to be among the
 * following list [ 'm', 'M', 'l', 'L', 'h', 'H', 'v', 'V', 'c, 'C', 's', 'S',
 * 'q', 'Q', 't', 'T', 'z', 'Z']. If the function could not parse a path element
 * the function returns NULL.
 * @param serdelizer the file accessor.
 * @return the new path element's pointer.
 * @see path_element_t.
 * @see serdelizer_t.
 */
path_element_t *parse_path_element(serdelizer_t *serdelizer);

/**
 * Attempts to parse a sequence a path elements.
 * Note that this function allocates memory.
 * Note that this function expects the char 'd' to be already consumed. The
 * function will expected to consume the 'ata="' text sequence before parsing
 * any path element. The function will parse parse elements until reaching the
 * '"' character. Note that if the error in the parsing process it will return
 * NULL.
 * @param serdelizer the file accessor.
 * @return the parsed path element linked list's pointer.
 * @see path_element_t.
 * @see path_element_node_t.
 * @see serdelizer_t.
 */
path_element_node_t *parse_path_elements(serdelizer_t *serdelizer);

#endif
