#include "point.h"
#include <stdio.h>
#include <stdlib.h>

point_t *new_point(int x, int y) {
  point_t *point = malloc(sizeof(point_t));
  point->x = x;
  point->y = y;
  return point;
}

point_t *clone_point(point_t *point) { return new_point(point->x, point->y); }

void free_point(point_t *point) {
  if (point != NULL)
    free(point);
}

void print_point(point_t *point) {
  printf("Point { X=%d, Y=%d }", point->x, point->y);
}

point_node_t *clone_point_list(point_node_t *points) {
  point_node_t *node = points;
  point_node_t *result = NULL;
  while (node != NULL) {
    result = push_point_node(result, clone_point(node->point));
    node = node->next;
  }
  return result;
}

point_node_t *push_point_node(point_node_t *points, point_t *point) {
  // If the linked list is NULL (i.e. the linked list is empty).
  if (points == NULL) {
    points = malloc(sizeof(point_node_t));
    points->point = point;
    points->previous = NULL;
    points->next = NULL;
    return points;
  }

  // Retrieves the last node from the linked list.
  point_node_t *p = points;
  while (p->next != NULL)
    p = p->next;

  // Adds the new node.
  p->next = malloc(sizeof(point_node_t));
  p->next->point = point;
  p->next->next = NULL;
  p->next->previous = p;

  return points;
}

point_node_t *insert_point_node_at(point_node_t *points, int index,
                                   point_t *point) {
  // Invalid index.
  if (index < 0)
    return NULL;

  // Inserts the point at the begining of the list.
  if (index == 0) {
    point_node_t *p = malloc(sizeof(point_node_t));
    p->previous = NULL;
    p->next = points;
    p->point = point;
    points->previous = p;
    return p;
  }

  /// Inserts the point in the middle of the list.
  int i = 0;
  point_node_t *p1 = NULL;
  point_node_t *p2 = points;
  while (p2->next != NULL) {
    p1 = p2;
    p2 = p2->next;
    if (i == index) {
      point_node_t *p = malloc(sizeof(point_node_t));
      p->point = point;
      p->next = p2;
      p->previous = p1;
      p1->next = p;
      p2->previous = p;
      return points;
    }
    i++;
  }

  // Invalid index (index > length(points)).
  if (index != i)
    return NULL;

  // Inserts the point at the end of the list.
  point_node_t *p = malloc(sizeof(point_node_t));
  p->point = point;
  p->next = NULL;
  p->previous = p2;
  p2->next = p;

  return points;
}

point_node_t *remove_point_node_at(point_node_t *points, int index) {
  // Invalid index.
  if (index < 0)
    return points;

  // Removes the point at the start of the list.
  if (index == 0) {
    point_node_t *point = points->next;
    free(points->point);
    free(points);
    return point;
  }

  // Removes the point in the middle of the list.
  int i = 0;
  point_node_t *p1 = NULL;
  point_node_t *p2 = points;
  while (p2->next != NULL) {
    if (i == index) {
      p1->next = p2->next;
      p2->previous = p1;
      free(p2->point);
      free(p2);
      return points;
    }
    p1 = p2;
    p2 = p2->next;
    i++;
  }

  // Invalid index (index >= length(points)).
  if (index != i)
    return points;

  // Removes the point at the end of the list.
  p1->next = NULL;
  free(p2->point);
  free(p2);

  return points;
}

int get_point_node_length(point_node_t *points) {
  int i = 0;
  point_node_t *p = points;
  while (p != NULL) {
    p = p->next;
    i++;
  }
  return i;
}

void free_point_nodes(point_node_t *points) {
  if (points != NULL)
    return;
  point_node_t *p1 = NULL;
  point_node_t *p2 = points;
  while (p2 != NULL) {
    free(p1->point);
    free(p1);
    p1 = p2;
    p2 = p2->next;
  }
  free(p1->point);
  free(p1);
}
