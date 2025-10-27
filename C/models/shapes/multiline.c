#include "multiline.h"
#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

shape_t *new_multiline(point_node_t *points, style_t *styles) {
  shape_union_t *sh = malloc(sizeof(shape_union_t));
  sh->multiline = points;

  shape_t *shape = malloc(sizeof(shape_t));
  shape->shape_variant = MULTILINE;
  shape->shape = sh;
  shape->styles = styles;

  return shape;
}

void free_multiline(multiline_t *multiline) { free_point_nodes(multiline); }

void print_multiline(multiline_t *multiline) {
  printf("Multiline { Points = [ ");
  point_node_t *node = multiline;
  while (node != NULL) {
    print_point(node->point);
    printf(", ");
    node = node->next;
  }
  printf("] }");
}
