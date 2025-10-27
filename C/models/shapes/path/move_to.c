#include "move_to.h"
#include "../../utils/point.h"
#include "path_element.h"
#include <stdio.h>
#include <stdlib.h>

#define MOVE_TO_STRING_SIZE 150

path_element_t *new_move_to(point_t *point) {
  path_element_t *move_to = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  path_element->move_to = point;
  move_to->path_element = path_element;
  move_to->path_element_variant = MOVE_TO;
  return move_to;
}

void free_move_to(move_to_t *move_to) { free_point(move_to); }

void print_move_to(move_to_t *move_to) {
  printf("Move to { ");
  print_point(move_to);
  printf(" }");
}

char *move_to_to_string(move_to_t *move_to) {
  char *result = malloc(sizeof(char) * MOVE_TO_STRING_SIZE);
  sprintf(result, "Move to { M %d %d }", move_to->x, move_to->y);
  return result;
}
