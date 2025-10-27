#include "svg.h"
#include "../utils/point.h"
#include "shape.h"
#include <stdio.h>
#include <stdlib.h>

viewport_t *new_viewport(point_t *start, point_t *end) {
  viewport_t *viewport = malloc(sizeof(viewport_t));
  viewport->start = start;
  viewport->end = end;
  return viewport;
}

void print_viewport(viewport_t *viewport) {
  printf("Viewport { Start = { ");
  print_point(viewport->start);
  printf(" }, End = { ");
  print_point(viewport->end);
  printf(" } }");
}

void free_viewport(viewport_t *viewport) {
  free_point(viewport->start);
  free_point(viewport->end);
  free(viewport);
}

svg_t *new_svg(viewport_t *viewport, shape_node_t *shapes) {
  svg_t *svg = malloc(sizeof(svg_t));
  svg->viewport = viewport;
  svg->shapes = shapes;

  return svg;
}

void print_svg(svg_t *svg) {
  printf("Svg { Viewport = { ");
  print_viewport(svg->viewport);
  printf(" }, Shapes = [ ");
  shape_node_t *s = svg->shapes;
  while (s != NULL) {
    print_shape(s->shape);
    printf(", ");
    s = s->next;
  }
  printf(" ] }");
}

void free_svg(svg_t *svg) {
  if (svg->viewport != NULL)
    free_viewport(svg->viewport);
  if (svg->shapes != NULL)
    free_shape_node(svg->shapes);
  free(svg);
}
