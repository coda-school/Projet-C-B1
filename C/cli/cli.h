#ifndef CODA_CLI
#define CODA_CLI

#include "../models/shapes/svg.h"
#include "../serde/serialize/export.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Lists all cli user questions output.
 * - CLI_VALID : The user submitted a valid answer.
 * - CLI_INVALID : The user submitted an invalid answer.
 * - CLI_EMPTY : The user submitted an empty answer.
 */
typedef enum cli_output_e { CLI_VALID, CLI_INVALID, CLI_EMPTY } cli_output_t;

/**
 * Clears out the terminal.
 */
void cli_clear_screen();

/**
 * Prints out the given string.
 * @param content the string to print.
 */
void cli_print_content(char *content);

/**
 * Prints out the given string in red.
 * @param content the string to print.
 */
void cli_print_error(char *content);

/**
 * Prints out the given string in green.
 * @param content the string to print.
 */
void cli_print_success(char *content);

/**
 * Prints out "depth" times 2-spaces tabs.
 */
void cli_print_spaces(int depth);

/**
 * Displays a formatted version of the given svg.
 * This function uses the xml format.
 * @param svg the svg to display.
 * @see svg_t.
 */
void cli_print_svg(svg_t *svg);

/**
 * Displays a formatted version of the given point linked list.
 * @param points the point linked list to display.
 * @see point_node_t.
 */
void cli_print_points(point_node_t *points);

/**
 * Displays a formatted version of the given path element linked list.
 * @param elements the path element linked list.
 * @see path_element_node_t.
 */
void cli_print_path_elements(path_element_node_t *elements);

/**
 * Displays a formatted version of the given shape linked list.
 * @param shapes the shape linked list.
 * @see shape_node_t.
 */
void cli_print_shapes(shape_node_t *shapes);

/**
 * Asks the user for an integer.
 * If the user submits a valid integer the value parameter is set.
 * @param value a pointer to an integer to set the valid integer submitted by
 * the user.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_int(int *value);

/**
 * Asks the user for a string.
 * If the user submits a valid string (length(string) <= max_length) then the
 * result and size parameters are set.
 * @param result     a pointer to a string to set the valid string submitted by
 * the user.
 * @param size       a pointer to set the valid string length submitted by the
 * user.
 * @param max_length the string's pax length.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_string(char *result, size_t *size, size_t max_length);

/**
 * Asks the user for a boolean.
 * If the user submits a valid boolean the value parameter is set.
 * @param value a pointer to a boolean to set the valid boolean submitted by
 * the user.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_bool(bool *value);

/**
 * Asks the user for a index in the range [`min`, `max`].
 * If the user submits a valid boolean the index parameter is set.
 * @param min   the minimum index allowed.
 * @param max   the maximum index allowed.
 * @param value a pointer to an integer to set the valid integer submitted by
 * the user.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_index(int min, int max, int *index);

/**
 * Waits for the user to press a key.
 */
void cli_press_any_key();

/**
 * Asks for the user to select a point's index in the given point linked list.
 * If the user submitted answer is value the index parameter is set.
 * The function prints out the point linked list, then prints out the given
 * prompt. The function displays the allowed range using the length of the
 * linked list, the `include_lower` and `include_upper` parameters.
 * @param prompt        the prompt to display.
 * @param points        the point linked list.
 * @param index         a pointer to an integer to set the valid integer
 * submitted by the user.
 * @param include_lower indicates if the user can submit the `0` value.
 * @param include_upper indicates if the user can submit the `length(points)`
 * value.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_point_index(char *prompt, point_node_t *points,
                                     int *index, bool include_lower,
                                     bool include_upper);

/**
 * Asks for the user to select a path element's index in the given path element
 * linked list. If the user submitted answer is value the index parameter is
 * set. The function prints out the path element linked list, then prints out
 * the given prompt. The function displays the allowed range using the length of
 * the linked list, the `include_lower` and `include_upper` parameters.
 * @param prompt        the prompt to display.
 * @param elements      the path element linked list.
 * @param index         a pointer to an integer to set the valid integer
 * submitted by the user.
 * @param include_lower indicates if the user can submit the `0` value.
 * @param include_upper indicates if the user can submit the `length(elements)`
 * value.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_path_element_index(char *prompt,
                                            path_element_node_t *elements,
                                            int *index, bool include_lower,
                                            bool include_upper);

/**
 * Asks for the user to select a shape's index in the given shape linked list.
 * If the user submitted answer is value the index parameter is set.
 * The function prints out the shape linked list, then prints out the given
 * prompt. The function displays the allowed range using the length of the
 * linked list, the `include_lower` and `include_upper` parameters.
 * @param prompt        the prompt to display.
 * @param shapes        the shape linked list.
 * @param index         a pointer to an integer to set the valid integer
 * submitted by the user.
 * @param include_lower indicates if the user can submit the `0` value.
 * @param include_upper indicates if the user can submit the `length(shapes)`
 * value.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_shape_index(char *prompt, shape_node_t *shapes,
                                     int *index, bool include_lower,
                                     bool include_upper);

/**
 * Asks the user to select an integer.
 * The function displays the given entity string, then displays the given
 * prompt. if multiple attemps are allowed, the function will repeatedly asks
 * for an int until a valid or empty answer is submitted. If multiple attemps
 * are allowed and the previous submitted value is invalid the error message is
 * displayed. When a value is submitted, the given predicate function is called
 * to check if it is valid or not. If the submitted value is valid is submitted,
 * the value parameter is set.
 * @param entity_display         the entity string to display.
 * @param prompt                 the prompt string to display.
 * @param error_message          the error message to display if the
 * allow_multiple_attempts is true and an invalid answer was submitted.
 * @param predicate               a function pointer of signature int -> bool to
 * validate the user's submitted values.
 * @param allow_multiple_attempts indicates if the user can have multiple
 * attempts.
 * @return the user cli output state.
 * @see cli_output_t.
 */
cli_output_t cli_ask_for_int_parameter(char *entity_display, char *prompt,
                                       char *error_message,
                                       bool (*predicate)(int),
                                       bool allow_multiple_attempts,
                                       int *value);

/**
 * Asks the user to update the given viewport.
 * @param viewport the viewport to update.
 * @see viewport_t.
 */
void cli_edit_viewport(viewport_t *viewport);

/**
 * Asks the user to create a new svg.
 * Note that this function allocates memory.
 * @return the new svg's pointer.
 * @see svg_t.
 */
svg_t *cli_create_new_svg();

/**
 * Asks the user for a file path.
 * Attempts to open and parse the given file path.
 * If an error occures (invalid file path, invalid file content, ...) the error
 * is printed out and the function returns NULL.
 * @return the new svg's pointer.
 * @see export_config_t.
 * @see serdelizer_t.
 * @see svg_t.
 */
svg_t *cli_open_svg();

/**
 * Asks the user to update the given svg.
 * @param svg the svg to update.
 * @see svg_t.
 */
void cli_edit_svg(svg_t *svg);

/**
 * Asks the user to create new export configs.
 * @return the new export config's pointer.
 * @see export_config_t.
 */
export_config_t *cli_new_export_config();

/**
 * Asks the user to select a file path to save the given svg.
 * @param svg the svg to save.
 * @see export_config_t.
 * @see serdelizer_t.
 * @see svg_t.
 */
void cli_export_svg(svg_t *svg);

/**
 * Asks the user to select a file path to export the given svg to html.
 * @param svg the svg to export.
 * @see svg_t.
 */
void cli_export_svg_to_html(svg_t *svg);

/**
 * Displays the cli main menu and asks the user for actions to perform.
 */
void cli_main_menu();

#endif
