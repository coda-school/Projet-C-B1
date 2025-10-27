#include "parser.h"
#include "parse_shape.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MESSAGE_SIZE 500

bool consume_next_char(serdelizer_t *serdelizer, char c) {
  char ch = get_next_non_whitespace_char(serdelizer);
  if (ch != c) {
    char buffer[ERROR_MESSAGE_SIZE];
    sprintf(buffer, "Expected char '%c' got char '%c'", c, ch);
    print_serdelizer_error("consume_next_char", buffer, serdelizer);
  }
  return ch == c;
}

bool consume_pattern(serdelizer_t *serdelizer, char *pattern) {
  int length = strlen(pattern);
  char buffer[ERROR_MESSAGE_SIZE];
  for (int i = 0; i < length; i++) {
    if (!consume_next_char(serdelizer, pattern[i])) {
      sprintf(buffer, "Could not consume char '%c'", pattern[i]);
      print_serdelizer_error("consume_pattern", buffer, serdelizer);
      return false;
    }
  }
  return true;
}

bool is_char_digit(char c) { return (bool)(48 <= c && c <= 57); }

bool is_char_hexa(char c) {
  return (bool)((48 <= c && c <= 57) || (65 <= c && c <= 70) ||
                (97 <= c && c <= 102));
}

int char_to_int(char c) {
  if (!is_char_digit(c)) {
    fprintf(stderr,
            "[ERROR] (char_to_int) > Expected int char (0-9) got char '%c'", c);
    exit(EXIT_FAILURE);
  }
  return ((int)c) - 48;
}

int hexa_to_int(char c) {
  if (!is_char_hexa(c)) {
    fprintf(
        stderr,
        "[ERROR] (hexa_to_int) > Expected hexa char (0-9 A-F) got char '%c'",
        c);
    exit(EXIT_FAILURE);
  }
  switch (c) {
  case '0':
    return 0;
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
  case 'a':
  case 'A':
    return 10;
  case 'b':
  case 'B':
    return 11;
  case 'c':
  case 'C':
    return 12;
  case 'd':
  case 'D':
    return 13;
  case 'e':
  case 'E':
    return 14;
  default:
    return 15;
  }
}

int_parsing_result_t parse_int(serdelizer_t *serdelizer, int base,
                               bool must_consume) {
  char c = get_next_char(serdelizer);
  bool is_negative = base < 0;

  if (c == '-' && base != 0)
    return (int_parsing_result_t){.value = 0, .success = false};

  if (c == '-') {
    is_negative = true;
    c = get_next_char(serdelizer);
  }

  if (!is_char_digit(c) && !must_consume)
    return (int_parsing_result_t){.value = base, .success = true};

  if (!is_char_digit(c)) {
    char buffer[ERROR_MESSAGE_SIZE];
    sprintf(buffer, "Expected digit char (0-9) got char '%c'", c);
    print_serdelizer_error("parse_int", buffer, serdelizer);
    return (int_parsing_result_t){.value = 0, .success = false};
  }

  int result = base;
  int temp;
  while (is_char_digit(c)) {
    temp = result;
    result *= 10;
    result += char_to_int(c);
    if ((is_negative && temp < result) || (!is_negative && temp > result)) {
      print_serdelizer_error(
          "parse_int",
          "[ERROR] (parse_int) > Int overflow occured while parsing integer.",
          serdelizer);
      return (int_parsing_result_t){.value = 0, .success = false};
    }
    c = get_next_char(serdelizer);
  }

  if (is_negative)
    return (int_parsing_result_t){.value = -result, .success = true};
  return (int_parsing_result_t){.value = result, .success = true};
}

uchar_parsing_result_t parse_hexa_byte(serdelizer_t *serdelizer) {
  unsigned char result = 0;
  char buffer[ERROR_MESSAGE_SIZE];

  char c = get_next_non_whitespace_char(serdelizer);
  if (!is_char_hexa(c)) {
    sprintf(buffer, "Exepcted hexa char (0-9 A-F) got char '%c'", c);
    print_serdelizer_error("parse_hexa_byte", buffer, serdelizer);
    return (uchar_parsing_result_t){.value = 0, .success = false};
  }
  result += hexa_to_int(c) * 16;

  c = get_next_non_whitespace_char(serdelizer);
  if (!is_char_hexa(c)) {
    sprintf(buffer, "Exepcted hexa char (0-9 A-F) got char '%c'", c);
    print_serdelizer_error("parse_hexa_byte", buffer, serdelizer);
    return (uchar_parsing_result_t){.value = 0, .success = false};
  }
  result += hexa_to_int(c);

  return (uchar_parsing_result_t){.value = result, .success = true};
}

point_t *parse_point(serdelizer_t *serdelizer) {
  int_parsing_result_t x, y;
  char buffer[ERROR_MESSAGE_SIZE];
  bool is_negative = false;
  char c = get_next_non_whitespace_char(serdelizer);

  if (c == '-') {
    is_negative = true;
    c = get_next_non_whitespace_char(serdelizer);
  }

  if (!is_char_digit(c)) {
    sprintf(buffer, "Expected digit char (0-9) got char '%c'", c);
    print_serdelizer_error("parse_point", buffer, serdelizer);
    return NULL;
  }

  int base = char_to_int(c);
  if (is_negative)
    base *= -1;

  x = parse_int(serdelizer, base, false);
  if (!x.success) {
    print_serdelizer_error("parse_point", "Could not parse point", serdelizer);
    return NULL;
  }
  is_negative = false;

  if (!is_whitespace(serdelizer->last_consumed)) {
    sprintf(buffer, "Expected whitespace char got char '%c'", c);
    print_serdelizer_error("parse_point", buffer, serdelizer);
    return NULL;
  }

  c = get_next_non_whitespace_char(serdelizer);
  if (c == '-') {
    is_negative = true;
    c = get_next_non_whitespace_char(serdelizer);
  }

  if (!is_char_digit(c)) {
    sprintf(buffer, "Expected digit char (0-9) got char '%c'", c);
    print_serdelizer_error("parse_point", buffer, serdelizer);
    return NULL;
  }

  base = char_to_int(c);
  if (is_negative)
    base *= -1;

  y = parse_int(serdelizer, base, false);

  if (!y.success) {
    print_serdelizer_error("parse_point", "Could not parse point", serdelizer);
    return NULL;
  }

  return new_point(x.value, y.value);
}

color_t *parse_color(serdelizer_t *serdelizer) {
  uchar_parsing_result_t red, green, blue, transparent;
  char buffer[ERROR_MESSAGE_SIZE];
  char c = get_next_non_whitespace_char(serdelizer);

  if (c != '#') {
    sprintf(buffer, "Expected char '#' got char '%c'", c);
    print_serdelizer_error("parse_color", buffer, serdelizer);
    return NULL;
  }

  red = parse_hexa_byte(serdelizer);

  if (!red.success) {
    print_serdelizer_error("parse_color",
                           "Could not parse hexa byte for red parameter.",
                           serdelizer);
    return NULL;
  }

  green = parse_hexa_byte(serdelizer);
  if (!green.success) {
    print_serdelizer_error("parse_color",
                           "Could not parse hexa byte for green parameter.",
                           serdelizer);
    return NULL;
  }

  blue = parse_hexa_byte(serdelizer);
  if (!blue.success) {
    print_serdelizer_error("parse_color",
                           "Could not parse hexa byte for blue parameter.",
                           serdelizer);
    return NULL;
  }

  transparent = parse_hexa_byte(serdelizer);
  if (!transparent.success) {
    print_serdelizer_error(
        "parse_color", "Could not parse hexa byte for transparency parameter.",
        serdelizer);
    return NULL;
  }

  return new_color(red.value, green.value, blue.value, transparent.value);
}

int_parsing_result_t parse_int_parameter(serdelizer_t *serdelizer,
                                         char *parameter_name) {
  char buffer[ERROR_MESSAGE_SIZE];

  if (strlen(parameter_name) != 0 &&
      !consume_pattern(serdelizer, parameter_name)) {
    print_serdelizer_error("parse_int_parameter",
                           "Could not parse int parameter.", serdelizer);
    return (int_parsing_result_t){.value = 0, .success = false};
  }

  if (!consume_pattern(serdelizer, "=\"")) {
    print_serdelizer_error("parse_int_parameter",
                           "Could not parse int parameter.", serdelizer);
    return (int_parsing_result_t){.value = 0, .success = false};
  }

  int_parsing_result_t value = parse_int(serdelizer, 0, true);

  if (!value.success) {
    print_serdelizer_error("parse_int_parameter",
                           "Could not parse int parameter.", serdelizer);
    return (int_parsing_result_t){.value = 0, .success = false};
  }

  if (serdelizer->last_consumed == '"')
    return value;

  if (!is_whitespace(serdelizer->last_consumed)) {
    sprintf(
        buffer,
        "Exepected char '\"' or whitespace (' ', '\\r', '\\t', '\\n') got '%c'",
        serdelizer->last_consumed);
    print_serdelizer_error("parse_int_parameter", buffer, serdelizer);
    return (int_parsing_result_t){.value = 0, .success = false};
  }

  char c = get_next_non_whitespace_char(serdelizer);
  if (c == '"')
    return value;

  sprintf(buffer, "Expected char '\"' got char '%c'", c);
  print_serdelizer_error("parse_int_parameter", buffer, serdelizer);
  return (int_parsing_result_t){.value = 0, .success = false};
}

color_t *parse_color_parameter(serdelizer_t *serdelizer, char *parameter_name) {
  char buffer[ERROR_MESSAGE_SIZE];

  if (strlen(parameter_name) != 0 &&
      !consume_pattern(serdelizer, parameter_name)) {
    print_serdelizer_error("parse_int_parameter",
                           "Could not parse int parameter.", serdelizer);
    return NULL;
  }

  if (!consume_pattern(serdelizer, "=\"")) {
    print_serdelizer_error("parse_color_parameter",
                           "Could not parse color parameter.", serdelizer);
    return NULL;
  }

  color_t *value = parse_color(serdelizer);

  if (value == NULL) {
    print_serdelizer_error("parse_color_parameter",
                           "Could not parse color parameter.", serdelizer);
    return NULL;
  }

  char c = get_next_non_whitespace_char(serdelizer);

  if (c == '"')
    return value;

  sprintf(buffer, "Exepected char '\"' got '%c'", serdelizer->last_consumed);
  print_serdelizer_error("parse_color_parameter", buffer, serdelizer);
  return NULL;
}

point_t *parse_point_parameter(serdelizer_t *serdelizer, char *parameter_name) {
  char buffer[ERROR_MESSAGE_SIZE];

  if (strlen(parameter_name) != 0 &&
      !consume_pattern(serdelizer, parameter_name)) {
    print_serdelizer_error("parse_int_parameter",
                           "Could not parse int parameter.", serdelizer);
    return NULL;
  }

  if (!consume_pattern(serdelizer, "=\"")) {
    print_serdelizer_error("parse_point_parameter",
                           "Could not parse point parameter.", serdelizer);
    return NULL;
  }

  point_t *value = parse_point(serdelizer);

  if (value == NULL) {
    print_serdelizer_error("parse_point_parameter",
                           "Could not parse point parameter.", serdelizer);
    return NULL;
  }

  if (serdelizer->last_consumed == '"')
    return value;

  if (!is_whitespace(serdelizer->last_consumed)) {
    sprintf(
        buffer,
        "Exepected char '\"' or whitespace (' ', '\\r', '\\t', '\\n') got '%c'",
        serdelizer->last_consumed);
    print_serdelizer_error("parse_point_parameter", buffer, serdelizer);
    return NULL;
  }

  char c = get_next_non_whitespace_char(serdelizer);
  if (c == '"')
    return value;

  sprintf(buffer, "Expected char '\"' got char '%c'", c);
  print_serdelizer_error("parse_point_parameter", buffer, serdelizer);
  return NULL;
}

point_node_t *parse_points_parameter(serdelizer_t *serdelizer,
                                     char *parameter_name) {
  if (strlen(parameter_name) != 0 &&
      !consume_pattern(serdelizer, parameter_name)) {
    print_serdelizer_error("parse_points_parameter",
                           "Could not parse points parameter.", serdelizer);
    return NULL;
  }

  if (!consume_pattern(serdelizer, "=\"")) {
    print_serdelizer_error("parse_points_parameter",
                           "Could not parse points parameter.", serdelizer);
    return NULL;
  }

  char c;
  point_node_t *points = NULL;
  int a = 0, b = 0;
  bool is_a_set = false, writing_a = false, writing_b = false;

  while ((c = get_next_char(serdelizer)) != EOF) {
    if (is_char_digit(c)) {
      if (is_a_set) {
        writing_b = true;
        b = b * 10 + char_to_int(c);
      } else {
        writing_a = true;
        a = a * 10 + char_to_int(c);
      }
      continue;
    }

    if (is_whitespace(c)) {
      if (!is_a_set && !writing_a)
        continue;
      if (!is_a_set) {
        writing_a = false;
        is_a_set = true;
      }
      if (is_a_set && !writing_b)
        continue;
      if (is_a_set) {
        points = push_point_node(points, new_point(a, b));
        writing_b = false;
        is_a_set = false;
        writing_a = false;
        a = 0;
        b = 0;
      }
    }

    if (c == '"')
      break;
  }

  if (is_a_set && writing_b) {
    points = push_point_node(points, new_point(a, b));
    writing_b = false;
    is_a_set = false;
    writing_a = false;
  }

  if ((writing_a || is_a_set) && !writing_b) {
    print_serdelizer_error("parse_points_parameter", "Missing integer value.",
                           serdelizer);
    free_point_nodes(points);
    return NULL;
  }

  return points;
}

void print_missing_parameter_error(serdelizer_t *serdelizer, char *source,
                                   char *parameter) {
  char buffer[ERROR_MESSAGE_SIZE];
  sprintf(buffer, "Missing parameter '%s'.", parameter);
  print_serdelizer_error(source, buffer, serdelizer);
}

viewport_t *parse_viewport(serdelizer_t *serdelizer) {
  char buffer[ERROR_MESSAGE_SIZE];
  if (get_next_non_whitespace_char(serdelizer) != 'v' ||
      !consume_pattern(serdelizer, "iewport=\"")) {
    print_serdelizer_error("parse_viewport", "Could not parse viewport",
                           serdelizer);
    return NULL;
  }

  point_t *start = parse_point(serdelizer);
  if (start == NULL) {
    print_serdelizer_error("parse_viewport",
                           "Could not parse viewport start point", serdelizer);
    return NULL;
  }

  point_t *end = parse_point(serdelizer);
  if (end == NULL) {
    free_point(start);
    print_serdelizer_error("parse_viewport",
                           "Could not parse viewport end point", serdelizer);
    return NULL;
  }

  if (serdelizer->last_consumed == '"')
    return new_viewport(start, end);
  if (get_next_non_whitespace_char(serdelizer) != '"') {
    free_point(start);
    free_point(end);
    sprintf(buffer, "Expected char '\"' got char '%c'",
            serdelizer->last_consumed);
    print_serdelizer_error("parse_viewport", buffer, serdelizer);
    return NULL;
  }

  return new_viewport(start, end);
}

svg_t *parse_svg(serdelizer_t *serdelizer) {
  char buffer[ERROR_MESSAGE_SIZE];
  if (!consume_pattern(serdelizer, "<svg")) {
    print_serdelizer_error("parse_svg", "Could not parse svg", serdelizer);
    return NULL;
  }

  viewport_t *viewport = parse_viewport(serdelizer);
  if (viewport == NULL) {
    print_serdelizer_error("parse_svg", "Could not parse svg's viewport",
                           serdelizer);
    return NULL;
  }

  if (get_next_non_whitespace_char(serdelizer) != '>') {
    sprintf(buffer, "Expected char '>' got char '%c'",
            serdelizer->last_consumed);
    print_serdelizer_error("parse_svg", buffer, serdelizer);
    free_viewport(viewport);
    return NULL;
  }

  shape_node_t *shapes = NULL;
  shape_t *shape = NULL;
  style_t *styles = new_default_style();
  while (get_next_non_whitespace_char(serdelizer) != EOF) {
    if (serdelizer->last_consumed != '<')
      break;
    if (get_next_non_whitespace_char(serdelizer) == '/')
      break;
    shape = parse_shape(serdelizer, styles);
    if (shape != NULL)
      shapes = push_shape_node(shapes, shape);
    else {
      free_viewport(viewport);
      free_style(styles);
      print_serdelizer_error("parse_svg", "Could not parse svg's shapes",
                             serdelizer);
      return NULL;
    }
  }

  if (!consume_pattern(serdelizer, "svg>")) {
    free_viewport(viewport);
    free_style(styles);
    free_shape_node(shapes);
    print_serdelizer_error("parse_svg", "Could not parse svg", serdelizer);
    return NULL;
  }

  free_style(styles);
  return new_svg(viewport, shapes);
}
