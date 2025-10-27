#ifndef CODA_CLI_SHAPE
#define CODA_CLI_SHAPE

#include "../models/shapes/shape.h"
#include "cli_path.h"

/**
 * Displays a formatted version of the given ellipse and the given styles.
 * This function displays in xml format.
 * @param ellipse the ellipse to display.
 * @param styles the styles to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see ellipse_t.
 * @see style_t.
 */
void cli_print_ellipse(ellipse_t *ellipse, style_t *styles, int depth);

/**
 * Displays a formatted version of the given rectangle and the given styles.
 * This function displays in xml format.
 * @param rectangle the rectangle to display.
 * @param styles the styles to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see rectangle_t.
 * @see style_t.
 */
void cli_print_rectangle(rectangle_t *rectangle, style_t *styles, int depth);

/**
 * Displays a formatted version of the given line and the given styles.
 * This function displays in xml format.
 * @param line the line to display.
 * @param styles the styles to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see line_t.
 * @see style_t.
 */
void cli_print_line(line_t *line, style_t *styles, int depth);

/**
 * Displays a formatted version of the given multiline and the given styles.
 * This function displays in xml format.
 * @param multiline the multiline to display.
 * @param styles the styles to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see multiline_t.
 * @see style_t.
 */
void cli_print_multiline(multiline_t *multiline, style_t *styles, int depth);

/**
 * Displays a formatted version of the given polygon and the given styles.
 * This function displays in xml format.
 * @param polygon the polygon to display.
 * @param styles the styles to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see polygon_t.
 * @see style_t.
 */
void cli_print_polygon(polygon_t *polygon, style_t *styles, int depth);

/**
 * Displays a formatted version of the given path and the given styles.
 * This function displays in xml format.
 * @param path the path to display.
 * @param styles the styles to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see path_t.
 * @see style_t.
 */
void cli_print_path(path_t *path, style_t *styles, int depth);

/**
 * Displays a formatted version of the given group and the given styles.
 * This function displays in xml format.
 * @param group the group to display.
 * @param styles the styles to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see group_t.
 * @see style_t.
 */
void cli_print_group(group_t *group, style_t *styles, int depth);

/**
 * Displays a formatted version of the given shape and the given styles.
 * This function displays in xml format.
 * @param shape the shape to display.
 * @param depth the number of tabs to print before displaying the other
 * elements.
 * @see shape_t.
 */
void cli_print_shape(shape_t *shape, int depth);

/**
 * Asks the user to update the given ellipse.
 * If the user submits an empty answer the update is skipped.
 * @param ellipse the ellipse to update.
 * @see ellipse_t.
 */
void cli_edit_ellipse(ellipse_t *ellipse);

/**
 * Asks the user to update the given rectangle.
 * If the user submits an empty answer the update is skipped.
 * @param rectangle the rectangle to update.
 * @see rectangle_t.
 */
void cli_edit_rectangle(rectangle_t *rectangle);

/**
 * Asks the user to update the given line.
 * If the user submits an empty answer the update is skipped.
 * @param line the line to update.
 * @see line_t.
 */
void cli_edit_line(line_t *line);

/**
 * Asks the user to update the given point.
 * If the user submits an empty answer the update is skipped.
 * @param point the point to update.
 * @see point_t.
 */
void cli_edit_point(point_t *point);

/**
 * Asks the user to add a point to the given point linked list.
 * Note that this function allocates memory.
 * @param points the point linked list.
 * @see point_node_t.
 */
void cli_add_point(point_node_t **points);

/**
 * Asks the user to remove a point to the given point linked list.
 * Note that this function frees memory.
 * @param points the point linked list.
 * @see point_node_t.
 */
void cli_remove_point(point_node_t **points);

/**
 * Asks the user to edit a point to the given point linked list.
 * @param points the point linked list.
 * @see point_node_t.
 */
void cli_edit_points(point_node_t *points);

/**
 * Asks the user to update the given multiline.
 * If the user submits an empty answer the update is skipped.
 * @param multiline the multiline to update.
 * @param styles the styles to update.
 * @see multiline_t.
 */
void cli_edit_multiline(multiline_t **multiline, style_t *styles);

/**
 * Asks the user to update the given polygon.
 * If the user submits an empty answer the update is skipped.
 * @param polygon the polygon to update.
 * @param styles the styles to update.
 * @see polygon_t.
 */
void cli_edit_polygon(polygon_t **polygon, style_t *styles);

/**
 * Asks the user to add a path element in given path element linked list.
 * Note that this function allocates memory.
 * @param elements the path element linked list.
 * @see path_element_t.
 * @see path_element_node_t.
 */
void cli_add_path_element(path_element_node_t **elements);

/**
 * Asks the user to remove a path element in given path element linked list.
 * Note that this function frees memory.
 * @param elements the path element linked list.
 */
void cli_remove_path_element(path_element_node_t **elements);

/**
 * Asks the user to edit a path element in given path element linked list.
 * @param elements the path element linked list.
 * @see path_element_t.
 * @see path_element_node_t.
 */
void cli_edit_path_elements(path_element_node_t *elements);

/**
 * Asks the user to update the given path.
 * @param path the path to update.
 * @param styles the given path's styles.
 * @see style_t.
 * @see path_t.
 */
void cli_edit_path(path_t **path, style_t *styles);

/**
 * Asks the user to add a new shape in the given shape linked list.
 * Note that this function allocates memory.
 * @param shapes the shape linked list.
 * @param inherited_styles the new shape inherited styles.
 * @see style_t.
 * @see shape_t.
 * @see shape_node_t.
 */
void cli_add_shape(shape_node_t **shapes, style_t *inherited_styles);

/**
 * Asks the user to update a shape in the given shape linked list.
 * @param shapes the shape linked list.
 * @see shape_node_t.
 */
void cli_edit_shapes(shape_node_t *shapes);

/**
 * Asks the user to remove a new shape in the given shape linked list.
 * Note that this function frees memory.
 * @param shapes the shape linked list.
 * @see shape_t.
 * @see shape_node_t.
 */
void cli_remove_shape(shape_node_t **shapes);

/**
 * Asks the user to update the given group.
 * @param group the group to update.
 * @param inherited_styles the group's styles.
 * @see style_t.
 * @see group_t.
 */
void cli_edit_group(group_t **group, style_t *inherited_styles);

/**
 * Asks the user to update the given shape.
 * @param shape the shape to update.
 * @see shape_t.
 */
void cli_edit_shape(shape_t *shape);

/**
 * Asks the user to create a new shape.
 * If the user submit an empty answer this function returns NULL.
 * Note that this function allocates memory.
 * @param inherited_styles the new shape's inheroted styles.
 * @return the new shape's pointer.
 * @see style_t.
 * @see shape_t.
 */
shape_t *cli_new_shape(style_t *inherited_styles);

#endif
