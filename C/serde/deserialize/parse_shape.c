#include "parse_shape.h"
#include "../../models/shapes/ellipse.h"
#include "../../models/shapes/group.h"
#include "../../models/shapes/line.h"
#include "../../models/shapes/multiline.h"
#include "../../models/shapes/polygon.h"
#include "../../models/shapes/rectangle.h"
#include "../../models/shapes/shape.h"
#include "../../models/styles/style.h"
#include "../serde.h"
#include "parse_path.h"
#include "parse_style.h"
#include "parser.h"
#include <stdio.h>

#define ERROR_MESSAGE_BUFFER_SIZE 500

shape_t *parse_ellipse(serdelizer_t *serdelizer, style_t *inherited_styles) {
  if (!consume_pattern(serdelizer, "llipse")) {
    print_serdelizer_error("parse_ellipse", "Could not parse ellipse shape",
                           serdelizer);
    return NULL;
  }

  char c;
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  int x, y, height, width;
  bool is_x_set = false, is_y_set = false, is_height_set = false,
       is_width_set = false;

  style_t *style = clone_style(inherited_styles);
  int_parsing_result_t integer;

  while ((c = get_next_non_whitespace_char(serdelizer)) != EOF) {
    switch (c) {
    case 'h':
      integer = parse_int_parameter(serdelizer, "eight");
      if (!integer.success) {
        print_serdelizer_error(
            "parse_ellipse", "Could not parse 'height' parameter.", serdelizer);
        free_style(style);
        return NULL;
      }
      height = integer.value;
      is_height_set = true;
      break;

    case 'w':
      integer = parse_int_parameter(serdelizer, "idth");
      if (!integer.success) {
        print_serdelizer_error(
            "parse_ellipse", "Could not parse 'width' parameter.", serdelizer);
        free_style(style);
        return NULL;
      }
      width = integer.value;
      is_width_set = true;
      break;

    case 'x':
      integer = parse_int_parameter(serdelizer, "");
      if (!integer.success) {
        print_serdelizer_error("parse_ellipse",
                               "Could not parse 'x' parameter.", serdelizer);
        free_style(style);
        return NULL;
      }
      x = integer.value;
      is_x_set = true;
      break;

    case 'y':
      integer = parse_int_parameter(serdelizer, "");
      if (!integer.success) {
        print_serdelizer_error("parse_ellipse",
                               "Could not parse 'y' parameter.", serdelizer);
        free_style(style);
        return NULL;
      }
      y = integer.value;
      is_y_set = true;
      break;

    case '/':
      if (get_next_non_whitespace_char(serdelizer) != '>') {
        sprintf(buffer, "Expected char '>' got char '%c'",
                serdelizer->last_consumed);
        print_serdelizer_error("parse_ellipse", buffer, serdelizer);
        free_style(style);
        return NULL;
      }

      if (!is_x_set) {
        print_missing_parameter_error(serdelizer, "ellipse", "x");
        free_style(style);
        return NULL;
      }

      if (!is_y_set) {
        print_missing_parameter_error(serdelizer, "ellipse", "y");
        free_style(style);
        return NULL;
      }

      if (!is_width_set) {
        print_missing_parameter_error(serdelizer, "ellipse", "width");
        free_style(style);
        return NULL;
      }

      if (!is_height_set) {
        print_missing_parameter_error(serdelizer, "ellipse", "height");
        free_style(style);
        return NULL;
      }

      return new_ellipse(x, y, width, height, style);
      break;

    default:
      if (!parse_styles(serdelizer, style, "ellipse")) {
        free_style(style);
        return NULL;
      }
      break;
    }
  }

  return NULL;
}

shape_t *parse_rectangle(serdelizer_t *serdelizer, style_t *inherited_styles) {
  if (!consume_pattern(serdelizer, "ectangle")) {
    print_serdelizer_error("parse_rectangle", "Could not parse rectangle shape",
                           serdelizer);
    return NULL;
  }

  char c;
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  int x, y, height, width;
  bool is_x_set = false, is_y_set = false, is_height_set = false,
       is_width_set = false;

  style_t *style = clone_style(inherited_styles);
  int_parsing_result_t integer;

  while ((c = get_next_non_whitespace_char(serdelizer)) != EOF) {
    switch (c) {
    case 'h':
      integer = parse_int_parameter(serdelizer, "eight");
      if (!integer.success) {
        print_serdelizer_error("parse_rectangle",
                               "Could not parse 'height' parameter.",
                               serdelizer);
        free_style(style);
        return NULL;
      }
      height = integer.value;
      is_height_set = true;
      break;

    case 'w':
      integer = parse_int_parameter(serdelizer, "idth");
      if (!integer.success) {
        print_serdelizer_error("parse_rectangle",
                               "Could not parse 'width' parameter.",
                               serdelizer);
        free_style(style);
        return NULL;
      }
      width = integer.value;
      is_width_set = true;
      break;

    case 'x':
      integer = parse_int_parameter(serdelizer, "");
      if (!integer.success) {
        print_serdelizer_error("parse_rectangle",
                               "Could not parse 'x' parameter.", serdelizer);
        free_style(style);
        return NULL;
      }
      x = integer.value;
      is_x_set = true;
      break;

    case 'y':
      integer = parse_int_parameter(serdelizer, "");
      if (!integer.success) {
        print_serdelizer_error("parse_rectangle",
                               "Could not parse 'y' parameter.", serdelizer);
        free_style(style);
        return NULL;
      }
      y = integer.value;
      is_y_set = true;
      break;

    case '/':
      if (get_next_non_whitespace_char(serdelizer) != '>') {
        sprintf(buffer, "Expected char '>' got char '%c'",
                serdelizer->last_consumed);
        print_serdelizer_error("parse_rectangle", buffer, serdelizer);
        free_style(style);
        return NULL;
      }

      if (!is_x_set) {
        print_missing_parameter_error(serdelizer, "rectangle", "x");
        free_style(style);
        return NULL;
      }

      if (!is_y_set) {
        print_missing_parameter_error(serdelizer, "rectangle", "y");
        free_style(style);
        return NULL;
      }

      if (!is_width_set) {
        print_missing_parameter_error(serdelizer, "rectangle", "width");
        free_style(style);
        return NULL;
      }

      if (!is_height_set) {
        print_missing_parameter_error(serdelizer, "rectangle", "height");
        free_style(style);
        return NULL;
      }

      return new_rectangle(x, y, width, height, style);
      break;

    default:
      if (!parse_styles(serdelizer, style, "rectangle")) {
        free_style(style);
        return NULL;
      }
      break;
    }
  }

  return NULL;
}

shape_t *parse_line(serdelizer_t *serdelizer, style_t *inherited_styles) {
  if (!consume_pattern(serdelizer, "ine")) {
    print_serdelizer_error("parse_line", "Could not parse line shape",
                           serdelizer);
    return NULL;
  }

  char ch;
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  point_t *start = NULL, *end = NULL;
  bool is_start_set = false, is_end_set = false;

  style_t *style = clone_style(inherited_styles);
  point_t *point = NULL;

  while ((ch = get_next_non_whitespace_char(serdelizer)) != EOF) {
    switch (ch) {
    case 's':
      point = parse_point_parameter(serdelizer, "tart");
      if (point == NULL) {
        if (start != NULL)
          free_point(start);
        if (end != NULL)
          free_point(end);
        free_style(style);
        print_serdelizer_error("parse_line",
                               "Could not parse 'start' parameter", serdelizer);
        return NULL;
      }
      if (start != NULL)
        free_point(start);
      start = point;
      is_start_set = true;
      break;

    case 'e':
      point = parse_point_parameter(serdelizer, "nd");
      if (point == NULL) {
        print_serdelizer_error("parse_line", "Could not parse 'end' parameter",
                               serdelizer);
        if (start != NULL)
          free_point(start);
        if (end != NULL)
          free_point(end);
        free_style(style);
        return NULL;
      }
      if (end != NULL)
        free_point(end);
      end = point;
      is_end_set = true;
      break;

    case '/':
      if (get_next_non_whitespace_char(serdelizer) != '>') {
        sprintf(buffer, "Expected char '>' got char '%c'",
                serdelizer->last_consumed);
        print_serdelizer_error("parse_line", buffer, serdelizer);
        if (start != NULL)
          free_point(start);
        if (end != NULL)
          free_point(end);
        free_style(style);
        return NULL;
      }

      if (!is_start_set) {
        print_missing_parameter_error(serdelizer, "line", "start");
        if (start != NULL)
          free_point(start);
        if (end != NULL)
          free_point(end);
        free_style(style);
        return NULL;
      }

      if (!is_end_set) {
        print_missing_parameter_error(serdelizer, "line", "end");
        if (start != NULL)
          free_point(start);
        if (end != NULL)
          free_point(end);
        free_style(style);
        return NULL;
      }

      return new_line(start, end, style);
      break;

    default:
      if (parse_styles(serdelizer, style, "line"))
        break;
      sprintf(buffer, "Could not parse line. Got unexpected char '%c'.",
              serdelizer->last_consumed);
      print_serdelizer_error("parse_line", buffer, serdelizer);
      if (start != NULL)
        free_point(start);
      if (end != NULL)
        free_point(end);
      free_style(style);
      return NULL;
      break;
    }
  }

  if (start != NULL)
    free_point(start);
  if (end != NULL)
    free_point(end);
  free_style(style);

  return NULL;
}

shape_t *parse_multiline(serdelizer_t *serdelizer, style_t *inherited_styles) {
  if (!consume_pattern(serdelizer, "ultiline")) {
    print_serdelizer_error("parse_multiline", "Could not parse multiline shape",
                           serdelizer);
    return NULL;
  }

  char ch;
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  bool are_points_set = false;

  style_t *style = clone_style(inherited_styles);
  point_node_t *points = NULL;

  while ((ch = get_next_non_whitespace_char(serdelizer)) != EOF) {
    switch (ch) {
    case 'p':
      if (points != NULL)
        free_point_nodes(points);
      points = parse_points_parameter(serdelizer, "oints");
      if (points == NULL) {
        print_serdelizer_error("parse_multiline",
                               "Could not parse 'points' parameter",
                               serdelizer);
        free_style(style);
        return NULL;
      }
      are_points_set = true;
      break;

    case '/':
      if (get_next_non_whitespace_char(serdelizer) != '>') {
        sprintf(buffer, "Expected char '>' got char '%c'",
                serdelizer->last_consumed);
        print_serdelizer_error("parse_multiline", buffer, serdelizer);
        if (points != NULL)
          free_point_nodes(points);
        free_style(style);
        return NULL;
      }

      if (!are_points_set) {
        print_missing_parameter_error(serdelizer, "multiline", "points");
        if (points != NULL)
          free_point_nodes(points);
        free_style(style);
        return NULL;
      }

      return new_multiline(points, style);
      break;

    default:
      if (!parse_styles(serdelizer, style, "multiline")) {
        if (points != NULL)
          free_point_nodes(points);
        free_style(style);
        return NULL;
      }
      break;
    }
  }

  return NULL;
}

shape_t *parse_polygon(serdelizer_t *serdelizer, style_t *inherited_styles) {
  if (!consume_pattern(serdelizer, "olygon")) {
    print_serdelizer_error("parse_polygon", "Could not parse polygon shape",
                           serdelizer);
    return NULL;
  }

  char ch;
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  bool are_points_set = false;

  style_t *style = clone_style(inherited_styles);
  point_node_t *points = NULL;

  while ((ch = get_next_non_whitespace_char(serdelizer)) != EOF) {
    switch (ch) {
    case 'p':
      if (points != NULL)
        free_point_nodes(points);
      points = parse_points_parameter(serdelizer, "oints");
      if (points == NULL) {
        print_serdelizer_error(
            "parse_polygon", "Could not parse 'points' parameter", serdelizer);
        if (points != NULL)
          free_point_nodes(points);
        free_style(style);
        return NULL;
      }
      are_points_set = true;
      break;

    case '/':
      if (get_next_non_whitespace_char(serdelizer) != '>') {
        sprintf(buffer, "Expected char '>' got char '%c'",
                serdelizer->last_consumed);
        print_serdelizer_error("parse_polygon", buffer, serdelizer);
        if (points != NULL)
          free_point_nodes(points);
        free_style(style);
        return NULL;
      }

      if (!are_points_set) {
        print_missing_parameter_error(serdelizer, "polygon", "points");
        if (points != NULL)
          free_point_nodes(points);
        free_style(style);
        return NULL;
      }

      return new_polygon(points, style);
      break;

    default:
      if (!parse_styles(serdelizer, style, "polygon")) {
        if (points != NULL)
          free_point_nodes(points);
        free_style(style);
        return NULL;
      }
      break;
    }
  }
  if (points != NULL)
    free_point_nodes(points);
  free_style(style);
  return NULL;
}

shape_t *parse_path(serdelizer_t *serdelizer, style_t *inherited_styles) {
  if (!consume_pattern(serdelizer, "raw")) {
    print_serdelizer_error("parse_path", "Could not parse path shape",
                           serdelizer);
    return NULL;
  }

  char ch;
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  bool are_path_elements_set = false;

  style_t *style = clone_style(inherited_styles);
  path_element_node_t *path_elements = NULL;

  while ((ch = get_next_non_whitespace_char(serdelizer)) != EOF) {
    switch (ch) {
    case 'd':
      if (path_elements != NULL)
        free_path_element_nodes(path_elements);
      path_elements = parse_path_elements(serdelizer);
      if (path_elements == NULL) {
        print_serdelizer_error("parse_path", "Could not parse 'data' parameter",
                               serdelizer);
        free_style(style);
        return NULL;
      }
      are_path_elements_set = true;
      break;

    case '/':
      if (get_next_non_whitespace_char(serdelizer) != '>') {
        sprintf(buffer, "Expected char '>' got char '%c'",
                serdelizer->last_consumed);
        print_serdelizer_error("parse_path", buffer, serdelizer);
        if (path_elements != NULL)
          free_path_element_nodes(path_elements);
        free_style(style);
        return NULL;
      }

      if (!are_path_elements_set) {
        print_missing_parameter_error(serdelizer, "path", "data");
        if (path_elements != NULL)
          free_path_element_nodes(path_elements);
        free_style(style);
        return NULL;
      }

      return new_path(path_elements, style);
      break;

    default:
      if (!parse_styles(serdelizer, style, "polygon")) {
        if (path_elements != NULL)
          free_path_element_nodes(path_elements);
        free_style(style);
        return NULL;
      }
      break;
    }
  }

  if (path_elements != NULL)
    free_path_element_nodes(path_elements);
  free_style(style);
  return NULL;
}

shape_t *parse_group(serdelizer_t *serdelizer, style_t *inherited_styles) {
  if (!consume_pattern(serdelizer, "roup")) {
    print_serdelizer_error("parse_group", "Could not parse group shape",
                           serdelizer);
    return NULL;
  }

  char c;
  style_t *style = clone_style(inherited_styles);

  // Parsing styles
  while ((c = get_next_non_whitespace_char(serdelizer)) != EOF) {
    switch (c) {
    case '>':
      break;
    default:
      if (parse_styles(serdelizer, style, "polygon"))
        break;
      fprintf(stdout, "[INFO ERR] (%c)\n", serdelizer->last_consumed);
      print_serdelizer_error("parse_group", "Could not parse group header",
                             serdelizer);
      free_style(style);
      return NULL;
    }
    if (serdelizer->last_consumed == '>')
      break;
  }
  shape_t *shape = NULL;
  shape_node_t *node = NULL;

  while ((c = get_next_non_whitespace_char(serdelizer)) != EOF) {
    if (c != '<')
      continue;
    c = get_next_non_whitespace_char(serdelizer);
    if (c == '/')
      break;
    shape = parse_shape(serdelizer, style);
    if (shape != NULL)
      node = push_shape_node(node, shape);
    else {
      free_style(style);
      if (node != NULL)
        free_shape_node(node);
      print_serdelizer_error("parse_group", "Could not parse group's shapes.",
                             serdelizer);
      return NULL;
    }
  }

  if (!consume_pattern(serdelizer, "group>")) {
    free_style(style);
    if (node != NULL)
      free_shape_node(node);
    print_serdelizer_error("parse_group", "Could not parse group.", serdelizer);
    return NULL;
  }

  return new_group(node, style);
}

shape_t *parse_shape(serdelizer_t *serdelizer, style_t *inherited_styles) {
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  switch (serdelizer->last_consumed) {
  case 'e':
    return parse_ellipse(serdelizer, inherited_styles);
    break;
  case 'r':
    return parse_rectangle(serdelizer, inherited_styles);
    break;
  case 'l':
    return parse_line(serdelizer, inherited_styles);
    break;
  case 'm':
    return parse_multiline(serdelizer, inherited_styles);
    break;
  case 'p':
    return parse_polygon(serdelizer, inherited_styles);
    break;
  case 'd':
    return parse_path(serdelizer, inherited_styles);
    break;
  case 'g':
    return parse_group(serdelizer, inherited_styles);
    break;
  default:
    sprintf(buffer, "Char '%c' : Not implemented yet",
            serdelizer->last_consumed);
    print_serdelizer_error("parse_shape", buffer, serdelizer);
    return NULL;
    break;
  }
}
