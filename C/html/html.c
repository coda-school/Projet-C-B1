#include "html.h"
#include <stdio.h>

#define HTML_FILE_START                                                        \
  "<!DOCTYPE html>\n\
<html lang=\"en\">\n\
  <head>\n\
    <meta charset=\"utf-8\" />\n\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n\
    <style>\n\
      * {\n\
        margin: 0;\n\
        padding: 0;\n\
      }\n\
      \n\
      svg {\n\
        width: 100vw;\n\
        width: 100dvw;\n\
        height: 100vh;\n\
        height: 100dvh;\n\
      }\n\
    </style>\n\
  </head>\n\
  <body>\n"

#define HTML_FILE_END                                                          \
  "\t</body>\n\
</html>"

void export_tabs_html(FILE *file, unsigned int amount) {
  for (int _ = 0; _ < amount; _++)
    fprintf(file, "\t");
}

void export_styles_html(FILE *file, style_t *styles) {
  fprintf(file, "stroke=\"rgba(%d, %d, %d, %d)\" ", styles->outline->red,
          styles->outline->green, styles->outline->blue,
          styles->outline->transparent);
  fprintf(file, "fill=\"rgba(%d, %d, %d, %d)\" ", styles->fill->red,
          styles->fill->green, styles->fill->blue, styles->fill->transparent);
  fprintf(file, "transform=\"translate(%d, %d) ", styles->translate->x,
          styles->translate->y);
  switch (styles->rotate->variant) {
  case FLIP_X:
    fprintf(file, "rotateX(180)\" ");
    break;
  case FLIP_Y:
    fprintf(file, "rotateY(180)\" ");
    break;
  case CIRCULAR:
    fprintf(file, "rotate(%d)\" ", styles->rotate->rotation.circular);
    break;
  }
}

void export_points_html(FILE *file, point_node_t *points) {
  point_node_t *node = points;
  if (node == NULL)
    return;
  while (node->next != NULL) {
    fprintf(file, "%d,%d ", node->point->x, node->point->y);
    node = node->next;
  }
  fprintf(file, "%d,%d", node->point->x, node->point->y);
}

void export_path_element_html(FILE *file, path_element_t *element) {
  switch (element->path_element_variant) {
  case MOVE_TO:
    fprintf(file, "M %d %d", element->path_element->move_to->x,
            element->path_element->move_to->y);
    break;
  case LINE_TO:
    fprintf(file, "L %d %d", element->path_element->line_to->x,
            element->path_element->line_to->y);
    break;
  case VERTICAL_LINE_TO:
    fprintf(file, "V %d", element->path_element->vertical_line_to);
    break;
  case HORIZONTAL_LINE_TO:
    fprintf(file, "H %d", element->path_element->horizontal_line_to);
    break;
  case END_PATH:
    fprintf(file, "Z");
    break;
  case CUBIC_CURVE_TO:
    fprintf(file, "C %d %d %d %d %d %d",
            element->path_element->cubic_curve_to->control_point_1->x,
            element->path_element->cubic_curve_to->control_point_1->y,
            element->path_element->cubic_curve_to->control_point_2->x,
            element->path_element->cubic_curve_to->control_point_2->y,
            element->path_element->cubic_curve_to->end->x,
            element->path_element->cubic_curve_to->end->y);
    break;
  case CUBIC_CURVE_TO_SHORTHAND:
    fprintf(file, "S %d %d %d %d",
            element->path_element->shorthand_cubic_curve_to->control_point->x,
            element->path_element->shorthand_cubic_curve_to->control_point->y,
            element->path_element->shorthand_cubic_curve_to->end->x,
            element->path_element->shorthand_cubic_curve_to->end->y);
    break;
  case QUADRATIC_CURVE_TO:
    fprintf(file, "Q %d %d %d %d",
            element->path_element->quadratic_curve_to->control_point->x,
            element->path_element->quadratic_curve_to->control_point->y,
            element->path_element->quadratic_curve_to->end->x,
            element->path_element->quadratic_curve_to->end->y);
    break;
  case QUADRATIC_CURVE_TO_SHORTHAND:
    fprintf(file, "T %d %d",
            element->path_element->shorthand_quadratic_curve_to->x,
            element->path_element->shorthand_quadratic_curve_to->y);
    break;
  }
}

void export_path_elements_html(FILE *file, path_element_node_t *elements) {
  path_element_node_t *node = elements;
  if (node == NULL)
    return;
  while (node->next != NULL) {
    export_path_element_html(file, node->element);
    fprintf(file, " ");
    node = node->next;
  }
  export_path_element_html(file, node->element);
}

void export_shapes_html(FILE *file, shape_node_t *shapes, unsigned int depth) {
  shape_node_t *node = shapes;
  if (node == NULL)
    return;
  while (node != NULL) {
    export_shape_html(file, node->shape, depth);
    node = node->next;
  }
}

void export_shape_html(FILE *file, shape_t *shape, unsigned int depth) {
  export_tabs_html(file, depth);
  switch (shape->shape_variant) {
  case ELLIPSE:
    fprintf(file, "<ellipse cx=\"%d\" cy=\"%d\" rx=\"%d\" ry=\"%d\" ",
            shape->shape->ellipse->center_x, shape->shape->ellipse->center_y,
            shape->shape->ellipse->radius_x, shape->shape->ellipse->radius_y);
    export_styles_html(file, shape->styles);
    fprintf(file, " />\n");
    break;
  case RECTANGLE:
    fprintf(file, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" ",
            shape->shape->rectangle->x, shape->shape->rectangle->y,
            shape->shape->rectangle->width, shape->shape->rectangle->height);
    export_styles_html(file, shape->styles);
    fprintf(file, " />\n");
    break;
  case LINE:
    fprintf(file, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" ",
            shape->shape->line->start->x, shape->shape->line->start->y,
            shape->shape->line->end->x, shape->shape->line->end->y);
    export_styles_html(file, shape->styles);
    fprintf(file, " />\n");
    break;
  case MULTILINE:
    fprintf(file, "<polyline points=\"");
    export_points_html(file, shape->shape->multiline);
    fprintf(file, "\" ");
    export_styles_html(file, shape->styles);
    fprintf(file, " />\n");
    break;
  case POLYGON:
    fprintf(file, "<polygon points=\"");
    export_points_html(file, shape->shape->multiline);
    fprintf(file, "\" ");
    export_styles_html(file, shape->styles);
    fprintf(file, " />\n");
    break;
  case PATH:
    fprintf(file, "<path d=\"");
    export_path_elements_html(file, shape->shape->path);
    fprintf(file, "\" ");
    export_styles_html(file, shape->styles);
    fprintf(file, " />\n");
    break;
  case GROUP:
    fprintf(file, "<g ");
    export_styles_html(file, shape->styles);
    fprintf(file, ">\n");
    export_shapes_html(file, shape->shape->group, depth + 1);
    export_tabs_html(file, depth);
    fprintf(file, "</g>\n");
    break;
  }
}

bool export_to_html(svg_t *svg, char *path) {
  FILE *file = fopen(path, "w");
  if (file == NULL)
    return false;
  fprintf(file, HTML_FILE_START);
  fprintf(file, "\t\t<svg viewport=\"%d %d %d %d\">\n", svg->viewport->start->x,
          svg->viewport->start->y, svg->viewport->end->x,
          svg->viewport->end->y);
  export_shapes_html(file, svg->shapes, 3);
  fprintf(file, "\t\t</svg>\n");
  fprintf(file, HTML_FILE_END);
  fclose(file);
  return true;
}
