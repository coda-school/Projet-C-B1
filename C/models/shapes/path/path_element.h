#ifndef CODA_PATH_ELEMENT
#define CODA_PATH_ELEMENT

#include "../../utils/point.h"

/**
 * Overrides the point_t type to define the move to path element type.
 */
typedef point_t move_to_t;

/**
 * Overrides the point_t type to define the line to path element type.
 */
typedef point_t line_to_t;

/**
 * Overrides the int type to define the vertical line to path element type.
 */
typedef int vertical_line_to_t;

/**
 * Overrides the int type to define the horizontal line to path element type.
 */
typedef int horizontal_line_to_t;

/**
 * Defines the end of path type.
 * Represents the SVG path element code Z.
 */
typedef struct end_path_s end_path_t;

/**
 * Predefines the cubic Bezier curve to path element type.
 */
typedef struct cubic_curve_to_s cubic_curve_to_t;

/**
 * Predefines the cubic Bezier curve to shorthand path element type.
 */
typedef struct shorthand_cubic_curve_to_s shorthand_cubic_curve_to_t;

/**
 * Predefines the quadratic Bezier curve to path element type.
 */
typedef struct quadratic_curve_to_s quadratic_curve_to_t;

/**
 * Predefines the quadratic Bezier curve to shorthand path element type.
 */
typedef point_t shorthand_quadratic_curve_to_t;

/**
 * Groups all path elements variants.
 * @see move_to_t
 * @see line_to_t
 * @see vertical_line_to_t
 * @see horizontal_line_to_t
 * @see end_path_t
 * @see cubic_curve_to_t
 * @see shorthand_cubic_curve_to_t
 * @see quadratic_curve_to_t
 * @see shorthand_quadratic_curve_to_t
 */
typedef union path_element_union_u {
  move_to_t *move_to;
  line_to_t *line_to;
  vertical_line_to_t vertical_line_to;
  horizontal_line_to_t horizontal_line_to;
  end_path_t *end_path;
  cubic_curve_to_t *cubic_curve_to;
  shorthand_cubic_curve_to_t *shorthand_cubic_curve_to;
  quadratic_curve_to_t *quadratic_curve_to;
  shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to;
} path_element_union_t;

/**
 * Lists all the path element variants.
 */
typedef enum path_element_variant_e {
  MOVE_TO,
  LINE_TO,
  VERTICAL_LINE_TO,
  HORIZONTAL_LINE_TO,
  END_PATH,
  CUBIC_CURVE_TO,
  CUBIC_CURVE_TO_SHORTHAND,
  QUADRATIC_CURVE_TO,
  QUADRATIC_CURVE_TO_SHORTHAND,
} path_element_variant_t;

/**
 * Defines the path element type.
 * @param path_element holds the active path element variant.
 * @param path_element_variant indicates the active path element variant.
 * @see path_element_union_t.
 * @see path_element_variant_t.
 */
typedef struct path_element_s {
  path_element_union_t *path_element;
  path_element_variant_t path_element_variant;
} path_element_t;

#endif
