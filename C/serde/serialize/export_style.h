#ifndef CODA_EXPORT_STYLE
#define CODA_EXPORT_STYLE

#include "../../models/styles/color.h"
#include "../../models/styles/style.h"
#include "../serde.h"
#include "export.h"

/**
 * Writes down a formatted version of the given fill parameter.
 * @param style      holds the fill parameter to export.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the fill
 * parameter.
 * @return returns true if the operation succeeded.
 * @see color_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_fill(style_t *style, serdelizer_t *serdelizer,
                 export_config_t *config, int depth);

/**
 * Writes down a formatted version of the given outline parameter.
 * @param style      holds the outline parameter to export.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the outline
 * parameter.
 * @return returns true if the operation succeeded.
 * @see color_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_outline(style_t *style, serdelizer_t *serdelizer,
                    export_config_t *config, int depth);

/**
 * Writes down a formatted version of the given translate parameter.
 * @param style      holds the translate parameter to export.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the translate
 * parameter.
 * @return returns true if the operation succeeded.
 * @see translate_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_translate(style_t *style, serdelizer_t *serdelizer,
                      export_config_t *config, int depth);

/**
 * Writes down a formatted version of the given rotate parameter.
 * @param style      holds the rotate parameter to export.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the rotate
 * parameter.
 * @return returns true if the operation succeeded.
 * @see rotate_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_rotate(style_t *style, serdelizer_t *serdelizer,
                   export_config_t *config, int depth);

/**
 * Writes down a formatted version of the given styles.
 * @param style      the styles to export.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the rotate
 * parameter.
 * @return returns true if the operation succeeded.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_styles(style_t *style, serdelizer_t *serdelizer,
                   export_config_t *config, int depth);

#endif
