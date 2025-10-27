#include "style.h"
#include "../styles/color.h"
#include "../styles/rotate.h"
#include "../utils/point.h"
#include <stdio.h>
#include <stdlib.h>

style_t *new_style(color_t *fill, color_t *outline, point_t *translate,
                   rotate_t *rotate) {
  style_t *style = malloc(sizeof(style_t));
  style->fill = fill;
  style->outline = outline;
  style->translate = translate;
  style->rotate = rotate;
  return style;
}

style_t *new_default_style() {
  style_t *style = malloc(sizeof(style_t));
  style->fill = new_default_color();
  style->outline = new_default_color();
  style->translate = new_point(0, 0);
  style->rotate = new_circular(0);
  return style;
}

style_t *clone_style(style_t *style) {
  return new_style(clone_color(style->fill), clone_color(style->outline),
                   clone_point(style->translate), clone_rotate(style->rotate));
}

void free_style(style_t *style) {
  free_color(style->fill);
  free_color(style->outline);
  free_point(style->translate);
  free_rotate(style->rotate);
  free(style);
}

void print_style(style_t *style) {
  printf("Style { Fill = { ");
  print_color(style->fill);
  printf(" }, Outline = { ");
  print_color(style->outline);
  printf(" }, Translate = { ");
  print_point(style->translate);
  printf(" }, Rotate = { ");
  print_rotate(style->rotate);
  printf(" } }");
}
