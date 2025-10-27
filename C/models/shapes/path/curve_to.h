#ifndef CODA_CURVE_TO
#define CODA_CURVE_TO

#include "../../utils/point.h"
#include "path_element.h"

/**
 * Represents a cubic Bezier curve to path element.
 * Represents the SVG path element code C <int> <int> <int> <int> <int> <int>.
 * @param control_point_1 the curve's first control point.
 * @param control_point_2 the curve's second control point.
 * @param end             the curve's end point.
 * @see point_t.
 */
struct cubic_curve_to_s {
  point_t *control_point_1;
  point_t *control_point_2;
  point_t *end;
};

/**
 * Destroys the given cubic curve.
 * Note that this function frees memory.
 * @param the cubic cruve to be destroyed.
 * @see cubic_curve_to_s.
 */
void free_cubic_curve_to(cubic_curve_to_t *cubic_curve_to);

/**
 * Prints out the given cubic curve.
 * Note that this function is for debug purposes only.
 * @param cubic_curve_to the cubic curve to be printed out.
 * @see cubic_curve_to_s.
 */
void print_cubic_curve_to(cubic_curve_to_t *cubic_curve_to);

/**
 * Creates a new cubic curve.
 * Note that this function allocates memory.
 * This function wraps the cubic curve in the path element structure.
 * @param control_point_1 the curve's first control point.
 * @param control_point_2 the curve's second control point.
 * @param end             the curve's end point.
 * @return the new cubic curve's pointer.
 * @see point_t.
 * @see cubic_curve_to_s.
 * @see path_element_t.
 */
path_element_t *new_cubic_curve_to(point_t *control_point_1,
                                   point_t *control_point_2, point_t *end);

/**
 * Converts the given cubic curve to a string.
 * Note that this function allocates memory.
 * @param cubic_curve_to the cubic curve to be converted.
 * @return a string.
 * @see cubic_curve_to_s.
 */
char *cubic_curve_to_string(cubic_curve_to_t *cubic_curve_to);

/**
 * Represents a cubic Bezier curve to shorthand.
 * Represents the SVG path element code S <int> <int> <int> <int>.
 * @param control_point the cubic curve shorthand's control point.
 * @param end           the cubic curve shorthand's end point.
 * @see point_t.
 */
struct shorthand_cubic_curve_to_s {
  point_t *control_point;
  point_t *end;
};

/**
 * Destroys the given shorthand cubic curve to shorthand.
 * Note that this function frees memory.
 * @param shorthand_cubic_curve_to the cubic curve shorthand to be destroyed.
 * @see shorthand_cubic_curve_to_s.
 */
void free_shorthand_cubic_curve_to(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to);

/**
 * Prints out the given cubic curve shorthand.
 * Note that this function is for debug purposes only.
 * @param shorthand_cubic_curve_to the cubic curve shorthand to be printed out.
 * @see shorthand_cubic_curve_to.
 */
void print_shorthand_cubic_curve_to(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to);

/**
 * Creates a new cubic curve shorthand.
 * Note that this function allocates memory.
 * This function wraps the cubic curve shorthand in the path element structure.
 * @param control_point the cubic curve shorthand's control point.
 * @param end           the cubic curve shorthand's end point.
 * @return the new cubic curve shorthand's pointer.
 * @see point_t.
 * @see shorthand_cubic_curve_to_s.
 * @see path_element_t.
 */
path_element_t *new_cubic_curve_to_shorthand(point_t *control_point,
                                             point_t *end);

/**
 * Converts the given cubic curve shorthand to a string.
 * Note that this function allocates memory.
 * @param shorthand_cubic_curve_to the cubic curve shorthand to be converted.
 * @return a string.
 * @see shorthand_cubic_curve_to_s.
 */
char *cubic_curve_to_shorthand_to_sting(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to);

/**
 * Represents a quadratic Bezier curve.
 * Represents the SVG path element code Q <int> <int> <int> <int>.
 * @param control_point the quadratic curve's control point.
 * @param end           the quadratic curve's end point.
 * @see point_t.
 */
struct quadratic_curve_to_s {
  point_t *control_point;
  point_t *end;
};

/**
 * Destroys the given quadratic curve.
 * Note that this function frees memory.
 * @param quadratic_curve_to the quadratic curve to be destroyed.
 * @see quadratic_curve_to_s.
 */
void free_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to);

/**
 * Prints out the given quadratic curve.
 * Note that this function is for debug purposes only.
 * @param quadratic_curve_to the quadratic curve to be printed out.
 * @see quadratic_curve_to_s.
 */
void print_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to);

/**
 * Creates a new quadratic curve.
 * Note that this function allocates memory.
 * This function wraps the quadratic curve in the path element structure.
 * @param control_point the quadratic curve's control point.
 * @param end           the quadratic curve's end point.
 * @return the new quadratic curve's pointer.
 * @see point_t.
 * @see quadratic_curve_to_s.
 * @see path_element_t.
 */
path_element_t *new_quadratic_curve_to(point_t *control_point, point_t *end);

/**
 * Converts the given quadratic curve to a string.
 * Note that this function allocates memory.
 * @param quadratic_curve_to the quadratic curve to be converted.
 * @return a string.
 * @see quadratic_curve_to_s.
 */
char *quadratic_curve_to_to_string(quadratic_curve_to_t *quadratic_curve_to);

/**
 * Destroys the given quadratic curve shorthand.
 * Note that this function frees memory.
 * @param shorthand_quadratic_curve_to the quadratic curve shorthand to be
 * destroyed.
 * @see shorthand_quadratic_curve_to_t.
 */
void free_shorthand_quadratic_curve_to(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to);

/**
 * Prints out the given quadratic curve shorthand.
 * Note that this function is for debug purposes only.
 * @param shorthand_quadratic_curve_to the quadratic curve shorthand to be
 * printed out.
 * @see quadratic_curve_to_s.
 */
void print_shorthand_quadratic_curve_to(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to);

/**
 * Creates a new quadratic curve shorthand.
 * Note that this function allocates memory.
 * This function wraps the quadratic curve shorthand in the path element
 * structure.
 * @param end the quadratic curve shorthand's end point.
 * @return the new quadratic curve shorthand's pointer.
 * @see point_t.
 * @see shorthand_quadratic_curve_to_t.
 * @see path_element_t.
 */
path_element_t *new_quadratic_curve_to_shorthand(point_t *end);

/**
 * Converts the given quadratic curve shorthand to a string.
 * Note that this function allocates memory.
 * @param shorthand_quadratic_curve_to the quadratic curve shorthand to be
 * converted.
 * @return a string.
 * @see shorthand_quadratic_curve_to_t.
 * @see path_element_t.
 */
char *quadratic_curve_to_shorthand_to_string(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to);

#endif
