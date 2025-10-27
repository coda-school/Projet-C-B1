#include "rectangle.h"
#include "../styles/style.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

#define RECTANGLE_STRING_SIZE 250

shape_t *new_rectangle(int x, int y, int width, int height, style_t *styles) {
  rectangle_t *rectangle = malloc(sizeof(rectangle_t));
  rectangle->x = x;
  rectangle->y = y;
  rectangle->width = width;
  rectangle->height = height;

  shape_union_t *sh = malloc(sizeof(shape_union_t));
  sh->rectangle = rectangle;

  shape_t *shape = malloc(sizeof(shape_t));
  shape->shape_variant = RECTANGLE;
  shape->shape = sh;
  shape->styles = styles;

  return shape;
}

void free_rectangle(rectangle_t *rectangle) { free(rectangle); }

void print_rectangle(rectangle_t *rectangle) {
  printf(
      "Rectangle { X = { %d }, Y = { %d }, Width = { %d }, Height = { %d } }",
      rectangle->x, rectangle->y, rectangle->width, rectangle->height);
}

char *rectangle_to_string(rectangle_t *rectangle) {
  char *result = malloc(sizeof(char) * RECTANGLE_STRING_SIZE);
  sprintf(result, "Rectangle { X=%d, Y=%d, Width=%d, Height=%d }", rectangle->x,
          rectangle->y, rectangle->width, rectangle->height);
  return result;
}
