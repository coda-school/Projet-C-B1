#include "path.h"
#include "../../styles/style.h"
#include "../shape.h"
#include "curve_to.h"
#include "end_path.h"
#include "line_to.h"
#include "move_to.h"
#include "path_element.h"
#include <stdio.h>
#include <stdlib.h>

path_element_t *clone_path_element(path_element_t *element) {
  switch (element->path_element_variant) {
  case MOVE_TO:
    return new_move_to(clone_point(element->path_element->move_to));
    break;
  case LINE_TO:
    return new_line_to(clone_point(element->path_element->line_to));
    break;
  case VERTICAL_LINE_TO:
    return new_vertical_line_to(element->path_element->vertical_line_to);
    break;
  case HORIZONTAL_LINE_TO:
    return new_horizontal_line_to(element->path_element->horizontal_line_to);
    break;
  case END_PATH:
    return new_end_path();
    break;
  case CUBIC_CURVE_TO:
    return new_cubic_curve_to(
        clone_point(element->path_element->cubic_curve_to->control_point_1),
        clone_point(element->path_element->cubic_curve_to->control_point_2),
        clone_point(element->path_element->cubic_curve_to->end));
    break;
  case CUBIC_CURVE_TO_SHORTHAND:
    return new_cubic_curve_to_shorthand(
        clone_point(
            element->path_element->shorthand_cubic_curve_to->control_point),
        clone_point(element->path_element->shorthand_cubic_curve_to->end));
    break;
  case QUADRATIC_CURVE_TO:
    return new_quadratic_curve_to(
        clone_point(element->path_element->quadratic_curve_to->control_point),
        clone_point(element->path_element->quadratic_curve_to->end));
    break;
  case QUADRATIC_CURVE_TO_SHORTHAND:
    return new_quadratic_curve_to_shorthand(
        clone_point(element->path_element->shorthand_quadratic_curve_to));
    break;
  }
  return NULL;
}

void free_path_element(path_element_t *path_element) {
  switch (path_element->path_element_variant) {
  case MOVE_TO:
    free_move_to(path_element->path_element->move_to);
    break;
  case LINE_TO:
    free_line_to(path_element->path_element->line_to);
    break;
  case END_PATH:
    free_end_path(path_element->path_element->end_path);
    break;
  case CUBIC_CURVE_TO:
    free_cubic_curve_to(path_element->path_element->cubic_curve_to);
    break;
  case CUBIC_CURVE_TO_SHORTHAND:
    free_shorthand_cubic_curve_to(
        path_element->path_element->shorthand_cubic_curve_to);
    break;
  case QUADRATIC_CURVE_TO:
    free_quadratic_curve_to(path_element->path_element->quadratic_curve_to);
    break;
  case QUADRATIC_CURVE_TO_SHORTHAND:
    free_shorthand_quadratic_curve_to(
        path_element->path_element->shorthand_quadratic_curve_to);
    break;
  case VERTICAL_LINE_TO:
  case HORIZONTAL_LINE_TO:
    break;
  }
  free(path_element->path_element);
  free(path_element);
}

void print_path_element(path_element_t *path_element) {
  printf("Path element = { ");
  switch (path_element->path_element_variant) {
  case MOVE_TO:
    print_move_to(path_element->path_element->move_to);
    break;
  case LINE_TO:
    print_line_to(path_element->path_element->line_to);
    break;
  case VERTICAL_LINE_TO:
    print_horizontal_line_to(path_element->path_element->vertical_line_to);
    break;
  case HORIZONTAL_LINE_TO:
    print_vertical_line_to(path_element->path_element->horizontal_line_to);
    break;
  case END_PATH:
    print_end_path(path_element->path_element->end_path);
    break;
  case CUBIC_CURVE_TO:
    print_cubic_curve_to(path_element->path_element->cubic_curve_to);
    break;
  case CUBIC_CURVE_TO_SHORTHAND:
    print_shorthand_cubic_curve_to(
        path_element->path_element->shorthand_cubic_curve_to);
    break;
  case QUADRATIC_CURVE_TO:
    print_quadratic_curve_to(path_element->path_element->quadratic_curve_to);
    break;
  case QUADRATIC_CURVE_TO_SHORTHAND:
    print_shorthand_quadratic_curve_to(
        path_element->path_element->shorthand_quadratic_curve_to);
    break;
  }
  printf(" }");
}

path_element_node_t *clone_path_element_list(path_element_node_t *list) {
  path_element_node_t *node = list;
  path_element_node_t *result = NULL;
  while (node != NULL) {
    result = push_path_element_node(result, clone_path_element(node->element));
    node = node->next;
  }
  return result;
}

path_element_node_t *push_path_element_node(path_element_node_t *elements,
                                            path_element_t *element) {
  if (elements == NULL) {
    elements = malloc(sizeof(path_element_node_t));
    elements->element = element;
    elements->previous = NULL;
    elements->next = NULL;
    return elements;
  }

  path_element_node_t *p = elements;
  while (p->next != NULL)
    p = p->next;
  p->next = malloc(sizeof(path_element_node_t));
  p->next->element = element;
  p->next->next = NULL;
  p->next->previous = p;
  return elements;
}

path_element_node_t *insert_path_element_node_at(path_element_node_t *elements,
                                                 int index,
                                                 path_element_t *element) {
  // Invalid index
  if (index < 0)
    return NULL;

  // Inserts the element at the begining of the list
  if (index == 0) {
    path_element_node_t *p = malloc(sizeof(path_element_node_t));
    p->previous = NULL;
    p->next = elements;
    p->element = element;
    elements->previous = p;
    return p;
  }

  /// Inserts the element in the middle of the list.
  int i = 0;
  path_element_node_t *p1 = NULL;
  path_element_node_t *p2 = elements;
  while (p2->next != NULL) {
    p1 = p2;
    p2 = p2->next;
    if (i == index) {
      path_element_node_t *p = malloc(sizeof(path_element_node_t));
      p->element = element;
      p->next = p2;
      p->previous = p1;
      p1->next = p;
      p2->previous = p;
      return elements;
    }
    i++;
  }

  // Invalid index.
  if (index != i)
    return NULL;

  // Inserts the element at the end of the list.
  path_element_node_t *p = malloc(sizeof(path_element_node_t));
  p->element = element;
  p->next = NULL;
  p->previous = p2;
  p2->next = p;

  return elements;
}

path_element_node_t *remove_path_element_node_at(path_element_node_t *elements,
                                                 int index) {
  // Invalid index.
  if (index < 0)
    return elements;

  // Removes the element at the start of the list.
  if (index == 0) {
    path_element_node_t *element = elements->next;
    free(elements->element);
    free(elements);
    return element;
  }

  // Removes the element in the middle of the list.
  int i = 0;
  path_element_node_t *p1 = NULL;
  path_element_node_t *p2 = elements;
  while (p2->next != NULL) {
    if (i == index) {
      p1->next = p2->next;
      p2->previous = p1;
      free_path_element(p2->element);
      free(p2);
      return elements;
    }
    p1 = p2;
    p2 = p2->next;
    i++;
  }

  // Invalid index.
  if (index != i)
    return elements;

  // Removes the element at the end of the list.
  p1->next = NULL;
  free_path_element(p2->element);
  free(p2);

  return elements;
}

int get_path_element_node_length(path_element_node_t *elements) {
  int i = 0;
  path_element_node_t *p = elements;
  while (p != NULL) {
    p = p->next;
    i++;
  }
  return i;
}

void free_path_element_nodes(path_element_node_t *elements) {
  if (elements != NULL)
    return;
  path_element_node_t *p1 = NULL;
  path_element_node_t *p2 = elements;
  while (p2 != NULL) {
    free_path_element(p1->element);
    free(p1);
    p1 = p2;
    p2 = p2->next;
  }
  free_path_element(p1->element);
  free(p1);
}

shape_t *new_path(path_element_node_t *path_elements, style_t *styles) {
  shape_union_t *sh = malloc(sizeof(shape_union_t));
  sh->path = path_elements;

  shape_t *shape = malloc(sizeof(shape_t));
  shape->shape_variant = PATH;
  shape->shape = sh;
  shape->styles = styles;

  return shape;
}

void free_path(path_t *path) { free_path_element_nodes(path); }

void print_path(path_t *path) {
  printf("Path { Elements = [ ");
  path_element_node_t *node = path;
  while (node != NULL) {
    print_path_element(node->element);
    printf(", ");
    node = node->next;
  }
  printf("] }");
}
