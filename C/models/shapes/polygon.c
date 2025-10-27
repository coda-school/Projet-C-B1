#include "polygon.h"
#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

shape_t *new_polygon(point_node_t *points, style_t *styles) {
  shape_union_t *sh = malloc(sizeof(shape_union_t));
  sh->polygon = points;

  shape_t *shape = malloc(sizeof(shape_t));
  shape->shape_variant = POLYGON;
  shape->shape = sh;
  shape->styles = styles;

  return shape;
}

void free_polygon(polygon_t *polygon) { free_point_nodes(polygon); }

void print_polygon(polygon_t *polygon) {
  printf("Polygon { Points = [ ");
  point_node_t *node = polygon;
  while (node != NULL) {
    print_point(node->point);
    printf(", ");
    node = node->next;
  }
  printf("] }");
}
