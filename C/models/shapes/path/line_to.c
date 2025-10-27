#include "line_to.h"
#include "../../utils/point.h"
#include "path_element.h"
#include <stdio.h>
#include <stdlib.h>

#define LINE_TO_STRING_SIZE 150
#define VERTICAL_LINE_TO_STRING_SIZE 150
#define HORIZONTAL_LINE_TO_STRING_SIZE 150

path_element_t *new_line_to(point_t *point) {
  path_element_t *line_to = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  path_element->line_to = point;
  line_to->path_element = path_element;
  line_to->path_element_variant = LINE_TO;
  return line_to;
}

void free_line_to(line_to_t *line_to) { free_point(line_to); }

void print_line_to(line_to_t *line_to) {
  printf("Line to { ");
  print_point(line_to);
  printf(" }");
}

char *line_to_to_string(line_to_t *line_to) {
  char *result = malloc(sizeof(char) * LINE_TO_STRING_SIZE);
  sprintf(result, "Line { L %d %d }", line_to->x, line_to->y);
  return result;
}

path_element_t *new_vertical_line_to(int position) {
  path_element_t *vertical_line_to = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  path_element->vertical_line_to = position;
  vertical_line_to->path_element = path_element;
  vertical_line_to->path_element_variant = VERTICAL_LINE_TO;
  return vertical_line_to;
}

void print_vertical_line_to(vertical_line_to_t vertical_line_to) {
  printf("Vertical line to { Position = { %d } }", vertical_line_to);
}

char *vertical_line_to_to_string(vertical_line_to_t vertical_line_to) {
  char *result = malloc(sizeof(char) * VERTICAL_LINE_TO_STRING_SIZE);
  sprintf(result, "Vertical line { V %d }", vertical_line_to);
  return result;
}

path_element_t *new_horizontal_line_to(int position) {
  path_element_t *horizontal_line_to = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  path_element->horizontal_line_to = position;
  horizontal_line_to->path_element = path_element;
  horizontal_line_to->path_element_variant = HORIZONTAL_LINE_TO;
  return horizontal_line_to;
}

void print_horizontal_line_to(horizontal_line_to_t horizontal_line_to) {
  printf("Horizontal line to { Position = { %d } }", horizontal_line_to);
}

char *horizontal_line_to_to_string(horizontal_line_to_t horizontal_line_to) {
  char *result = malloc(sizeof(char) * VERTICAL_LINE_TO_STRING_SIZE);
  sprintf(result, "Horizontal line { H %d }", horizontal_line_to);
  return result;
}
