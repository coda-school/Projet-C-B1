#include "cli_shape.h"
#include "../models/shapes/ellipse.h"
#include "../models/shapes/group.h"
#include "../models/shapes/line.h"
#include "../models/shapes/multiline.h"
#include "../models/shapes/path/path.h"
#include "../models/shapes/polygon.h"
#include "../models/shapes/rectangle.h"
#include "../models/shapes/shape.h"
#include "../utils/utils.h"
#include "cli.h"
#include "cli_path.h"
#include "cli_style.h"
#include <stdio.h>
#include <stdlib.h>

#define POINT_BUFFER_SIZE 150

void cli_print_ellipse(ellipse_t *ellipse, style_t *styles, int depth) {
  cli_print_spaces(depth);
  fprintf(stdout, "<ellipse x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" ",
          ellipse->center_x, ellipse->center_y, ellipse->radius_x,
          ellipse->radius_y);
  cli_display_style(styles);
  cli_print_content("/>\n");
}

void cli_print_rectangle(rectangle_t *rectangle, style_t *styles, int depth) {
  cli_print_spaces(depth);
  fprintf(stdout, "<rectangle x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" ",
          rectangle->x, rectangle->y, rectangle->width, rectangle->height);
  cli_display_style(styles);
  cli_print_content("/>\n");
}

void cli_print_line(line_t *line, style_t *styles, int depth) {
  cli_print_spaces(depth);
  fprintf(stdout, "<line start=\"%d %d\" end=\"%d %d\" ", line->start->x,
          line->start->y, line->end->x, line->end->y);
  cli_display_style(styles);
  cli_print_content("/>\n");
}

void cli_print_multiline(multiline_t *multiline, style_t *styles, int depth) {
  cli_print_spaces(depth);
  cli_print_content("<multiline points=\"");
  point_node_t *point = multiline;
  if (point == NULL) {
    cli_print_content("\" />\n");
    return;
  }
  while (point->next != NULL) {
    fprintf(stdout, "(%d %d) ", point->point->x, point->point->y);
    point = point->next;
  }
  if (point != NULL)
    fprintf(stdout, "(%d, %d)\" ", point->point->x, point->point->y);
  cli_display_style(styles);
  cli_print_content("/>\n");
}

void cli_print_polygon(polygon_t *polygon, style_t *styles, int depth) {
  cli_print_spaces(depth);
  cli_print_content("<polygon points=\"");
  point_node_t *point = polygon;
  if (point == NULL) {
    cli_print_content("\" />\n");
    return;
  }

  while (point->next != NULL) {
    fprintf(stdout, "(%d %d) ", point->point->x, point->point->y);
    point = point->next;
  }
  if (point != NULL)
    fprintf(stdout, "(%d, %d)\" ", point->point->x, point->point->y);
  cli_display_style(styles);
  cli_print_content("/>\n");
}

void cli_print_path(path_t *path, style_t *styles, int depth) {
  cli_print_spaces(depth);
  cli_print_content("<path d=\"");
  path_element_node_t *element = path;
  if (element == NULL) {
    cli_print_content("\" />\n");
    return;
  }

  while (element->next != NULL) {
    cli_print_path_element(element->element);
    fprintf(stdout, " ");
    element = element->next;
  }
  if (element != NULL)
    cli_print_path_element(element->element);
  fprintf(stdout, "\" ");
  cli_display_style(styles);
  cli_print_content("/>\n");
}

void cli_print_group(group_t *group, style_t *styles, int depth) {
  cli_print_spaces(depth);
  cli_print_content("<group ");
  cli_display_style(styles);
  cli_print_content(">\n");

  shape_node_t *shape = group;
  if (shape == NULL) {
    cli_print_spaces(depth);
    cli_print_content("</group>\n");
    return;
  }

  while (shape != NULL) {
    cli_print_shape(shape->shape, depth + 1);
    shape = shape->next;
  }
  cli_print_spaces(depth);
  cli_print_content("</group>\n");
}

void cli_print_shape(shape_t *shape, int depth) {
  switch (shape->shape_variant) {
  case ELLIPSE:
    cli_print_ellipse(shape->shape->ellipse, shape->styles, depth);
    break;
  case RECTANGLE:
    cli_print_rectangle(shape->shape->rectangle, shape->styles, depth);
    break;
  case LINE:
    cli_print_line(shape->shape->line, shape->styles, depth);
    break;
  case MULTILINE:
    cli_print_multiline(shape->shape->multiline, shape->styles, depth);
    break;
  case POLYGON:
    cli_print_polygon(shape->shape->polygon, shape->styles, depth);
    break;
  case PATH:
    cli_print_path(shape->shape->path, shape->styles, depth);
    break;
  case GROUP:
    cli_print_group(shape->shape->group, shape->styles, depth);
    break;
  }
}

void cli_edit_ellipse(ellipse_t *ellipse) {
  int n;
  char *text = ellipse_to_string(ellipse);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the ellipse's X coordinate.\n",
                                "Enter a valid interger\n", NULL, true, &n))
    ellipse->center_x = n;
  free(text);

  text = ellipse_to_string(ellipse);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the ellipse's Y coordinate.\n",
                                "Enter a valid interger\n", NULL, true, &n))
    ellipse->center_y = n;
  free(text);

  text = ellipse_to_string(ellipse);
  if (CLI_VALID == cli_ask_for_int_parameter(
                       text, "Select the ellipse's width coordinate.\n",
                       "Enter a valid interger > 0\n", must_be_strict_positive,
                       true, &n))
    ellipse->radius_x = n;
  free(text);

  text = ellipse_to_string(ellipse);
  if (CLI_VALID == cli_ask_for_int_parameter(
                       text, "Select the ellipse's height coordinate.\n",
                       "Enter a valid interger > 0\n", must_be_strict_positive,
                       true, &n))
    ellipse->radius_y = n;
  free(text);
}

void cli_edit_rectangle(rectangle_t *rectangle) {
  int n;
  char *text = rectangle_to_string(rectangle);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the rectangle's X coordinate.\n",
                                "Enter a valid interger\n", NULL, true, &n))
    rectangle->x = n;
  free(text);

  text = rectangle_to_string(rectangle);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the rectangle's Y coordinate.\n",
                                "Enter a valid interger\n", NULL, true, &n))
    rectangle->y = n;
  free(text);

  text = rectangle_to_string(rectangle);
  if (CLI_VALID == cli_ask_for_int_parameter(text,
                                             "Select the rectangle's width.\n",
                                             "Enter a valid interger > 0\n",
                                             must_be_strict_positive, true, &n))
    rectangle->width = n;
  free(text);

  text = rectangle_to_string(rectangle);
  if (CLI_VALID == cli_ask_for_int_parameter(text,
                                             "Select the rectangle's height.\n",
                                             "Enter a valid interger > 0\n",
                                             must_be_strict_positive, true, &n))
    rectangle->height = n;
  free(text);
}

void cli_edit_line(line_t *line) {
  int n;
  char *text = line_to_string(line);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the line's start X coordinate.\n",
                                "Enter a valid interger\n", NULL, true, &n))
    line->start->x = n;
  free(text);

  text = line_to_string(line);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the line's start Y coordinate.\n",
                                "Enter a valid interger\n", NULL, true, &n))
    line->start->y = n;
  free(text);

  text = line_to_string(line);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the line's end X coordinate.\n",
                                "Enter a valid interger > 0\n", NULL, true, &n))
    line->end->x = n;
  free(text);

  text = line_to_string(line);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the line's end Y coordinate.\n",
                                "Enter a valid interger > 0\n", NULL, true, &n))
    line->end->y = n;
  free(text);
}

void cli_edit_point(point_t *point) {
  char buffer[POINT_BUFFER_SIZE];
  sprintf(buffer, "Point X=%d Y=%d", point->x, point->y);
  int n;
  if (CLI_VALID ==
      cli_ask_for_int_parameter(buffer, "Select the point's X coordinate.\n",
                                "Enter a valid integer.\n", NULL, true, &n))
    point->x = n;
  sprintf(buffer, "Point X=%d Y=%d", point->x, point->y);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(buffer, "Select the point's Y coordinate.\n",
                                "Enter a valid integer.\n", NULL, true, &n))
    point->y = n;
}

void cli_add_point(point_node_t **points) {
  int length = get_point_node_length(*points), index;
  if (cli_ask_for_point_index("Select the index for the new point.\n", *points,
                              &index, true, true) != CLI_VALID)
    return;
  point_t *point = new_point(0, 0);
  cli_edit_point(point);
  if (index < 0 || index > length) {
    free_point(point);
    return;
  } else if (index == length)
    *points = push_point_node(*points, point);
  else
    *points = insert_point_node_at(*points, index, point);
}

void cli_remove_point(point_node_t **points) {
  int index;
  if (cli_ask_for_point_index("Select the point's index to remove.\n", *points,
                              &index, true, false) != CLI_VALID)
    return;
  *points = remove_point_node_at(*points, index);
}

void cli_edit_points(point_node_t *points) {
  int index;
  if (cli_ask_for_point_index("Select the point's index to edit.\n", points,
                              &index, true, false) != CLI_VALID)
    return;
  int i = 0;
  point_node_t *point = points;
  while (point != NULL) {
    if (i == index)
      break;
    point = point->next;
    i++;
  }
  if (i != index || point == NULL)
    return;
  cli_edit_point(point->point);
}

void cli_edit_multiline(multiline_t **multiline, style_t *styles) {
  bool error = false;
  int opt;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_multiline(*multiline, styles, 0);
    cli_print_content("Select action to perform :\n");
    cli_print_content("- Add point (1)\n");
    cli_print_content("- Edit point (2)\n");
    cli_print_content("- Remove point (3)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");
    output = cli_ask_for_int(&opt);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }
    switch (opt) {
    case 1:
      cli_add_point(multiline);
      error = false;
      break;
    case 2:
      cli_edit_points(*multiline);
      error = false;
      break;
    case 3:
      cli_remove_point(multiline);
      error = false;
      break;
    default:
      error = true;
      break;
    }
  }
}

void cli_edit_polygon(polygon_t **polygon, style_t *styles) {
  bool error = false;
  int opt;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_polygon(*polygon, styles, 0);
    cli_print_content("Select action to perform :\n");
    cli_print_content("- Add point (1)\n");
    cli_print_content("- Edit point (2)\n");
    cli_print_content("- Remove point (3)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");
    output = cli_ask_for_int(&opt);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }
    switch (opt) {
    case 1:
      cli_add_point(polygon);
      break;
    case 2:
      cli_edit_points(*polygon);
      break;
    case 3:
      cli_remove_point(polygon);
      break;
    default:
      error = true;
      break;
    }
  }
}

void cli_add_path_element(path_element_node_t **elements) {
  int length = get_path_element_node_length(*elements), index;
  if (cli_ask_for_path_element_index(
          "Select the index for the new path element.\n", *elements, &index,
          true, true) != CLI_VALID)
    return;
  path_element_t *element = cli_new_path_element();
  if (element == NULL)
    return;
  cli_edit_path_element(element);
  if (index < 0 || index > length) {
    free_path_element(element);
    return;
  } else if (index == length)
    *elements = push_path_element_node(*elements, element);
  else {
    *elements = insert_path_element_node_at(*elements, index, element);
  }
}

void cli_remove_path_element(path_element_node_t **elements) {
  cli_clear_screen();
  int index;
  if (cli_ask_for_path_element_index(
          "Select the path element's index to delete.\n", *elements, &index,
          true, false) != CLI_VALID)
    return;
  *elements = remove_path_element_node_at(*elements, index);
}

void cli_edit_path_elements(path_element_node_t *elements) {
  int index, i = 0;
  if (cli_ask_for_path_element_index(
          "Select the path element's index to edit.\n", elements, &index, true,
          false) != CLI_VALID)
    return;
  path_element_node_t *element = elements;
  while (element != NULL && i < index) {
    element = element->next;
    i++;
  }
  if (i != index || element == NULL)
    return;
  cli_edit_path_element(element->element);
}

void cli_edit_path(path_t **path, style_t *styles) {
  bool error = false;
  int d;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_path(*path, styles, 0);
    cli_print_content("Select action to perform :\n");
    cli_print_content("- Add path element (1)\n");
    cli_print_content("- Edit path element (2)\n");
    cli_print_content("- Remove path element (3)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");
    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    switch (d) {
    case 1:
      cli_add_path_element(path);
      break;
    case 2:
      cli_edit_path_elements(*path);
      break;
    case 3:
      cli_remove_path_element(path);
      break;
    default:
      error = true;
      break;
    }
  }
}

void cli_add_shape(shape_node_t **shapes, style_t *inherited_styles) {
  int length = get_shape_node_length(*shapes), index;
  if (cli_ask_for_shape_index("Select the index for the new shape.\n", *shapes,
                              &index, true, true) != CLI_VALID)
    return;

  shape_t *shape = cli_new_shape(inherited_styles);
  if (shape == NULL)
    return;

  if (index < 0 || index > length) {
    free_shape(shape);
    return;
  } else if (index == length)
    *shapes = push_shape_node(*shapes, shape);
  else
    *shapes = insert_shape_node_at(*shapes, index, shape);
}

void cli_remove_shape(shape_node_t **shapes) {
  int index;
  if (cli_ask_for_shape_index("Select the shapes's index to delete.\n", *shapes,
                              &index, true, false) != CLI_VALID)
    return;
  *shapes = remove_shape_node_at(*shapes, index);
}

void cli_edit_shapes(shape_node_t *shapes) {
  int index;
  if (cli_ask_for_shape_index("Select the shape's index to edit.\n", shapes,
                              &index, true, false) != CLI_VALID)
    return;
  int i = 0;
  shape_node_t *shape = shapes;
  while (shape != NULL && i < index) {
    shape = shape->next;
    i++;
  }
  if (i != index || shape == NULL)
    return;
  cli_edit_shape(shape->shape);
}

void cli_edit_group(group_t **group, style_t *inherited_styles) {
  bool error = false;
  cli_output_t output;
  int d;
  while (true) {
    cli_clear_screen();
    cli_print_group(*group, inherited_styles, 0);
    cli_print_content("Select action to perform :\n");
    cli_print_content("- Add new shape (1)\n");
    cli_print_content("- Edit shape (2)\n");
    cli_print_content("- Remove shape (3)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");

    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    switch (d) {
    case 1:
      cli_add_shape(group, inherited_styles);
      break;
    case 2:
      cli_edit_shapes(*group);
      break;
    case 3:
      cli_remove_shape(group);
      break;
    default:
      error = true;
      continue;
    }
  }
}

void cli_edit_shape(shape_t *shape) {
  bool error = false;
  cli_output_t output;
  int d;
  while (true) {
    cli_clear_screen();
    cli_print_shape(shape, 0);
    cli_print_content("Select action to perform :\n");
    cli_print_content("- Edit styles (1)\n");
    cli_print_content("- Edit shape (2)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");

    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    switch (d) {
    case 1:
      cli_edit_style(shape->styles);
      break;
    case 2:
      switch (shape->shape_variant) {
      case ELLIPSE:
        cli_edit_ellipse(shape->shape->ellipse);
        break;
      case RECTANGLE:
        cli_edit_rectangle(shape->shape->rectangle);
        break;
      case LINE:
        cli_edit_line(shape->shape->line);
        break;
      case MULTILINE:
        cli_edit_multiline(&shape->shape->multiline, shape->styles);
        break;
      case POLYGON:
        cli_edit_polygon(&shape->shape->polygon, shape->styles);
        break;
      case PATH:
        cli_edit_path(&shape->shape->path, shape->styles);
        break;
      case GROUP:
        cli_edit_group(&shape->shape->group, shape->styles);
        break;
      default:
        error = true;
        break;
      }
      break;
    default:
      error = true;
      break;
    }
  }
}

shape_t *cli_new_shape(style_t *inherited_styles) {
  bool error = false;
  int d;
  shape_t *shape = NULL;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select the new shape type :\n");
    cli_print_content("- Ellipse (1)\n");
    cli_print_content("- Rectangle (2)\n");
    cli_print_content("- Line (3)\n");
    cli_print_content("- Multiline (4)\n");
    cli_print_content("- Polygon (5)\n");
    cli_print_content("- Path (6)\n");
    cli_print_content("- Group (7)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");

    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return shape;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    switch (d) {
    case 1:
      shape = new_ellipse(0, 0, 10, 10, clone_style(inherited_styles));
      cli_edit_shape(shape);
      return shape;
      break;
    case 2:
      shape = new_rectangle(0, 0, 10, 10, clone_style(inherited_styles));
      cli_edit_shape(shape);
      return shape;
      break;
    case 3:
      shape = new_line(new_point(0, 0), new_point(10, 10),
                       clone_style(inherited_styles));
      cli_edit_shape(shape);
      return shape;
      break;
    case 4:
      shape = new_multiline(NULL, clone_style(inherited_styles));
      cli_edit_shape(shape);
      return shape;
      break;
    case 5:
      shape = new_polygon(NULL, clone_style(inherited_styles));
      cli_edit_shape(shape);
      return shape;
      break;
    case 6:
      shape = new_path(NULL, clone_style(inherited_styles));
      cli_edit_shape(shape);
      return shape;
      break;
    case 7:
      shape = new_group(NULL, clone_style(inherited_styles));
      cli_edit_shape(shape);
      return shape;
      break;
    default:
      error = false;
      break;
    }
  }
  return NULL;
}
