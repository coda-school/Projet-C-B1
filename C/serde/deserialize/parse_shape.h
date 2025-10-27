#ifndef CODA_PARSE_SHAPE
#define CODA_PARSE_SHAPE

#include "../../models/shapes/shape.h"
#include "../../models/styles/style.h"
#include "../serde.h"

/**
 * Attempts to parse an ellipse.
 * Note that this function allocates memory.
 * Note that this function expects that the last consumed char is 'e'. The
 * function will consume the text pattern 'llipse' before parsing the ellipse
 * content. If the parsing fails the function returns NULL. If there is a
 * missing parameter the function returns NULL. If the function succeeds, it
 * returns the new ellipse shape's pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the new ellipse default styles.
 * @return the new ellipse shape's pointer.
 * @see style_t.
 * @see serdelizer_t.
 * @see ellipse_t.
 * @see shape_t.
 */
shape_t *parse_ellipse(serdelizer_t *serdelizer, style_t *inherited_styles);

/**
 * Attempts to parse an rectangle.
 * Note that this function allocates memory.
 * Note that this function expects that the last consumed char is 'r'. The
 * function will consume the text pattern 'ectangle' before parsing the
 * rectangle content. If the parsing fails the function returns NULL. If there
 * is a missing parameter the function returns NULL. If the function succeeds,
 * it returns the new rectangle shape's pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the new rectangle default styles.
 * @return the new rectangle shape's pointer.
 * @see style_t.
 * @see serdelizer_t.
 * @see rectangle_t.
 * @see shape_t.
 */
shape_t *parse_rectangle(serdelizer_t *serdelizer, style_t *inherited_styles);

/**
 * Attempts to parse an line.
 * Note that this function allocates memory.
 * Note that this function expects that the last consumed char is 'l'. The
 * function will consume the text pattern 'ine' before parsing the line
 * content. If the parsing fails the function returns NULL. If there is a
 * missing parameter the function returns NULL. If the function succeeds, it
 * returns the new line shape's pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the new line default styles.
 * @return the new line shape's pointer.
 * @see style_t.
 * @see serdelizer_t.
 * @see line_t.
 * @see shape_t.
 */
shape_t *parse_line(serdelizer_t *serdelizer, style_t *inherited_styles);

/**
 * Attempts to parse an multiline.
 * Note that this function allocates memory.
 * Note that this function expects that the last consumed char is 'm'. The
 * function will consume the text pattern 'ultiline' before parsing the
 * multiline content. If the parsing fails the function returns NULL. If there
 * is a missing parameter the function returns NULL. If the function succeeds,
 * it returns the new multiline shape's pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the new multiline default styles.
 * @return the new multiline shape's pointer.
 * @see style_t.
 * @see serdelizer_t.
 * @see multiline_t.
 * @see shape_t.
 */
shape_t *parse_multiline(serdelizer_t *serdelizer, style_t *inherited_styles);

/**
 * Attempts to parse an polygon.
 * Note that this function allocates memory.
 * Note that this function expects that the last consumed char is 'p'. The
 * function will consume the text pattern 'olygon' before parsing the polygon
 * content. If the parsing fails the function returns NULL. If there is a
 * missing parameter the function returns NULL. If the function succeeds, it
 * returns the new polygon shape's pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the new polygon default styles.
 * @return the new polygon shape's pointer.
 * @see style_t.
 * @see serdelizer_t.
 * @see polygon_t.
 * @see shape_t.
 */
shape_t *parse_polygon(serdelizer_t *serdelizer, style_t *inherited_styles);

/**
 * Attempts to parse an path.
 * Note that this function allocates memory.
 * Note that this function expects that the last consumed char is 'd'. The
 * function will consume the text pattern 'raw' before parsing the path
 * content. If the parsing fails the function returns NULL. If there is a
 * missing parameter the function returns NULL. If the function succeeds, it
 * returns the new path shape's pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the new path default styles.
 * @return the new path shape's pointer.
 * @see style_t.
 * @see serdelizer_t.
 * @see path_t.
 * @see shape_t.
 */
shape_t *parse_path(serdelizer_t *serdelizer, style_t *inherited_styles);

/**
 * Attempts to parse an group.
 * Note that this function allocates memory.
 * Note that this function expects that the last consumed char is 'g'. The
 * function will consume the text pattern 'roup' before parsing the group
 * content. If the parsing fails the function returns NULL. If there is a
 * missing parameter the function returns NULL. If the function succeeds, it
 * returns the new group shape's pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the new group default styles.
 * @return the new group shape's pointer.
 * @see style_t.
 * @see serdelizer_t.
 * @see group_t.
 * @see shape_t.
 */
shape_t *parse_group(serdelizer_t *serdelizer, style_t *inherited_styles);

/**
 * Attempts to parse a shape.
 * Note that this function allocates memory.
 * Note that this function expects the last consumed char to be is the following
 * list : ['e', 'r', 'l', 'm', 'p', 'd', 'g']. If the function fails to parse a
 * shape it returns NULL. If the function succeeds it returns the new shape's
 * pointer.
 * @param serdelizer       the file accessor.
 * @param inherited_styles the shape's parent styles. It is used as default
 * styles.
 * @return the new shape's pointer.
 * @see style_t.
 * @see shape_t.
 * @see serdelizer_t.
 */
shape_t *parse_shape(serdelizer_t *serdelizer, style_t *inherited_styles);

#endif
