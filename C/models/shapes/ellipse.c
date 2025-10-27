#include "ellipse.h"
#include "../styles/style.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

#define ELLIPSE_TO_STRING_SIZE 250

shape_t *new_ellipse(int center_x, int center_y, int radius_x, int radius_y,
                     style_t *styles) {
  ellipse_t *ellipse = malloc(sizeof(ellipse_t));
  ellipse->center_x = center_x;
  ellipse->center_y = center_y;
  ellipse->radius_x = radius_x;
  ellipse->radius_y = radius_y;

  shape_union_t *sh = malloc(sizeof(shape_union_t));
  sh->ellipse = ellipse;

  shape_t *shape = malloc(sizeof(shape_t));
  shape->shape_variant = ELLIPSE;
  shape->shape = sh;
  shape->styles = styles;

  return shape;
}

void free_ellipse(ellipse_t *ellipse) { free(ellipse); }

void print_ellipse(ellipse_t *ellipse) {
  printf("Ellipse { Center X = { %d }, Center Y = { %d }, Radius X = { %d }, "
         "Radius Y = { %d } }",
         ellipse->center_x, ellipse->center_y, ellipse->radius_x,
         ellipse->radius_y);
}

char *ellipse_to_string(ellipse_t *ellipse) {
  char *result = malloc(sizeof(char) * ELLIPSE_TO_STRING_SIZE);
  sprintf(result, "Ellispe { X=%d Y=%d Width=%d Height=%d }", ellipse->center_x,
          ellipse->center_y, ellipse->radius_x, ellipse->radius_y);
  return result;
}
