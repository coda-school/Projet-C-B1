#include "export_style.h"
#include "../../models/styles/rotate.h"
#include "../../models/styles/style.h"
#include "../serde.h"
#include "export.h"
#include <stdbool.h>

bool export_fill(style_t *style, serdelizer_t *serdelizer,
                 export_config_t *config, int depth) {
  if (!export_color_parameter(serdelizer, config, "fill", style->fill, depth)) {
    print_serdelizer_error("export_fill", "Could not export fill parameter",
                           serdelizer);
    return false;
  }
  return true;
}

bool export_outline(style_t *style, serdelizer_t *serdelizer,
                    export_config_t *config, int depth) {
  if (!export_color_parameter(serdelizer, config, "outline", style->fill,
                              depth)) {
    print_serdelizer_error("export_outline",
                           "Could not export outline parameter", serdelizer);
    return false;
  }
  return true;
}

bool export_translate(style_t *style, serdelizer_t *serdelizer,
                      export_config_t *config, int depth) {
  if (!export_point_parameter(serdelizer, config, "translate", style->translate,
                              depth)) {
    print_serdelizer_error("export_translate",
                           "Could not export translate parameter", serdelizer);
    return false;
  }
  return true;
}

bool export_rotate(style_t *style, serdelizer_t *serdelizer,
                   export_config_t *config, int depth) {
  rotation_variants_t variant = style->rotate->variant;

  switch (variant) {
  case FLIP_X:
  case FLIP_Y:
    if (!export_string_parameter(serdelizer, config, "rotate",
                                 variant == FLIP_X ? "X" : "Y", depth)) {
      print_serdelizer_error("export_rotate",
                             "Could not export rotate parameter", serdelizer);
      return false;
    }
    return true;
    break;

  case CIRCULAR:
    if (!export_int_parameter(serdelizer, config, "rotate",
                              style->rotate->rotation.circular, depth)) {
      print_serdelizer_error("export_rotate",
                             "Could not export rotate parameter", serdelizer);
      return false;
    }
    return true;
    break;
  }

  print_serdelizer_error(
      "export_rotate", "Could not export rotate. Unmatch variant", serdelizer);
  return false;
}

bool export_styles(style_t *style, serdelizer_t *serdelizer,
                   export_config_t *config, int depth) {
  if (!export_fill(style, serdelizer, config, depth) ||
      !export_outline(style, serdelizer, config, depth) ||
      !export_translate(style, serdelizer, config, depth) ||
      !export_rotate(style, serdelizer, config, depth)) {
    print_serdelizer_error("export_styles", "Could not export sytles",
                           serdelizer);
    return false;
  }

  return true;
}
