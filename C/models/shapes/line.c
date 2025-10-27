#include "line.h"
#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

#define LINE_STRING_SIZE 150

shape_t *new_line(point_t *start, point_t *end, style_t *styles) {
  line_t *line = malloc(sizeof(line_t));
  line->start = start;
  line->end = end;

  shape_union_t *sh = malloc(sizeof(shape_union_t));
  sh->line = line;

  shape_t *shape = malloc(sizeof(shape_t));
  shape->shape = sh;
  shape->shape_variant = LINE;
  shape->styles = styles;

  return shape;
}

void print_line(line_t *line) {
  printf("Line = { Start = { ");
  print_point(line->start);
  printf(" }, End = { ");
  print_point(line->end);
  printf(" } }");
}

void free_line(line_t *line) {
  free_point(line->start);
  free_point(line->end);
  free(line);
}

char *line_to_string(line_t *line) {
  char *result = malloc(sizeof(char) * LINE_STRING_SIZE);
  sprintf(result, "Line { X1=%d, Y1=%d, X2=%d, Y2=%d }", line->start->x,
          line->start->y, line->end->x, line->end->y);
  return result;
}
