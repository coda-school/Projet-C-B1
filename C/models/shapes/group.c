#include "group.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

shape_t *new_group(shape_node_t *shapes, style_t *styles) {
  shape_union_t *sh = malloc(sizeof(shape_union_t));
  sh->group = shapes;

  shape_t *shape = malloc(sizeof(shape_t));
  shape->shape_variant = GROUP;
  shape->shape = sh;
  shape->styles = styles;

  return shape;
}

void free_group(group_t *group) { free_shape_node(group); }

void print_group(group_t *group) {
  printf("Group { Shapes = [ ");
  shape_node_t *shape = group;
  while (shape != NULL) {
    print_shape(shape->shape);
    printf(", ");
  }
  printf(" ] }");
}
