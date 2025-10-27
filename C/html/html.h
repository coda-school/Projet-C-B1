#ifndef CODA_HTML
#define CODA_HTML

#include "../models/shapes/path/path.h"
#include "../models/shapes/svg.h"
#include <stdio.h>

/**
 * Writes down the given number of tabulations to the given file.
 * @param file   an opened file in writing mode.
 * @param amount the number of tabulations to write.
 */
void export_tabs_html(FILE *file, unsigned int amount);

/**
 * Writes down the given styles to the given file in HTML format.
 * @param file   an opened file in writing mode.
 * @param styles the styles to write down.
 * @see style_t.
 */
void export_styles_html(FILE *file, style_t *styles);

/**
 * Writes down the given point linked list to the given file in HTML format.
 * @param file   an opened file in writing mode.
 * @param points the linked list to write down.
 * @see point_t.
 * @see point_node_t.
 */
void export_points_html(FILE *file, point_node_t *points);

/**
 * Writes down the given path element to the given file in HTML format.
 * @param file    an opened file in writing mode.
 * @param element the path element to write down.
 * @see path_element_t.
 */
void export_path_element_html(FILE *file, path_element_t *element);

/**
 * Writes down the given path element linked list to the given file in HTML
 * format.
 * @param file     an opened file in writing mode.
 * @param elements the path element linked list to write down.
 * @see path_element_t.
 * @see path_element_node_t.
 */
void export_path_elements_html(FILE *file, path_element_node_t *elements);

/**
 * Writes down the given shape linked list to the given file in HTML format.
 * @param file   an opened file in writing mode.
 * @param shapes the shape linked list to write down.
 * @param depth  the number of tabulations to write.
 * @see shape_t.
 * @see shape_node_t.
 */
void export_shapes_html(FILE *file, shape_node_t *shapes, unsigned int depth);

/**
 * Writes down the given shape to the given file in HTML format.
 * @param file  an opened file in writing mode.
 * @param shape the shape to write down.
 * @param depth the number of tabulations to write.
 * @see shape_t.
 */
void export_shape_html(FILE *file, shape_t *shape, unsigned int depth);

/**
 * Writes down the given svg to the given file path.
 * @param svg the svg to write down.
 * @param the destination file's path.
 * @return returns true if the operation succeeded.
 * @see svg_t.
 */
bool export_to_html(svg_t *svg, char *path);

#endif
