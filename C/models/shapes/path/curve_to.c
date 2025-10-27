#include "curve_to.h"
#include "../../utils/point.h"
#include "path_element.h"
#include <stdio.h>
#include <stdlib.h>

#define CUBIC_CURVE_TO_STRING_SIZE 250
#define CUBIC_CURVE_TO_SHORTHAND_STRING_SIZE 250
#define QUADRATIC_CURVE_TO_STRING_SIZE 250
#define QUADRATIC_CURVE_TO_SHORTHAND_STRING_SIZE 250

path_element_t *new_cubic_curve_to(point_t *control_point_1,
                                   point_t *control_point_2, point_t *end) {
  path_element_t *cubic_curve_to = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  cubic_curve_to_t *cct = malloc(sizeof(cubic_curve_to_t));
  cct->control_point_1 = control_point_1;
  cct->control_point_2 = control_point_2;
  cct->end = end;
  path_element->cubic_curve_to = cct;
  cubic_curve_to->path_element = path_element;
  cubic_curve_to->path_element_variant = CUBIC_CURVE_TO;
  return cubic_curve_to;
}

void free_cubic_curve_to(cubic_curve_to_t *cubic_curve_to) {
  free_point(cubic_curve_to->control_point_1);
  free_point(cubic_curve_to->control_point_2);
  free_point(cubic_curve_to->end);
  free(cubic_curve_to);
}

void print_cubic_curve_to(cubic_curve_to_t *cubic_curve_to) {
  printf("Cubic curve to { Control point 1 = { ");
  print_point(cubic_curve_to->control_point_1);
  printf(" }, Control point 2 = { ");
  print_point(cubic_curve_to->control_point_2);
  printf(" }, End = { ");
  print_point(cubic_curve_to->end);
  printf(" }");
}

char *cubic_curve_to_string(cubic_curve_to_t *cubic_curve_to) {
  char *result = malloc(sizeof(char) * CUBIC_CURVE_TO_STRING_SIZE);
  sprintf(
      result, "Cubic curve { C %d %d %d %d %d %d }",
      cubic_curve_to->control_point_1->x, cubic_curve_to->control_point_1->y,
      cubic_curve_to->control_point_2->x, cubic_curve_to->control_point_2->y,
      cubic_curve_to->end->x, cubic_curve_to->end->y);
  return result;
}

path_element_t *new_cubic_curve_to_shorthand(point_t *control_point,
                                             point_t *end) {
  path_element_t *cubic_curve_to_shorthand = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  shorthand_cubic_curve_to_t *scct = malloc(sizeof(shorthand_cubic_curve_to_t));
  scct->control_point = control_point;
  scct->end = end;
  path_element->shorthand_cubic_curve_to = scct;
  cubic_curve_to_shorthand->path_element = path_element;
  cubic_curve_to_shorthand->path_element_variant = CUBIC_CURVE_TO_SHORTHAND;
  return cubic_curve_to_shorthand;
}

void free_shorthand_cubic_curve_to(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to) {
  free_point(shorthand_cubic_curve_to->control_point);
  free_point(shorthand_cubic_curve_to->end);
  free(shorthand_cubic_curve_to);
}

void print_shorthand_cubic_curve_to(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to) {
  printf("Cubic curve to shorthand { Control point = { ");
  print_point(shorthand_cubic_curve_to->control_point);
  printf(" }, End = { ");
  print_point(shorthand_cubic_curve_to->end);
  printf(" }");
}

char *cubic_curve_to_shorthand_to_sting(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to) {
  char *result = malloc(sizeof(char) * CUBIC_CURVE_TO_SHORTHAND_STRING_SIZE);
  sprintf(result, "Cubic curve shorthand { S %d %d %d %d }",
          shorthand_cubic_curve_to->control_point->x,
          shorthand_cubic_curve_to->control_point->y,
          shorthand_cubic_curve_to->end->x, shorthand_cubic_curve_to->end->y);
  return result;
}

path_element_t *new_quadratic_curve_to(point_t *control_point, point_t *end) {
  path_element_t *quadratic_curve_to = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  quadratic_curve_to_t *qct = malloc(sizeof(quadratic_curve_to_t));
  qct->control_point = control_point;
  qct->end = end;
  path_element->quadratic_curve_to = qct;
  quadratic_curve_to->path_element = path_element;
  quadratic_curve_to->path_element_variant = QUADRATIC_CURVE_TO;
  return quadratic_curve_to;
}

void free_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to) {
  free_point(quadratic_curve_to->control_point);
  free_point(quadratic_curve_to->end);
  free(quadratic_curve_to);
}

void print_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to) {
  printf("Quadratic curve to { Control point = { ");
  print_point(quadratic_curve_to->control_point);
  printf(" }, End = { ");
  print_point(quadratic_curve_to->end);
  printf(" }");
}

char *quadratic_curve_to_to_string(quadratic_curve_to_t *quadratic_curve_to) {
  char *result = malloc(sizeof(char) * QUADRATIC_CURVE_TO_STRING_SIZE);
  sprintf(result, "Quadratic curve { Q %d %d %d %d }",
          quadratic_curve_to->control_point->x,
          quadratic_curve_to->control_point->y, quadratic_curve_to->end->x,
          quadratic_curve_to->end->y);
  return result;
}

path_element_t *new_quadratic_curve_to_shorthand(point_t *end) {
  path_element_t *shorthand_quadratic_curve_to = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  path_element->shorthand_quadratic_curve_to = end;
  shorthand_quadratic_curve_to->path_element = path_element;
  shorthand_quadratic_curve_to->path_element_variant =
      QUADRATIC_CURVE_TO_SHORTHAND;
  return shorthand_quadratic_curve_to;
}

void free_shorthand_quadratic_curve_to(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to) {
  free_point(shorthand_quadratic_curve_to);
}

void print_shorthand_quadratic_curve_to(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to) {
  printf("Quadratic curve to shorthand { ");
  print_point(shorthand_quadratic_curve_to);
  printf(" }");
}

char *quadratic_curve_to_shorthand_to_string(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to) {
  char *result =
      malloc(sizeof(char) * QUADRATIC_CURVE_TO_SHORTHAND_STRING_SIZE);
  sprintf(result, "Quadratic curve shorthand { T %d %d }",
          shorthand_quadratic_curve_to->x, shorthand_quadratic_curve_to->y);
  return result;
}
