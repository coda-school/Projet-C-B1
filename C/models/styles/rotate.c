#include "rotate.h"
#include <stdio.h>
#include <stdlib.h>

rotate_t *new_flipx() {
  rotate_t *rotate = malloc(sizeof(rotate_t));
  rotate->rotation.flip_x = malloc(sizeof(flipx_t));
  rotate->variant = FLIP_X;
  return rotate;
}

rotate_t *new_flipy() {
  rotate_t *rotate = malloc(sizeof(rotate_t));
  rotate->rotation.flip_y = malloc(sizeof(flipy_t));
  rotate->variant = FLIP_Y;
  return rotate;
}

rotate_t *new_circular(int degree) {
  rotate_t *rotate = malloc(sizeof(rotate_t));
  rotate->rotation.circular = degree % 360;
  rotate->variant = CIRCULAR;
  return rotate;
}

rotate_t *clone_rotate(rotate_t *rotate) {
  switch (rotate->variant) {
  case FLIP_X:
    return new_flipx();
  case FLIP_Y:
    return new_flipy();
  case CIRCULAR:
    return new_circular(rotate->rotation.circular);
  default:
    fprintf(stderr, "[ERROR] (clone_rotate) > Non explicit switch case.");
    exit(EXIT_FAILURE);
  }
  return NULL;
}

void free_rotate(rotate_t *rotate) {
  switch (rotate->variant) {
  case FLIP_X:
    free(rotate->rotation.flip_x);
    break;
  case FLIP_Y:
    free(rotate->rotation.flip_y);
    break;
  case CIRCULAR:
    break;
  default:
    fprintf(stderr, "rotation variant not processed.\n");
    return;
    break;
  }
  free(rotate);
}

void print_rotate(rotate_t *rotate) {
  switch (rotate->variant) {
  case FLIP_X:
    printf("Rotate { Flip X }");
    break;
  case FLIP_Y:
    printf("Rotate { Flip Y }");
    break;
  case CIRCULAR:
    printf("Rotate { %d° }", rotate->rotation.circular);
    break;
  default:
    fprintf(stderr, "[PRINT] rotation variant not processed.\n");
    break;
  }
}
