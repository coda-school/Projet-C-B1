#include "parse_path.h"
#include "../../models/shapes/path/curve_to.h"
#include "../../models/shapes/path/end_path.h"
#include "../../models/shapes/path/line_to.h"
#include "../../models/shapes/path/move_to.h"
#include "parser.h"

#define ERROR_MESSAGE_BUFFER_SIZE 500

path_element_t *parse_move_to(serdelizer_t *serdelizer) {
  if (serdelizer->last_consumed != 'M' && serdelizer->last_consumed != 'm') {
    print_serdelizer_error("parse_move_to", "Invalid element to parse.",
                           serdelizer);
    return NULL;
  }

  point_t *point = parse_point(serdelizer);
  if (point == NULL) {
    print_serdelizer_error("parse_move_to", "Could not parse move to element",
                           serdelizer);
    return NULL;
  }

  return new_move_to(point);
}

path_element_t *parse_line_to(serdelizer_t *serdelizer) {
  if (serdelizer->last_consumed != 'L' && serdelizer->last_consumed != 'l') {
    print_serdelizer_error("parse_line_to", "Invalid element to parse.",
                           serdelizer);
    return NULL;
  }

  point_t *point = parse_point(serdelizer);
  if (point == NULL) {
    print_serdelizer_error("parse_line_to", "Could not parse line to element",
                           serdelizer);
    return NULL;
  }

  return new_line_to(point);
}

path_element_t *parse_horizontal_line_to(serdelizer_t *serdelizer) {
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  if (serdelizer->last_consumed != 'H' && serdelizer->last_consumed != 'h') {
    print_serdelizer_error("parse_horizontal_line_to",
                           "Invalid element to parse.", serdelizer);
    return NULL;
  }

  char c = get_next_non_whitespace_char(serdelizer);
  if (!is_char_digit(c)) {
    sprintf(buffer, "Expected integer char (0-9) got char '%c'", c);
    print_serdelizer_error("parse_horizontal_line_to", buffer, serdelizer);
    return NULL;
  }

  int_parsing_result_t integer = parse_int(serdelizer, char_to_int(c), false);
  if (!integer.success) {
    print_serdelizer_error("parse_horizontal_line_to",
                           "Could not parse horizontal line to element",
                           serdelizer);
    return NULL;
  }

  return new_horizontal_line_to(integer.value);
}

path_element_t *parse_vertical_line_to(serdelizer_t *serdelizer) {
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  if (serdelizer->last_consumed != 'V' && serdelizer->last_consumed != 'v') {
    print_serdelizer_error("parse_vertical_line_to",
                           "Invalid element to parse.", serdelizer);
    return NULL;
  }

  char c = get_next_non_whitespace_char(serdelizer);
  if (!is_char_digit(c)) {
    sprintf(buffer, "Expected integer char (0-9) got char '%c'", c);
    print_serdelizer_error("parse_vertical_line_to", buffer, serdelizer);
    return NULL;
  }

  int_parsing_result_t integer = parse_int(serdelizer, char_to_int(c), false);
  if (!integer.success) {
    print_serdelizer_error("parse_vertical_line_to",
                           "Could not parse vertical line to element",
                           serdelizer);
    return NULL;
  }

  return new_vertical_line_to(integer.value);
}

path_element_t *parse_end_of_path(serdelizer_t *serdelizer) {
  if (serdelizer->last_consumed != 'Z' && serdelizer->last_consumed != 'z') {
    print_serdelizer_error("parse_end_of_path", "Invalid element to parse.",
                           serdelizer);
    return NULL;
  }
  return new_end_path();
}

path_element_t *parse_cubic_curve_to(serdelizer_t *serdelizer) {
  if (serdelizer->last_consumed != 'C' && serdelizer->last_consumed != 'c') {
    print_serdelizer_error("parse_cubic_curve_to", "Invalid element to parse.",
                           serdelizer);
    return NULL;
  }

  point_t *control_point1 = parse_point(serdelizer);
  if (control_point1 == NULL) {
    print_serdelizer_error("parse_cubic_curve_to",
                           "Could not parse cubic curve to control point 1.",
                           serdelizer);
    return NULL;
  }

  point_t *control_point2 = parse_point(serdelizer);
  if (control_point2 == NULL) {
    print_serdelizer_error("parse_cubic_curve_to",
                           "Could not parse cubic curve to control point 2.",
                           serdelizer);
    free_point(control_point1);
    return NULL;
  }

  point_t *end_point = parse_point(serdelizer);
  if (end_point == NULL) {
    print_serdelizer_error("parse_cubic_curve_to",
                           "Could not parse cubic curve to point.", serdelizer);
    free_point(control_point1);
    free_point(control_point2);
    return NULL;
  }

  return new_cubic_curve_to(control_point1, control_point2, end_point);
}

path_element_t *parse_cubic_curve_to_shorthand(serdelizer_t *serdelizer) {
  if (serdelizer->last_consumed != 'S' && serdelizer->last_consumed != 's') {
    print_serdelizer_error("parse_cubic_curve_to_shorthand",
                           "Invalid element to parse.", serdelizer);
    return NULL;
  }

  point_t *control_point = parse_point(serdelizer);
  if (control_point == NULL) {
    print_serdelizer_error(
        "parse_cubic_curve_to_shorthand",
        "Could not parse cubic curve to shorthand control point.", serdelizer);
    return NULL;
  }

  point_t *end_point = parse_point(serdelizer);
  if (end_point == NULL) {
    print_serdelizer_error("parse_cubic_curve_to_shorthand",
                           "Could not parse cubic curve shorthand to point.",
                           serdelizer);
    free_point(control_point);
    return NULL;
  }

  return new_cubic_curve_to_shorthand(control_point, end_point);
}

path_element_t *parse_quadratic_curve_to(serdelizer_t *serdelizer) {
  if (serdelizer->last_consumed != 'Q' && serdelizer->last_consumed != 'q') {
    print_serdelizer_error("parse_quadratic_curve_to",
                           "Invalid element to parse.", serdelizer);
    return NULL;
  }

  point_t *control_point = parse_point(serdelizer);
  if (control_point == NULL) {
    print_serdelizer_error("parse_quadratic_curve_to",
                           "Could not parse quadratic curve to control point.",
                           serdelizer);
    return NULL;
  }

  point_t *end_point = parse_point(serdelizer);
  if (end_point == NULL) {
    print_serdelizer_error("parse_quadratic_curve_to",
                           "Could not parse quadratic curve to point.",
                           serdelizer);
    free_point(control_point);
    return NULL;
  }

  return new_quadratic_curve_to(control_point, end_point);
}

path_element_t *parse_quadratic_curve_to_shorthand(serdelizer_t *serdelizer) {
  if (serdelizer->last_consumed != 'T' && serdelizer->last_consumed != 't') {
    print_serdelizer_error("parse_quadratic_curve_to_shorthand",
                           "Invalid element to parse.", serdelizer);
    return NULL;
  }

  point_t *point = parse_point(serdelizer);
  if (point == NULL) {
    print_serdelizer_error("parse_quadratic_curve_to_shorthand",
                           "Could not parse quadratic curve shorhand to point.",
                           serdelizer);
    return NULL;
  }

  return new_quadratic_curve_to_shorthand(point);
}

path_element_t *parse_path_element(serdelizer_t *serdelizer) {
  path_element_t *path_element = NULL;
  switch (serdelizer->last_consumed) {
  case 'M':
  case 'm':
    path_element = parse_move_to(serdelizer);
    break;
  case 'L':
  case 'l':
    path_element = parse_line_to(serdelizer);
    break;
  case 'H':
  case 'h':
    path_element = parse_horizontal_line_to(serdelizer);
    break;
  case 'V':
  case 'v':
    path_element = parse_vertical_line_to(serdelizer);
    break;
  case 'Z':
  case 'z':
    path_element = parse_end_of_path(serdelizer);
    break;
  case 'C':
  case 'c':
    path_element = parse_cubic_curve_to(serdelizer);
    break;
  case 'S':
  case 's':
    path_element = parse_cubic_curve_to_shorthand(serdelizer);
    break;
  case 'Q':
  case 'q':
    path_element = parse_quadratic_curve_to(serdelizer);
    break;
  case 'T':
  case 't':
    path_element = parse_quadratic_curve_to_shorthand(serdelizer);
    break;
  }

  if (path_element == NULL)
    print_serdelizer_error("parse_path_element", "Could not parse path element",
                           serdelizer);
  return path_element;
}

path_element_node_t *parse_path_elements(serdelizer_t *serdelizer) {
  path_element_node_t *path_elements = NULL;
  path_element_t *element;

  if (!consume_pattern(serdelizer, "ata=\"")) {
    print_serdelizer_error("parse_path_elements",
                           "Could not parse path elements", serdelizer);
    return false;
  }

  char c = get_next_non_whitespace_char(serdelizer);
  while (c != EOF) {
    switch (c) {
    case '"':
      if (get_path_element_node_length(path_elements) == 0) {
        print_serdelizer_error(
            "parse_path_elements",
            "Could not parse path elements. Must contain at least 1 element.",
            serdelizer);
        if (path_elements != NULL)
          free_path_element_nodes(path_elements);
        return NULL;
      }
      return path_elements;
      break;
    default:
      element = parse_path_element(serdelizer);
      if (element == NULL) {
        print_serdelizer_error("parse_path_elements",
                               "Could not parse path elements", serdelizer);
        if (path_elements != NULL)
          free_path_element_nodes(path_elements);
        return NULL;
      }
      path_elements = push_path_element_node(path_elements, element);
      c = get_next_non_whitespace_char(serdelizer);
      break;
    }
  }

  print_serdelizer_error("parse_path_elements", "Reach end of file",
                         serdelizer);
  if (path_elements != NULL)
    free_path_element_nodes(path_elements);
  return NULL;
}
