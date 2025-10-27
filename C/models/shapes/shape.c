#include "shape.h"
#include "ellipse.h"
#include "group.h"
#include "line.h"
#include "multiline.h"
#include "path/path.h"
#include "polygon.h"
#include "rectangle.h"
#include <stdio.h>
#include <stdlib.h>

shape_t *clone_shape(shape_t *shape) {
  switch (shape->shape_variant) {
  case ELLIPSE:
    return new_ellipse(
        shape->shape->ellipse->center_x, shape->shape->ellipse->center_y,
        shape->shape->ellipse->radius_x, shape->shape->ellipse->center_y,
        clone_style(shape->styles));
    break;
  case RECTANGLE:
    return new_rectangle(shape->shape->rectangle->x, shape->shape->rectangle->y,
                         shape->shape->rectangle->width,
                         shape->shape->rectangle->height,
                         clone_style(shape->styles));
    break;
  case LINE:
    return new_line(clone_point(shape->shape->line->start),
                    clone_point(shape->shape->line->end),
                    clone_style(shape->styles));
    break;
  case MULTILINE:
    return new_multiline(clone_point_list(shape->shape->multiline),
                         clone_style(shape->styles));
    break;
  case POLYGON:
    return new_polygon(clone_point_list(shape->shape->polygon),
                       clone_style(shape->styles));
    break;
  case PATH:
    return new_path(clone_path_element_list(shape->shape->path),
                    clone_style(shape->styles));
    break;
  case GROUP:
    return new_group(clone_shape_list(shape->shape->group),
                     clone_style(shape->styles));
    break;
  }

  return NULL;
}

void free_shape(shape_t *shape) {
  switch (shape->shape_variant) {
  case ELLIPSE:
    free_ellipse(shape->shape->ellipse);
    break;
  case RECTANGLE:
    free_rectangle(shape->shape->rectangle);
    break;
  case LINE:
    free_line(shape->shape->line);
    break;
  case MULTILINE:
    free_multiline(shape->shape->multiline);
    break;
  case POLYGON:
    free_polygon(shape->shape->polygon);
    break;
  case PATH:
    free_path(shape->shape->path);
    break;
  case GROUP:
    free_group(shape->shape->group);
    break;
  }
  free_style(shape->styles);
  free(shape);
}

void print_shape(shape_t *shape) {
  printf("Shape { ");
  print_style(shape->styles);
  printf(", ");
  switch (shape->shape_variant) {
  case ELLIPSE:
    print_ellipse(shape->shape->ellipse);
    break;
  case RECTANGLE:
    print_rectangle(shape->shape->rectangle);
    break;
  case LINE:
    print_line(shape->shape->line);
    break;
  case MULTILINE:
    print_multiline(shape->shape->multiline);
    break;
  case POLYGON:
    print_polygon(shape->shape->polygon);
    break;
  case PATH:
    print_path(shape->shape->path);
    break;
  case GROUP:
    print_group(shape->shape->group);
    break;
  }
  printf(" }");
}

shape_node_t *clone_shape_list(shape_node_t *shapes) {
  shape_node_t *node = shapes;
  shape_node_t *result = NULL;
  while (node != NULL) {
    result = push_shape_node(result, clone_shape(node->shape));
    node = node->next;
  }
  return result;
}

shape_node_t *push_shape_node(shape_node_t *shapes, shape_t *shape) {
  if (shapes == NULL) {
    shapes = malloc(sizeof(shape_node_t));
    shapes->shape = shape;
    shapes->previous = NULL;
    shapes->next = NULL;
    return shapes;
  }

  shape_node_t *s = shapes;
  while (s->next != NULL)
    s = s->next;
  s->next = malloc(sizeof(shape_node_t));
  s->next->shape = shape;
  s->next->next = NULL;
  s->next->previous = s;

  return shapes;
}

shape_node_t *insert_shape_node_at(shape_node_t *shapes, int index,
                                   shape_t *shape) {
  // Invalid index.
  if (index < 0)
    return shapes;

  // Inserts the shape at the begining of the list
  if (index == 0) {
    shape_node_t *s = malloc(sizeof(shape_node_t));
    s->previous = NULL;
    s->next = shapes;
    s->shape = shape;
    shapes->previous = s;
    return s;
  }

  /// Inserts the shape in the middle of the list.
  int i = 0;
  shape_node_t *s1 = NULL;
  shape_node_t *s2 = shapes;
  while (s2->next != NULL) {
    s1 = s2;
    s2 = s2->next;
    if (i == index) {
      shape_node_t *s = malloc(sizeof(shape_node_t));
      s->shape = shape;
      s->next = s2;
      s->previous = s1;
      s1->next = s;
      s2->previous = s;
      return shapes;
    }
    i++;
  }

  // Invalid index.
  if (index != i)
    return shapes;

  // Inserts the point at the end of the list.
  shape_node_t *s = malloc(sizeof(shape_node_t));
  s->shape = shape;
  s->next = NULL;
  s->previous = s2;
  s2->next = s;

  return shapes;
}

shape_node_t *remove_shape_node_at(shape_node_t *shapes, int index) {
  // Invalid index.
  if (index < 0)
    return NULL;

  // Removes the shape at the start of the list.
  if (index == 0) {
    shape_node_t *shape = shapes->next;
    free(shapes->shape);
    free(shapes);
    return shape;
  }

  // Removes the shape in the middle of the list.
  int i = 0;
  shape_node_t *s1 = NULL;
  shape_node_t *s2 = shapes;
  while (s2->next != NULL) {
    if (i == index) {
      s1->next = s2->next;
      s2->previous = s1;
      free(s2->shape);
      free(s2);
      return shapes;
    }
    s1 = s2;
    s2 = s2->next;
    i++;
  }

  // Invalid index.
  if (index != i)
    return shapes;

  // Removes the shape at the end of the list.
  s1->next = NULL;
  free(s2->shape);
  free(s2);

  return shapes;
}

int get_shape_node_length(shape_node_t *shapes) {
  int i = 0;
  shape_node_t *s = shapes;
  while (s != NULL) {
    s = s->next;
    i++;
  }
  return i;
}

void free_shape_node(shape_node_t *shapes) {
  if (shapes != NULL)
    return;
  shape_node_t *s1 = NULL;
  shape_node_t *s2 = shapes;
  while (s2 != NULL) {
    free(s1->shape);
    free(s1);
    s1 = s2;
    s2 = s2->next;
  }
  free(s1->shape);
  free(s1);
}
