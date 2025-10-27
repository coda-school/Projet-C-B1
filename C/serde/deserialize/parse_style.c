#include "parse_style.h"
#include "../../models/styles/color.h"
#include "../../models/styles/rotate.h"
#include "../../models/styles/style.h"
#include "../../models/utils/point.h"
#include "../serde.h"
#include "parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define ERROR_MESSAGE_BUFFER_SIZE 500

bool parse_outline(serdelizer_t *serdelizer, style_t *style, char *shape) {
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  color_t *previous_color = style->outline;
  color_t *color = parse_color_parameter(serdelizer, "utline");
  if (color == NULL) {
    sprintf(buffer, "Could not parse %s. Could not parse 'fill' parameter.",
            shape);
    print_serdelizer_error("parse_outline", buffer, serdelizer);
    return false;
  }
  style->outline = color;
  if (previous_color != NULL)
    free_color(previous_color);
  return true;
}

bool parse_fill(serdelizer_t *serdelizer, style_t *style, char *shape) {
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  color_t *previous_color = style->fill;
  color_t *color = parse_color_parameter(serdelizer, "ill");
  if (color == NULL) {
    sprintf(buffer, "Could not parse %s. Could not parse 'fill' parameter.",
            shape);
    print_serdelizer_error("parse_fill", buffer, serdelizer);
    return false;
  }
  style->fill = color;
  if (previous_color != NULL)
    free_color(previous_color);
  return true;
}

bool parse_translate(serdelizer_t *serdelizer, style_t *style, char *shape) {
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  point_t *point = parse_point_parameter(serdelizer, "ranslate");
  point_t *previous_translate = style->translate;
  if (point == NULL) {
    sprintf(buffer,
            "Could not parse %s. Could not parse 'translate' parameter.",
            shape);
    print_serdelizer_error("parse_translate", buffer, serdelizer);
    return false;
  }

  style->translate = point;
  if (previous_translate != NULL)
    free_point(previous_translate);
  return true;
}

bool parse_rotate(serdelizer_t *serdelizer, style_t *style, char *shape) {
  char buffer[ERROR_MESSAGE_BUFFER_SIZE];
  rotate_t *previous_rotate = style->rotate;

  if (!consume_pattern(serdelizer, "otate=\"")) {
    sprintf(buffer,
            "Could not parse shape %s. Could not parse 'rotate' parameter.",
            shape);
    print_serdelizer_error("parse_rotate", buffer, serdelizer);
    return false;
  }

  char c = get_next_non_whitespace_char(serdelizer);

  if (c == 'x' || c == 'X' || c == 'y' || c == 'Y') {
    if (get_next_non_whitespace_char(serdelizer) != '"') {
      sprintf(buffer,
              "Could not parse rorate 'X' / 'Y' variants. Expected char '\"' "
              "got char '%c'",
              serdelizer->last_consumed);
      print_serdelizer_error("parse_rotate", buffer, serdelizer);
      return false;
    }
    if (c == 'x' || c == 'X')
      style->rotate = new_flipx();
    else
      style->rotate = new_flipy();
    if (previous_rotate != NULL)
      free_rotate(previous_rotate);
    return true;
  }

  if (!is_char_digit(c)) {
    sprintf(buffer,
            "Could not parse shape %s. Could not parse 'rotate' parameter.\
      Exepected char 'x', 'X', 'y' 'Y' or digit (0-9) got char '%c'.",
            shape, c);
    print_serdelizer_error("parse_rotate", buffer, serdelizer);
    return false;
  }

  int_parsing_result_t rotate = parse_int(serdelizer, char_to_int(c), false);

  if (!rotate.success) {
    sprintf(buffer,
            "Could not parse shape %s. Could not parse 'rotate' parameter.",
            shape);
    print_serdelizer_error("parse_rotate", buffer, serdelizer);
    return false;
  }

  style->rotate = new_circular(rotate.value);
  if (previous_rotate != NULL)
    free_rotate(previous_rotate);
  return true;
}

bool parse_styles(serdelizer_t *serdelizer, style_t *style, char *shape) {
  switch (serdelizer->last_consumed) {
  case 'f':
    return parse_fill(serdelizer, style, shape);
  case 'o':
    return parse_outline(serdelizer, style, shape);
  case 't':
    return parse_translate(serdelizer, style, shape);
  case 'r':
    return parse_rotate(serdelizer, style, shape);
  default:
    return false;
  }
}
