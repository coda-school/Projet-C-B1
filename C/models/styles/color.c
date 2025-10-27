#include "color.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

color_t *new_color(unsigned char red, unsigned char green, unsigned char blue,
                   unsigned char transparent) {
  color_t *color = malloc(sizeof(color_t));
  color->red = red;
  color->green = green;
  color->blue = blue;
  color->transparent = transparent;
  return color;
}

color_t *new_default_color() {
  color_t *color = malloc(sizeof(color_t));
  color->red = 0;
  color->green = 0;
  color->blue = 0;
  color->transparent = 255;
  return color;
}

color_t *clone_color(color_t *color) {
  return new_color(color->red, color->green, color->blue, color->transparent);
}

void free_color(color_t *color) { free(color); }

void print_color(color_t *color) {
  printf("Color: #%02x%02x%02x%02x", color->red, color->green, color->blue,
         color->transparent);
}
