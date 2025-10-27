#include "export_path.h"
#include "../../models/shapes/path/path_element.h"
#include "export.h"

#define PARAMETER_STRING_BUFFER_SIZE 500

bool export_move_to(move_to_t *move_to, serdelizer_t *serdelizer) {
  if (!write_to_file(serdelizer, "M ") || !export_point(move_to, serdelizer)) {
    print_serdelizer_error("export_move_to", "Could not export move to",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_line_to(line_to_t *line_to, serdelizer_t *serdelizer) {
  if (!write_to_file(serdelizer, "L ") || !export_point(line_to, serdelizer)) {
    print_serdelizer_error("export_line_to", "Could not export line to",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_horizontal_line_to(horizontal_line_to_t *horizontal_line_to,
                               serdelizer_t *serdelizer) {
  char buffer[PARAMETER_STRING_BUFFER_SIZE];
  sprintf(buffer, "H %d", *horizontal_line_to);
  if (!write_to_file(serdelizer, buffer)) {
    print_serdelizer_error("export_horizontal_line_to",
                           "Could not export horizontal line to", serdelizer);
    return false;
  }
  return true;
}

bool export_vertical_line_to(vertical_line_to_t *vertical_line_to,
                             serdelizer_t *serdelizer) {
  char buffer[PARAMETER_STRING_BUFFER_SIZE];
  sprintf(buffer, "V %d", *vertical_line_to);
  if (!write_to_file(serdelizer, buffer)) {
    print_serdelizer_error("export_vertical_line_to",
                           "Could not export vertical line to", serdelizer);
    return false;
  }
  return true;
}

bool export_end_of_path(end_path_t *end_of_path, serdelizer_t *serdelizer) {
  if (!write_to_file(serdelizer, "Z")) {
    print_serdelizer_error("export_end_of_path", "Could not export end of path",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_cubic_curve_to(cubic_curve_to_t *cubic_curve_to,
                           serdelizer_t *serdelizer) {
  if (!write_to_file(serdelizer, "C ") ||
      !export_point(cubic_curve_to->control_point_1, serdelizer) ||
      !write_to_file(serdelizer, " ") ||
      !export_point(cubic_curve_to->control_point_2, serdelizer) ||
      !write_to_file(serdelizer, " ") ||
      !export_point(cubic_curve_to->end, serdelizer)) {
    print_serdelizer_error("export_cubic_curve_to",
                           "Could not export cubic curve to", serdelizer);
    return false;
  }
  return true;
}

bool export_cubic_curve_to_shorthand(
    shorthand_cubic_curve_to_t *shorthand_cubic_curve_to,
    serdelizer_t *serdelizer) {
  if (!write_to_file(serdelizer, "S ") ||
      !export_point(shorthand_cubic_curve_to->control_point, serdelizer) ||
      !write_to_file(serdelizer, " ") ||
      !export_point(shorthand_cubic_curve_to->end, serdelizer)) {
    print_serdelizer_error("export_cubic_curve_to_shorthand",
                           "Could not export cubic curve to shorthand",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to,
                               serdelizer_t *serdelizer) {
  if (!write_to_file(serdelizer, "Q ") ||
      !export_point(quadratic_curve_to->control_point, serdelizer) ||
      !write_to_file(serdelizer, " ") ||
      !export_point(quadratic_curve_to->end, serdelizer)) {
    print_serdelizer_error("export_quadratic_curve_to",
                           "Could not export quadratic curve to", serdelizer);
    return false;
  }
  return true;
}

bool export_quadratic_curve_to_shorthand(
    shorthand_quadratic_curve_to_t *shorthand_quadratic_curve_to,
    serdelizer_t *serdelizer) {
  if (!write_to_file(serdelizer, "T ") ||
      !export_point(shorthand_quadratic_curve_to, serdelizer)) {
    print_serdelizer_error("export_quadratic_curve_to_shorthand",
                           "Could not export quadratic curve to shorthand",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_path_element(path_element_t *path_element,
                         serdelizer_t *serdelizer) {
  bool export_result = false;
  switch (path_element->path_element_variant) {
  case MOVE_TO:
    export_result =
        export_move_to(path_element->path_element->move_to, serdelizer);
    break;
  case LINE_TO:
    export_result =
        export_line_to(path_element->path_element->line_to, serdelizer);
    break;
  case VERTICAL_LINE_TO:
    export_result = export_vertical_line_to(
        &path_element->path_element->vertical_line_to, serdelizer);
    break;
  case HORIZONTAL_LINE_TO:
    export_result = export_horizontal_line_to(
        &path_element->path_element->horizontal_line_to, serdelizer);
    break;
  case END_PATH:
    export_result =
        export_end_of_path(path_element->path_element->end_path, serdelizer);
    break;
  case CUBIC_CURVE_TO:
    export_result = export_cubic_curve_to(
        path_element->path_element->cubic_curve_to, serdelizer);
    break;
  case CUBIC_CURVE_TO_SHORTHAND:
    export_result = export_cubic_curve_to_shorthand(
        path_element->path_element->shorthand_cubic_curve_to, serdelizer);
    break;
  case QUADRATIC_CURVE_TO:
    export_result = export_quadratic_curve_to(
        path_element->path_element->quadratic_curve_to, serdelizer);
    break;
  case QUADRATIC_CURVE_TO_SHORTHAND:
    export_result = export_quadratic_curve_to_shorthand(
        path_element->path_element->shorthand_quadratic_curve_to, serdelizer);
    break;
  }

  if (!export_result) {
    print_serdelizer_error("export_path_element",
                           "Could not export path element", serdelizer);
    return false;
  }
  return true;
}

bool export_path_elements(path_element_node_t *path_elements,
                          serdelizer_t *serdelizer, export_config_t *config,
                          int depth) {
  if (config->line_break &&
      !write_spaces(serdelizer, config->tab_size * depth)) {
    print_serdelizer_error("export_path_elements",
                           "Could not export path elements", serdelizer);
    return false;
  }

  if (!write_to_file(serdelizer, "data=\"")) {
    print_serdelizer_error("export_path_elements",
                           "Could not export path elements", serdelizer);
    return false;
  }

  path_element_node_t *node = path_elements;
  while (node->next != NULL) {
    if (!export_path_element(node->element, serdelizer) ||
        !write_to_file(serdelizer, " ")) {
      print_serdelizer_error("export_path_elements",
                             "Could not export path elements", serdelizer);
      return false;
    }
    node = node->next;
  }

  if (!export_path_element(node->element, serdelizer) ||
      !write_to_file(serdelizer, "\"")) {
    print_serdelizer_error("export_path_elements",
                           "Could not export path elements", serdelizer);
    return false;
  }

  if ((config->line_break && !write_to_file(serdelizer, "\n")) ||
      (!config->line_break && !write_to_file(serdelizer, " "))) {
    print_serdelizer_error("export_path_elements",
                           "Could not export path elements", serdelizer);
    return false;
  }

  return true;
}
