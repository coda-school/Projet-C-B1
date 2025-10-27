#include "export_shape.h"
#include "../../models/shapes/shape.h"
#include "../../models/styles/style.h"
#include "../serde.h"
#include "export.h"
#include "export_path.h"
#include "export_style.h"
#include <stdio.h>

#define SHAPE_NAME_BUFFER_SIZE 500

bool export_shape_name(serdelizer_t *serdelizer, export_config_t *config,
                       char *shape_name, int depth) {
  char buffer[SHAPE_NAME_BUFFER_SIZE];
  sprintf(buffer, "<%s", shape_name);

  if (!write_spaces(serdelizer, depth * config->tab_size) ||
      !write_to_file(serdelizer, buffer)) {
    print_serdelizer_error("export_shape_name", "Could not export shape name",
                           serdelizer);
    return false;
  }

  if ((config->line_break && !write_to_file(serdelizer, "\n")) ||
      (!config->line_break && !write_to_file(serdelizer, " "))) {
    print_serdelizer_error("export_shape_name", "Could not export shape name",
                           serdelizer);
    return false;
  }

  return true;
}

bool export_inline_close_shape(serdelizer_t *serdelizer,
                               export_config_t *config, int depth) {
  if (config->line_break &&
      !write_spaces(serdelizer, depth * config->tab_size)) {
    print_serdelizer_error("export_inline_close_shape",
                           "Could not export inline close shape tag",
                           serdelizer);
    return false;
  }

  if (!write_to_file(serdelizer, "/>")) {
    print_serdelizer_error("export_inline_close_shape",
                           "Could not export inline close shape tag",
                           serdelizer);
    return false;
  }

  return true;
}

bool export_close_shape(serdelizer_t *serdelizer, export_config_t *config,
                        char *shape_name, int depth) {
  char buffer[SHAPE_NAME_BUFFER_SIZE];
  sprintf(buffer, "<%s/>", shape_name);
  if (!write_spaces(serdelizer, depth * config->tab_size) ||
      !write_to_file(serdelizer, buffer)) {
    print_serdelizer_error("export_inline_close_shape",
                           "Could not export close shape tag", serdelizer);
    return false;
  }

  return true;
}

bool export_ellipse(ellipse_t *ellipse, style_t *style,
                    serdelizer_t *serdelizer, export_config_t *config,
                    int depth) {
  if (!export_shape_name(serdelizer, config, "ellipse", depth) ||
      !export_styles(style, serdelizer, config, depth + 1) ||
      !export_int_parameter(serdelizer, config, "x", ellipse->center_x,
                            depth + 1) ||
      !export_int_parameter(serdelizer, config, "y", ellipse->center_y,
                            depth + 1) ||
      !export_int_parameter(serdelizer, config, "width", ellipse->radius_y,
                            depth + 1) ||
      !export_int_parameter(serdelizer, config, "height", ellipse->radius_x,
                            depth + 1) ||
      !export_inline_close_shape(serdelizer, config, depth)) {
    print_serdelizer_error("export_ellipse", "Could not export ellipse",
                           serdelizer);
    return false;
  }

  return true;
}

bool export_rectangle(rectangle_t *rectangle, style_t *style,
                      serdelizer_t *serdelizer, export_config_t *config,
                      int depth) {
  if (!export_shape_name(serdelizer, config, "rectangle", depth) ||
      !export_styles(style, serdelizer, config, depth + 1) ||
      !export_int_parameter(serdelizer, config, "x", rectangle->x, depth + 1) ||
      !export_int_parameter(serdelizer, config, "y", rectangle->y, depth + 1) ||
      !export_int_parameter(serdelizer, config, "width", rectangle->width,
                            depth + 1) ||
      !export_int_parameter(serdelizer, config, "height", rectangle->height,
                            depth + 1) ||
      !export_inline_close_shape(serdelizer, config, depth)) {
    print_serdelizer_error("export_rectangle", "Could not export rectangle",
                           serdelizer);
    return false;
  }

  return true;
}

bool export_line(line_t *line, style_t *style, serdelizer_t *serdelizer,
                 export_config_t *config, int depth) {
  if (!export_shape_name(serdelizer, config, "line", depth) ||
      !export_styles(style, serdelizer, config, depth + 1) ||
      !export_point_parameter(serdelizer, config, "start", line->start,
                              depth + 1) ||
      !export_point_parameter(serdelizer, config, "end", line->end,
                              depth + 1) ||
      !export_inline_close_shape(serdelizer, config, depth)) {
    print_serdelizer_error("export_line", "Could not export line", serdelizer);
    return false;
  }
  return true;
}

bool export_multiline(multiline_t *multiline, style_t *style,
                      serdelizer_t *serdelizer, export_config_t *config,
                      int depth) {
  if (!export_shape_name(serdelizer, config, "multiline", depth) ||
      !export_styles(style, serdelizer, config, depth + 1) ||
      !export_points_parameter(serdelizer, config, "points", multiline,
                               depth + 1) ||
      !export_inline_close_shape(serdelizer, config, depth)) {
    print_serdelizer_error("export_multiline", "Could not export multiline",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_polygon(polygon_t *polygon, style_t *style,
                    serdelizer_t *serdelizer, export_config_t *config,
                    int depth) {
  if (!export_shape_name(serdelizer, config, "polygon", depth) ||
      !export_styles(style, serdelizer, config, depth + 1) ||
      !export_points_parameter(serdelizer, config, "points", polygon,
                               depth + 1) ||
      !export_inline_close_shape(serdelizer, config, depth)) {
    print_serdelizer_error("export_polygon", "Could not export polygon",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_path(path_t *path, style_t *style, serdelizer_t *serdelizer,
                 export_config_t *config, int depth) {
  if (!export_shape_name(serdelizer, config, "draw", depth) ||
      !export_styles(style, serdelizer, config, depth + 1) ||
      !export_path_elements(path, serdelizer, config, depth + 1) ||
      !export_inline_close_shape(serdelizer, config, depth)) {
    print_serdelizer_error("export_path", "Could not export path", serdelizer);
    return false;
  }
  return true;
}

bool export_group(group_t *group, style_t *style, serdelizer_t *serdelizer,
                  export_config_t *config, int depth) {
  if (!export_shape_name(serdelizer, config, "group", depth) ||
      !export_styles(style, serdelizer, config, depth + 1) ||
      (config->line_break &&
       !write_spaces(serdelizer, config->tab_size * depth)) ||
      !write_to_file(serdelizer, ">\n")) {
    print_serdelizer_error("export_group", "Could not export group",
                           serdelizer);
    return false;
  }

  shape_node_t *node = group;
  while (node != NULL) {
    if (!export_shape(node->shape, serdelizer, config, depth + 1)) {
      print_serdelizer_error("export_group", "Could not export group's shapes",
                             serdelizer);
      return false;
    }
    node = node->next;
  }

  if (!export_close_shape(serdelizer, config, "group", depth)) {
    print_serdelizer_error("export_group", "Could not export group",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_shape(shape_t *shape, serdelizer_t *serdelizer,
                  export_config_t *config, int depth) {
  bool result = false;
  switch (shape->shape_variant) {

  case ELLIPSE:
    result = export_ellipse(shape->shape->ellipse, shape->styles, serdelizer,
                            config, depth);
    break;
  case RECTANGLE:
    result = export_rectangle(shape->shape->rectangle, shape->styles,
                              serdelizer, config, depth);
    break;
  case LINE:
    result = export_line(shape->shape->line, shape->styles, serdelizer, config,
                         depth);
    break;
  case MULTILINE:
    result = export_multiline(shape->shape->multiline, shape->styles,
                              serdelizer, config, depth);
    break;
  case POLYGON:
    result = export_polygon(shape->shape->polygon, shape->styles, serdelizer,
                            config, depth);
    break;
  case PATH:
    result = export_path(shape->shape->path, shape->styles, serdelizer, config,
                         depth);
    break;
  case GROUP:
    result = export_group(shape->shape->group, shape->styles, serdelizer,
                          config, depth);
    break;
  }
  result = result & write_to_file(serdelizer, "\n");

  if (!result)
    print_serdelizer_error("export_shape", "Could not export shape",
                           serdelizer);
  return result;
}
