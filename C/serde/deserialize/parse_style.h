#ifndef CODA_PARSE_STYLE
#define CODA_PARSE_STYLE

#include "../../models/styles/color.h"
#include "../../models/styles/rotate.h"
#include "../../models/styles/style.h"
#include "../../models/utils/point.h"
#include "../serde.h"

/**
 * Attempts to parse an outline color.
 * Note that this function frees and allocates memory.
 * Note that the function expects the character 'o' to be already consumed. The
 * function will consume the text sequence 'utline="' before attempting to
 * parse a color. If the function fails to parse an outline color it will return
 * NULL. If the function succeeds, the previous outline color is destroyed and
 * the new one is set.
 * @param serdelizer the file accessor.
 * @param style      the style to update.
 * @param shape      the shape. Use for printing error messages.
 * @return returns true if the function parsed the parameter.
 */
bool parse_outline(serdelizer_t *serdelizer, style_t *style, char *shape);

/**
 * Attempts to parse a fill color.
 * Note that this function frees and allocates memory.
 * Note that the function expects the character 'f' to be already consumed. The
 * function will consume the text sequence 'ill="' before attempting to
 * parse a color. If the function fails to parse a fill color it will return
 * NULL. If the function succeeds, the previous fill color is destroyed and
 * the new one is set.
 * @param serdelizer the file accessor.
 * @param style      the style to update.
 * @param shape      the shape. Use for printing error messages.
 * @return returns true if the function parsed the parameter.
 */
bool parse_fill(serdelizer_t *serdelizer, style_t *style, char *shape);

/**
 * Attempts to parse translate point.
 * Note that this function frees and allocates memory.
 * Note that this function expects the character 't' to be already consumed. The
 * function will consume the text sequence 'ranslate="' brefore attempting to
 * parse a point. If the function fails to parse a translate point it will
 * return NULL. If the function succeeds, the previous translate point is
 * destroyed and a new one is set.
 * @param serdelizer the file accessor.
 * @param style      the style to update.
 * @param shape      the shape. Use for printing error messages.
 * @return returns true if the function parsed the parameter.
 */
bool parse_translate(serdelizer_t *serdelizer, style_t *style, char *shape);

/**
 * Attempts to parse rotate.
 * Note that this function frees and allocates memory.
 * Note that this function expects the character 'r' to be already consumed. The
 * function will consume the text sequence 'otate="' brefore attempting to
 * parse a rotate value. The rotate value can be 'x' / 'X' or 'y' / 'Y' or any
 * integer. If the function fails to parse a rotate it will return NULL. If the
 * function succeeds, the previous rotate is destroyed and a new one is set.
 * @param serdelizer the file accessor.
 * @param style      the style to update.
 * @param shape      the shape. Use for printing error messages.
 * @return returns true if the function parsed the parameter.
 */
bool parse_rotate(serdelizer_t *serdelizer, style_t *style, char *shape);

/**
 * Attempts to parse a style.
 * Note that this function frees and allocates memory.
 * Note that this function expects the last consummed char to be among the
 * following list : ['f', 'o', 't', 'r']. If the function fails to parse it
 * returns NULL. If the function succeeds, the previous parameter value is
 * destroyed and the new one is set.
 * @param serdelizer the file accessor.
 * @param style      the style to update.
 * @param shape      the shape. Use for printing error messages.
 * @return returns true if the function parsed the parameter.
 */
bool parse_styles(serdelizer_t *serdelizer, style_t *style, char *shape);

#endif
