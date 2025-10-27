#ifndef CODA_EXPORT_SHAPE
#define CODA_EXPORT_SHAPE

#include "../../models/shapes/ellipse.h"
#include "../../models/shapes/shape.h"
#include "../../models/styles/style.h"
#include "../serde.h"
#include "export.h"
#include "export_style.h"

/**
 * Writes down the given shape's open tag.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param shape_name the shape's name.
 * @param depth      the amount of spacing to write before writing the shape's
 * open tag.
 * @return returns true if the operation succeeded.
 * @see export_config_t.
 * @see serdelizer.
 */
bool export_shape_name(serdelizer_t *serdelizer, export_config_t *config,
                       char *shape_name, int depth);

/**
 * Writes down an inline close shape tag.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the shape
 * inline close tag.
 * @return returns true if the operation succeeded.
 * @see export_config_t.
 * @see serdelizer.
 */
bool export_inline_close_shape(serdelizer_t *serdelizer,
                               export_config_t *config, int depth);

/**
 * Writes down the shape's close tag.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param shape_name the shape's name.
 * @param depth      the amount of spacing to write before writing the shape
 * inline close tag.
 * @return returns true if the operation succeeded.
 * @see export_config_t.
 * @see serdelizer.
 */
bool export_close_shape(serdelizer_t *serdelizer, export_config_t *config,
                        char *shape_name, int depth);

/**
 * Writes down the given ellipse.
 * @param ellipse    the ellipse to export.
 * @param style      the ellipse's style.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the ellipse.
 * @return returns true if the operation suceeded.
 * @see ellipse_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_ellipse(ellipse_t *ellipse, style_t *style,
                    serdelizer_t *serdelizer, export_config_t *config,
                    int depth);

/**
 * Writes down the given rectangle.
 * @param rectangle  the rectangle to export.
 * @param style      the rectangle's style.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the
 * rectangle.
 * @return returns true if the operation suceeded.
 * @see rectangle_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_rectangle(rectangle_t *rectangle, style_t *style,
                      serdelizer_t *serdelizer, export_config_t *config,
                      int depth);

/**
 * Writes down the given line.
 * @param line       the line to export.
 * @param style      the line's style.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the line.
 * @return returns true if the operation suceeded.
 * @see line_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_line(line_t *line, style_t *style, serdelizer_t *serdelizer,
                 export_config_t *config, int depth);

/**
 * Writes down the given multiline.
 * @param multiline  the multiline to export.
 * @param style      the multiline's style.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the
 * multiline.
 * @return returns true if the operation suceeded.
 * @see multiline_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_multiline(multiline_t *multiline, style_t *style,
                      serdelizer_t *serdelizer, export_config_t *config,
                      int depth);

/**
 * Writes down the given polygon.
 * @param polygon    the polygon to export.
 * @param style      the polygon's style.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the polygon.
 * @return returns true if the operation suceeded.
 * @see polygon_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_polygon(polygon_t *polygon, style_t *style,
                    serdelizer_t *serdelizer, export_config_t *config,
                    int depth);

/**
 * Writes down the given path.
 * @param path       the path to export.
 * @param style      the path's style.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the path.
 * @return returns true if the operation suceeded.
 * @see path_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_path(path_t *path, style_t *style, serdelizer_t *serdelizer,
                 export_config_t *config, int depth);

/**
 * Writes down the given group.
 * @param group      the group to export.
 * @param style      the group's style.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param depth      the amount of spacing to write before writing the group.
 * @return returns true if the operation suceeded.
 * @see group_t.
 * @see style_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_group(group_t *group, style_t *style, serdelizer_t *serdelizer,
                  export_config_t *config, int depth);

/**
 * Writes down the given shape.
 * @param shape      the shape to export.
 * @param serdelizer the file accessor.
 * @param config     the export configs.
 * @param            the amount of spacing to write before writing the shape.
 * @return returns true if the operation succeeded.
 * @see shape_t.
 * @see export_config_t.
 * @see serdelizer_t.
 */
bool export_shape(shape_t *shape, serdelizer_t *serdelizer,
                  export_config_t *config, int depth);

#endif
