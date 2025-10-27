#ifndef CODA_PARSER
#define CODA_PARSER

#include "../../models/shapes/svg.h"
#include "../../models/styles/color.h"
#include "../../models/utils/point.h"
#include "../serde.h"

/**
 * Attempts to consume the given char.
 * @param serdelizer the file accessor.
 * @param c          the char expected to be consumed.
 * @return true if the next consumed char is the one given.
 * @see serdelizer_t.
 */
bool consume_next_char(serdelizer_t *serdelizer, char c);

/**
 * Attempts to consume the given string.
 * @param serdelizer the file accessor.
 * @param pattern    the string expected to be consumed.
 * @return true if the next consumed string sequence is the one given.
 * @see serdelizer_t.
 */
bool consume_pattern(serdelizer_t *serdelizer, char *pattern);

/**
 * Checks if the given char is a digit.
 * I.e. it checks if c is among this list : ['0', '1', '2' '3', '4', '5', '6',
 * '7', '8', '9'].
 * @param c the char to check.
 * @return returns true if the given char is a digit.
 */
bool is_char_digit(char c);

/**
 * Checks if the given char is an hexadecimal digit.
 * I.e. it checks if c is among this list : ['0', '1', '2' '3', '4', '5', '6',
 * '7', '8', '9', 'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f'].
 * @param c the char to check.
 * @return returns true if the given char is an hexadecimal digit.
 */
bool is_char_hexa(char c);

/**
 * Converts the given char to an int.
 * If the char is not a digit the programs fails and terminates.
 * @param c the char to convert.
 * @return returns the converted char.
 */
int char_to_int(char c);

/**
 * Converts the given hexadecimal digit char to an int.
 * If the char is not a digit the programs fails and terminates.
 * @param c the hexadecimal digit to convert.
 * @returns returns the converted char.
 */
int hexa_to_int(char c);

/**
 * Defines the int parsing result type.
 * @param value   holds the parsed value.
 * @param success indicates if the parsing was successful.
 */
typedef struct int_parsing_result_s {
  int value;
  bool success;
} int_parsing_result_t;

/**
 * Attempts to parse an int.
 * The base parameter is the first digit of the parsed int. If the value is 0 it
 * does not affect the parsing result. If the previous function has already
 * consumed a digit, the base parameter uses it for the parsing process. This
 * function can parse negative numbers only if the base parameter is 0 otherwise
 * it fails. The function returns after consuming a non digit character. If the
 * must_consume parameter is true and the function immediately consumes a non
 * digit character the function fails.
 * @param serdelizer   the file accessor.
 * @param base         holds the first digit of the number to parse.
 * @param must_consume indicates if the function must consume at least 1 digit
 * to succeed.
 * @return a parsing result structure holding the parsed value and the output
 * state.
 * @see serdelizer_t.
 * @see int_parsing_result_t.
 */
int_parsing_result_t parse_int(serdelizer_t *serdelizer, int base,
                               bool must_consume);

/**
 * Defines the unisgned character parsing result type.
 * @param value   holds the parsed value.
 * @param success indicates if the parsing was successful.
 */
typedef struct uchar_parsing_result_s {
  unsigned char value;
  bool success;
} uchar_parsing_result_t;

/**
 * Attempts to parse an hexa byte (i.e. 2 hexadecimal digits).
 * @param serdelizer the file accessor.
 * @return a parsing result structure holding the parsed value and the output
 * state.
 * @see serdelizer_t.
 * @see uchar_parsing_result_t.
 */
uchar_parsing_result_t parse_hexa_byte(serdelizer_t *serdelizer);

/**
 * Attempts to parse a point.
 * Note that this function allocates memory.
 * If the function failed to parse a point it returns NULL.
 * @param serdelizer the file accessor.
 * @return the parsed point.
 * @see serdelizer_t.
 */
point_t *parse_point(serdelizer_t *serdelizer);

/**
 * Attempts to parse a color.
 * Note that this function allocates memory.
 * If the function failed to parse a color it returns NULL.
 * @param serdelizer the file accessor.
 * @return the parsed color.
 * @see serdelizer_t.
 */
color_t *parse_color(serdelizer_t *serdelizer);

/**
 * Attempts to parse a integer parameter.
 * An integer parameter matches the following pattern [parameter_name]="[int]".
 * @param serdelizer     the file accessor.
 * @param parameter_name the parameter's name to parse.
 * @return a parsing result structure holding the parsed value and the output
 * state.
 * @see serdelizer_t.
 * @see int_parsing_result_t.
 */
int_parsing_result_t parse_int_parameter(serdelizer_t *serdelizer,
                                         char *parameter_name);

/**
 * Attempts to parse a color parameter.
 * Note that this function allocates memory.
 * An integer parameter matches the following pattern
 * [parameter_name]="[color]". If the parsing fails it returns NULL.
 * @param serdelizer     the file accessor.
 * @param parameter_name the parameter's name to parse.
 * @return the parsed color's pointer
 * @see serdelizer_t.
 * @see color_t.
 */
color_t *parse_color_parameter(serdelizer_t *serdelizer, char *parameter_name);

/**
 * Attempts to parse a point parameter.
 * Note that this function allocates memory.
 * An integer parameter matches the following pattern
 * [parameter_name]="[point]". If the parsing fails it returns NULL.
 * @param serdelizer     the file accessor.
 * @param parameter_name the parameter's name to parse.
 * @return the parsed point's pointer
 * @see serdelizer_t.
 * @see point_t.
 */
point_t *parse_point_parameter(serdelizer_t *serdelizer, char *parameter_name);

/**
 * Attempts to parse a points parameter.
 * Note that this function allocates memory.
 * An integer parameter matches the following pattern
 * [parameter_name]="[point], ...". If the parsing fails it returns NULL.
 * @param serdelizer     the file accessor.
 * @param parameter_name the parameter's name to parse.
 * @return the parsed point linked list's pointer
 * @see serdelizer_t.
 * @see point_node_t.
 */
point_node_t *parse_points_parameter(serdelizer_t *serdelizer,
                                     char *parameter_name);

/**
 * Displays a formatted error message of a shape's missing parameter.
 * This function displays in red the error message and the cursor's line and
 * position.
 * @param serdelizer the file accessor.
 * @param source     the source of the error message (i.e. the function's name
 * that raised the error).
 * @param parameter  the missing parameter's name.
 * @see serdelizer_t.
 */
void print_missing_parameter_error(serdelizer_t *serdelizer, char *source,
                                   char *parameter);

/**
 * Attempts to parse a viewport.
 * Note that this function allocates memory.
 * If the function fails to parse the viewport it returns NULL.
 * @param serdelizer the file accessor.
 * @return the parsed viewport's pointer.
 * @see serdelizer_t.
 * @see viewport_t.
 */
viewport_t *parse_viewport(serdelizer_t *serdelizer);

/**
 * Attempts to parse a svg.
 * Note that this function allocates memory.
 * If the function fails to parse it returns NULL.
 * @param serdelizer the file accessor.
 * @return the parsed svg's pointer.
 * @see serdelizer_t.
 * @see svg_t.
 */
svg_t *parse_svg(serdelizer_t *serdelizer);

#endif
