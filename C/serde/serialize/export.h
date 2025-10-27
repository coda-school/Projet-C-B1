#ifndef CODA_EXPORT
#define CODA_EXPORT

#include "../../models/shapes/svg.h"
#include "../../models/styles/color.h"
#include "../../models/utils/point.h"
#include "../serde.h"
#include <stdbool.h>

/**
 * Defines the export config type.
 * @param tab_size   the number of spaces per tab.
 * @param line_break indicates if the programs creates a new line for each
 * parameter.
 */
typedef struct export_config_s {
  unsigned int tab_size;
  bool line_break;
} export_config_t;

/**
 * Creates a new export config.
 * Note that this function allocates memory.
 * @param tab_size   the number of spaces per tab.
 * @param line_break indicates if the programs creates a new line for each
 * parameter.
 * @return returns the new export config's pointer.
 * @see export_config_t.
 */
export_config_t *new_export_config(int tab_size, bool line_break);

/**
 * Destroys the given export config.
 * Note that this function frees memory.
 * @param export_config the configs to destroy.
 * @see export_config_t.
 */
void free_export_config(export_config_t *export_config);

/**
 * Writes down the given point.
 * @param point      the point to export.
 * @param serdelizer the file accessor.
 * @return returns true if the operation succeeded.
 * @see point_t.
 * @see serdelizer_t.
 */
bool export_point(point_t *point, serdelizer_t *serdelizer);

/**
 * Writes down the given color.
 * @param color      the color to export.
 * @param serdelizer the file accessor.
 * @return returns true if the operation succeeded.
 * @see color_t.
 * @see serdelizer_t.
 */
bool export_color(color_t *color, serdelizer_t *serdelizer);

/**
 * Closes the written parameter.
 * The function writes down the config matching whitespace ('\n' or ' ').
 * @param serdelizer      the file accessor.
 * @param export_config_t the export configs.
 * @return returns true if the operation succeeded.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_close_parameter(serdelizer_t *serdelizer, export_config_t *config);

/**
 * Writes down an integer parameter.
 * The function writes down the parameter's name and its value.
 * @param serdelizer     the file accessor.
 * @param config         the export configs.
 * @param parameter_name the parameter's name.
 * @param value          the value to export.
 * @param                the amount of spacing to write before writing the
 * parameter.
 * @return returns true if the operation succeeded.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_int_parameter(serdelizer_t *serdelizer, export_config_t *config,
                          char *parameter_name, int value, int depth);

/**
 * Writes down a color parameter.
 * The function writes down the parameter's name and its value.
 * @param serdelizer     the file accessor.
 * @param config         the export configs.
 * @param parameter_name the parameter's name.
 * @param color          the color to export.
 * @param                the amount of spacing to write before writing the
 * parameter.
 * @return returns true if the operation succeeded.
 * @see color_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_color_parameter(serdelizer_t *serdelizer, export_config_t *config,
                            char *parameter_name, color_t *color, int depth);

/**
 * Writes down a point parameter.
 * The function writes down the parameter's name and its value.
 * @param serdelizer     the file accessor.
 * @param config         the export configs.
 * @param parameter_name the parameter's name.
 * @param point          the point to export.
 * @param                the amount of spacing to write before writing the
 * parameter.
 * @return returns true if the operation succeeded.
 * @see point_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_point_parameter(serdelizer_t *serdelizer, export_config_t *config,
                            char *parameter_name, point_t *point, int depth);

/**
 * Writes down a point linked list parameter.
 * The function writes down the parameter's name and its value.
 * @param serdelizer     the file accessor.
 * @param config         the export configs.
 * @param parameter_name the parameter's name.
 * @param points         the point linked list to export.
 * @param                the amount of spacing to write before writing the
 * parameter.
 * @return returns true if the operation succeeded.
 * @see point_t.
 * @see point_node_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_points_parameter(serdelizer_t *serdelizer, export_config_t *config,
                             char *parameter_name, point_node_t *points,
                             int depth);

/**
 * Writes down a string parameter.
 * The function writes down the parameter's name and its value.
 * @param serdelizer     the file accessor.
 * @param config         the export configs.
 * @param parameter_name the parameter's name.
 * @param string          the string to export.
 * @param                the amount of spacing to write before writing the
 * parameter.
 * @return returns true if the operation succeeded.
 * @see string_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_string_parameter(serdelizer_t *serdelizer, export_config_t *config,
                             char *parameter_name, char *value, int depth);

/**
 * Writes down the given svg.
 * @param svg        the svg to export.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @return returns true if the operation succeeded.
 * @see svg_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_svg(svg_t *svg, serdelizer_t *serdelizer, export_config_t *config);

#endif
