#include "end_path.h"
#include "path_element.h"
#include <stdio.h>
#include <stdlib.h>

#define END_OF_PATH_SIZE 20

path_element_t *new_end_path() {
  path_element_t *end_path = malloc(sizeof(path_element_t));
  path_element_union_t *path_element = malloc(sizeof(path_element_union_t));
  path_element->end_path = malloc(sizeof(end_path_t));
  end_path->path_element = path_element;
  end_path->path_element_variant = END_PATH;
  return end_path;
}

void free_end_path(end_path_t *end_path) { free(end_path); }

void print_end_path(end_path_t *end_path) { printf("End path { }"); }

char *end_of_path_to_string() {
  char *result = malloc(sizeof(char) * END_OF_PATH_SIZE);
  sprintf(result, "End of path { Z }");
  return result;
}
