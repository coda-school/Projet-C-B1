#include "export.h"
#include "../../models/utils/point.h"
#include "../serde.h"
#include "export_shape.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POINT_BUFFER_SIZE 500
#define POINT_PARAMETER_BUFFER_SIZE 500
#define POINTS_PARAMETER_BUFFER_SIZE 500
#define COLOR_BUFFER_SIZE 10
#define COLOR_PARAMETER_BUFFER_SIZE 500
#define INT_BUFFER_SIZE 500
#define STRING_BUFFER_SIZE 500

export_config_t *new_export_config(int tab_size, bool line_break) {

  if (tab_size <= 0) {
    fprintf(stderr,
            "[ERROR] (new_export_config) > 'tab_size' must be > 0. Got '%d'",
            tab_size);
    return NULL;
  }

  export_config_t *config = malloc(sizeof(export_config_t));
  config->tab_size = tab_size;
  config->line_break = line_break;
  return config;
}

void free_export_config(export_config_t *export_config) { free(export_config); }

bool export_point(point_t *point, serdelizer_t *serdelizer) {
  char buffer[POINT_BUFFER_SIZE];

  sprintf(buffer, "%d %d", point->x, point->y);

  if (write_to_file(serdelizer, buffer) <= 0) {
    print_serdelizer_error("export_point", "Could not export point",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_color(color_t *color, serdelizer_t *serdelizer) {
  char buffer[COLOR_BUFFER_SIZE];
  sprintf(buffer, "#%02x%02x%02x%02x", color->red, color->green, color->blue,
          color->transparent);

  if (write_to_file(serdelizer, buffer) <= 0) {
    print_serdelizer_error("export_color", "Could not export color",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_close_parameter(serdelizer_t *serdelizer, export_config_t *config) {
  if (fprintf(serdelizer->file, "\"%c", config->line_break ? '\n' : ' ') <= 0) {
    print_serdelizer_error("export_close_parameter",
                           "Could not close parameter", serdelizer);
    return false;
  }
  return true;
}

bool export_int_parameter(serdelizer_t *serdelizer, export_config_t *config,
                          char *parameter_name, int value, int depth) {
  if (config->line_break &&
      !write_spaces(serdelizer, depth * config->tab_size)) {
    print_serdelizer_error("export_point_parameter",
                           "Could not export point parameter", serdelizer);
    return false;
  }

  char buffer[INT_BUFFER_SIZE];
  sprintf(buffer, "%s=\"%d", parameter_name, value);
  if (!write_to_file(serdelizer, buffer) ||
      !export_close_parameter(serdelizer, config)) {
    print_serdelizer_error("export_int_parameter",
                           "Could not export int parameter", serdelizer);
    return false;
  }
  return true;
}

bool export_color_parameter(serdelizer_t *serdelizer, export_config_t *config,
                            char *parameter_name, color_t *color, int depth) {
  if (config->line_break &&
      !write_spaces(serdelizer, depth * config->tab_size)) {
    print_serdelizer_error("export_point_parameter",
                           "Could not export point parameter", serdelizer);
    return false;
  }

  char buffer[COLOR_PARAMETER_BUFFER_SIZE];
  sprintf(buffer, "%s=\"", parameter_name);
  if (!write_to_file(serdelizer, buffer) || !export_color(color, serdelizer) ||
      !export_close_parameter(serdelizer, config)) {
    print_serdelizer_error("export_color_parameter",
                           "Could not export color parameter", serdelizer);
    return false;
  }
  return true;
}

bool export_point_parameter(serdelizer_t *serdelizer, export_config_t *config,
                            char *parameter_name, point_t *point, int depth) {
  if (config->line_break &&
      !write_spaces(serdelizer, depth * config->tab_size)) {
    print_serdelizer_error("export_point_parameter",
                           "Could not export point parameter", serdelizer);
    return false;
  }

  char buffer[POINT_PARAMETER_BUFFER_SIZE];
  sprintf(buffer, "%s=\"", parameter_name);

  if (!write_to_file(serdelizer, buffer) || !export_point(point, serdelizer) ||
      !export_close_parameter(serdelizer, config)) {
    print_serdelizer_error("export_point_parameter",
                           "Could not export point parameter", serdelizer);
    return false;
  }
  return true;
}

bool export_points_parameter(serdelizer_t *serdelizer, export_config_t *config,
                             char *parameter_name, point_node_t *points,
                             int depth) {
  if (config->line_break &&
      !write_spaces(serdelizer, depth * config->tab_size)) {
    print_serdelizer_error("export_points_parameter",
                           "Could not export points parameter", serdelizer);
    return false;
  }

  char buffer[POINTS_PARAMETER_BUFFER_SIZE];
  sprintf(buffer, "%s=\"", parameter_name);
  if (!write_to_file(serdelizer, buffer)) {
    print_serdelizer_error("export_points_parameter",
                           "Could not export points parameter", serdelizer);
    return false;
  }

  point_node_t *node = points;
  while (node->next != NULL) {
    if (!export_point(node->point, serdelizer) ||
        !write_to_file(serdelizer, " ")) {
      print_serdelizer_error("export_points_parameter",
                             "Could not export points parameter", serdelizer);
      return false;
    }
    node = node->next;
  }

  if (!export_point(node->point, serdelizer) ||
      !export_close_parameter(serdelizer, config)) {
    print_serdelizer_error("export_points_parameter",
                           "Could not export points parameter", serdelizer);
    return false;
  }

  return true;
}

bool export_string_parameter(serdelizer_t *serdelizer, export_config_t *config,
                             char *parameter_name, char *value, int depth) {
  if (config->line_break &&
      !write_spaces(serdelizer, depth * config->tab_size)) {
    print_serdelizer_error("export_string_parameter",
                           "Could not export string parameter", serdelizer);
    return false;
  }

  char buffer[STRING_BUFFER_SIZE];
  sprintf(buffer, "%s=\"%s", parameter_name, value);

  if (!write_to_file(serdelizer, buffer) ||
      !export_close_parameter(serdelizer, config)) {
    print_serdelizer_error("export_string_parameter",
                           "Could not export string parameter", serdelizer);
    return false;
  }
  return true;
}

bool export_svg(svg_t *svg, serdelizer_t *serdelizer, export_config_t *config) {
  if (!write_to_file(serdelizer, "<svg")) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }

  if (config->line_break && (!write_to_file(serdelizer, "\n") ||
                             !write_spaces(serdelizer, 1 * config->tab_size))) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }

  if (!config->line_break && !write_to_file(serdelizer, " ")) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }
  if (!write_to_file(serdelizer, "viewport=\"")) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }
  if (!export_point(svg->viewport->start, serdelizer) ||
      !write_to_file(serdelizer, " ") ||
      !export_point(svg->viewport->end, serdelizer)) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }
  if (!write_to_file(serdelizer, "\"")) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }

  if (!write_to_file(serdelizer, ">\n")) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }

  shape_node_t *shape = svg->shapes;
  while (shape != NULL) {
    if (shape->shape == NULL)
      continue;
    if (!export_shape(shape->shape, serdelizer, config, 1)) {
      print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
      return false;
    }
    shape = shape->next;
  }

  if (!write_to_file(serdelizer, "</svg>")) {
    print_serdelizer_error("export_svg", "Could not export svg", serdelizer);
    return false;
  }
  return true;
}
