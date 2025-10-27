#ifndef CODA_SVG
#define CODA_SVG

#include "../styles/style.h"
#include "../utils/point.h"
#include "shape.h"

/**
 * Defines the viewport type.
 * @param start the viewport's start position.
 * @param end   the viewport's end position.
 * @see point_t.
 */
typedef struct viewport_s {
  point_t *start;
  point_t *end;
} viewport_t;

/**
 * Creates a new viewport.
 * Note that this function allocates memory.
 * @param start the viewport's start position.
 * @param end   the viewport's start position.
 * @return the new viewport's pointer.
 * @see point_t.
 */
viewport_t *new_viewport(point_t *start, point_t *end);

/**
 * Prints out the given viewport.
 * Note that this function is for debug purposes only.
 * @param viewport the viewport to be printed out.
 * @see viewport_t.
 */
void print_viewport(viewport_t *viewport);

/**
 * Destroys the given viewport.
 * Note that this function frees memory.
 * @param viewport the viewport to be destroyed.
 * @see viewport_t.
 */
void free_viewport(viewport_t *viewport);

/**
 * Definew the svg type.
 * @param viewport the svg's viewport.
 * @param shapes   the svg's shapes.
 * @see viewport_t.
 * @see shape_node_t.
 */
typedef struct svg_s {
  viewport_t *viewport;
  shape_node_t *shapes;
} svg_t;

/**
 * Creates a new svg.
 * Note that this function allocates memory.
 * @param viewport the svg's viewport.
 * @param shapes   the svg's shapes.
 * @return the new svg's pointer.
 * @see shape_node_t.
 * @see viewport_t.
 * @see svg_t.
 */
svg_t *new_svg(viewport_t *viewport, shape_node_t *shapes);

/**
 * Duplicates the given svg.
 * Note that this function allocates memory.
 * @param svg the svg to duplicate.
 * @return the duplicated svg's pointer.
 * @see svg_t.
 */
svg_t *clone_svg(svg_t *svg);

/**
 * Prints out the given svg.
 * Note that this function is for debug purposes only.
 * @param svg the svg to be printed out.
 * @see svg_t.
 */
void print_svg(svg_t *svg);

/**
 * Destroys the given svg.
 * Note that this function frees memory.
 * @param svg the svg to be destroyed.
 * @see svg_t.
 */
void free_svg(svg_t *svg);

#endif
