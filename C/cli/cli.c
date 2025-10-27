#include "cli.h"
#include "../html/html.h"
#include "../models/shapes/svg.h"
#include "../serde/deserialize/parser.h"
#include "../serde/serialize/export.h"
#include "../utils/utils.h"
#include "cli_path.h"
#include "cli_shape.h"
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define RESET "\033[1;38m"

#define PRINT_SVG_BUFFER_SIZE 500
#define PRINT_VIEWPORT_BUFFER_SIZE 500
#define OPEN_FILE_PATH_BUFFER_SIZE 500
#define SAVE_FILE_PATH_BUFFER_SIZE 500
#define EXPORT_HTML_FILE_PATH_BUFFER_SIZE 500
#define ASK_FOR_INDEX_BUFFER_SIZE 200

void cli_clear_screen() { fprintf(stdout, "\e[1;1H\e[2J"); }

void cli_print_content(char *content) { fprintf(stdout, "%s", content); }

void cli_print_error(char *content) {
  fprintf(stdout, RED "%s" WHITE, content);
}

void cli_print_success(char *content) {
  fprintf(stdout, GREEN "%s" WHITE, content);
}

void cli_print_spaces(int depth) {
  for (int i = 0; i < depth; i++)
    cli_print_content("  ");
}

void cli_print_svg(svg_t *svg) {
  char buffer[PRINT_SVG_BUFFER_SIZE];
  sprintf(buffer, "<svg viewport=\"%d %d %d %d\">\n", svg->viewport->start->x,
          svg->viewport->start->y, svg->viewport->end->x,
          svg->viewport->end->y);
  cli_print_content(buffer);
  shape_node_t *shape = svg->shapes;
  while (shape != NULL) {
    cli_print_shape(shape->shape, 1);
    shape = shape->next;
  }
  sprintf(buffer, "<svg \\>\n\n");
  cli_print_content(buffer);
}

void cli_print_points(point_node_t *points) {
  int i = 0;
  cli_print_content("Points [ ");
  if (points == NULL) {
    cli_print_content("]\n");
    return;
  }
  point_node_t *node = points;
  while (node->next != NULL) {
    fprintf(stdout, "(%i) X=%d Y%d, ", i, node->point->x, node->point->y);
    node = node->next;
    i++;
  }

  fprintf(stdout, "(%i) X=%d Y%d ]\n", i, node->point->x, node->point->y);
}

void cli_print_path_elements(path_element_node_t *elements) {
  int i = 0;
  cli_print_content("Path elements [ ");
  if (elements == NULL) {
    cli_print_content("]\n");
    return;
  }

  path_element_node_t *node = elements;
  while (node->next != NULL) {
    fprintf(stdout, "(%d) ", i);
    cli_print_path_element(node->element);
    cli_print_content(", ");
    node = node->next;
    i++;
  }

  fprintf(stdout, "(%d) ", i);
  cli_print_path_element(node->element);
  cli_print_content("]\n");
}

void cli_print_shapes(shape_node_t *shapes) {
  int i = 0;
  cli_print_content("Shapes [ ");
  if (shapes == NULL) {
    cli_print_content("]\n");
    return;
  } else
    cli_print_content("\n");

  shape_node_t *node = shapes;
  while (node->next != NULL) {
    fprintf(stdout, "(%d) ", i);
    cli_print_shape(node->shape, 0);
    node = node->next;
    i++;
  }

  fprintf(stdout, "(%d) ", i);
  cli_print_shape(node->shape, 0);
  cli_print_content("]\n");
}

cli_output_t cli_ask_for_int(int *value) {
  char input[100];
  char *endptr;
  cli_print_content("Enter an integer value (or nothing to exit) : ");
  if (fgets(input, sizeof(input), stdin) == NULL)
    return CLI_INVALID;
  if (input[0] == '\n')
    return CLI_EMPTY;

  input[strcspn(input, "\n")] = '\0';

  long num = strtol(input, &endptr, 10);

  if (*endptr != '\0' || num < INT_MIN || num > INT_MAX)
    return CLI_INVALID;

  *value = (int)num;
  return CLI_VALID;
}

cli_output_t cli_ask_for_string(char *result, size_t *size, size_t max_length) {
  cli_print_content("Enter your input : ");

  if (fgets(result, max_length, stdin) == NULL)
    return CLI_INVALID;

  if (result[0] == '\n')
    return CLI_EMPTY;

  result[strcspn(result, "\n")] = '\0';
  *size = strlen(result);

  return CLI_VALID;
}

cli_output_t cli_ask_for_bool(bool *value) {
  char input[10];
  if (fgets(input, sizeof(input), stdin) == NULL)
    return CLI_INVALID;

  if (input[0] == '\n')
    return CLI_EMPTY;

  input[strcspn(input, "\n")] = '\0';
  for (int i = 0; input[i]; i++)
    input[i] = tolower(input[i]);

  if (strcmp(input, "true") == 0) {
    *value = true;
    return CLI_VALID;
  } else if (strcmp(input, "false") == 0) {
    *value = false;
    return CLI_VALID;
  }

  return CLI_INVALID;
}

cli_output_t cli_ask_for_index(int min, int max, int *index) {
  int value = 0;
  cli_output_t result = cli_ask_for_int(&value);
  if (result == CLI_VALID && min <= value && value <= max) {
    *index = value;
    return result;
  }
  if (result == CLI_VALID)
    return CLI_INVALID;
  return result;
}

void cli_press_any_key() {
  cli_print_content("Press any key to continue...");
  while (getchar() != '\n')
    ;
  getchar();
}

cli_output_t cli_ask_for_point_index(char *prompt, point_node_t *points,
                                     int *index, bool include_lower,
                                     bool include_upper) {
  cli_output_t output;
  bool error = false;
  int length = get_point_node_length(points);
  char buffer[ASK_FOR_INDEX_BUFFER_SIZE];
  char lower = include_lower ? '[' : ']';
  char upper = include_upper ? ']' : '[';
  sprintf(buffer, "Select an index in the range %c0, %d%c.\n", lower, length, upper);
  int i;
  while (true) {
    cli_clear_screen();
    cli_print_points(points);
    cli_print_content(prompt);
    if (error)
      cli_print_error("Select a valid index.\n");
    cli_print_content(buffer);
    output = cli_ask_for_index(0, length, &i);
    if (output == CLI_EMPTY)
      return output;
    if (output == CLI_VALID) {
      *index = i;
      return output;
    }
    error = true;
  }
}

cli_output_t cli_ask_for_path_element_index(char *prompt,
                                            path_element_node_t *elements,
                                            int *index, bool include_lower,
                                            bool include_upper) {
  cli_output_t output;
  bool error = false;
  int length = get_path_element_node_length(elements);
  char buffer[ASK_FOR_INDEX_BUFFER_SIZE];
  char lower = include_lower ? '[' : ']';
  char upper = include_upper ? ']' : '[';
  sprintf(buffer, "Select an index in the range %c0, %d%c.\n", lower, length, upper);
  int i;
  while (true) {
    cli_clear_screen();
    cli_print_path_elements(elements);
    cli_print_content(prompt);
    if (error)
      cli_print_error("Select a valid index.\n");
    cli_print_content(buffer);
    output = cli_ask_for_index(0, length, &i);
    if (output == CLI_EMPTY)
      return output;
    if (output == CLI_VALID) {
      *index = i;
      return output;
    }
    error = true;
  }
}

cli_output_t cli_ask_for_shape_index(char *prompt, shape_node_t *shapes,
                                     int *index, bool include_lower,
                                     bool include_upper) {
  cli_output_t output;
  bool error = false;
  int length = get_shape_node_length(shapes);
  char buffer[ASK_FOR_INDEX_BUFFER_SIZE];
  char lower = include_lower ? '[' : ']';
  char upper = include_upper ? ']' : '[';
  sprintf(buffer, "Select an index in the range %c0, %d%c.\n", lower, length, upper);
  int i;
  while (true) {
    cli_clear_screen();
    cli_print_shapes(shapes);
    cli_print_content(prompt);
    if (error)
      cli_print_error("Select a valid index.\n");
    cli_print_content(buffer);
    output = cli_ask_for_index(0, length, &i);
    if (output == CLI_EMPTY)
      return output;
    if (output == CLI_VALID) {
      *index = i;
      return output;
    }
    error = true;
  }
}

cli_output_t cli_ask_for_int_parameter(char *entity_display, char *prompt,
                                       char *error_message,
                                       bool (*predicate)(int),
                                       bool allow_multiple_attempts,
                                       int *value) {
  bool error = false;
  cli_output_t output;
  int n;
  while (true) {
    cli_clear_screen();
    cli_print_content(entity_display);
    cli_print_content("\n");
    cli_print_content(prompt);
    if (error)
      cli_print_error(error_message);
    output = cli_ask_for_int(&n);
    if (output == CLI_EMPTY)
      return output;
    if (output == CLI_VALID && (predicate == NULL || (*predicate)(n))) {
      *value = n;
      return output;
    }
    if (output == CLI_INVALID && !allow_multiple_attempts)
      return output;
    error = true;
  }
}

void cli_edit_viewport(viewport_t *viewport) {
  int n;
  char buffer[PRINT_VIEWPORT_BUFFER_SIZE];
  sprintf(buffer, "Viewport { X1 = %d, Y1 = %d, X2 = %d, Y2 = %d }\n\n",
          viewport->start->x, viewport->start->y, viewport->end->x,
          viewport->end->y);
  cli_output_t output;
  bool error = false;

  while (true) {
    cli_clear_screen();
    cli_print_content(buffer);
    cli_print_content("Select the viewport start point's X coordinate.\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&n);
    if (output == CLI_EMPTY)
      break;
    if (output == CLI_VALID) {
      viewport->start->x = n;
      break;
    }
    error = true;
  }

  error = false;
  while (true) {
    cli_clear_screen();
    cli_print_content(buffer);
    cli_print_content("Select the viewport start point's Y coordinate.\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&n);
    if (output == CLI_EMPTY)
      break;
    if (output == CLI_VALID) {
      viewport->start->y = n;
      break;
    }
    error = true;
  }

  error = false;
  while (true) {
    cli_clear_screen();
    cli_print_content(buffer);
    cli_print_content("Select the viewport end point's X coordinate.\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&n);
    if (output == CLI_EMPTY)
      break;
    if (output == CLI_VALID) {
      viewport->end->x = n;
      break;
    }
    error = true;
  }

  error = false;
  while (true) {
    cli_clear_screen();
    cli_print_content(buffer);
    cli_print_content("Select the viewport end point's Y coordinate.\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&n);
    if (output == CLI_EMPTY)
      break;
    if (output == CLI_VALID) {
      viewport->end->y = n;
      break;
    }
    error = true;
  }
}

svg_t *cli_create_new_svg() {
  int vsx = 0, vsy = 0, vex = 0, vey = 0;
  bool error = false;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select the viewport start point's X coordinate (default "
                      "value is 0).\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&vsx);
    if (output == CLI_INVALID)
      error = true;
    else
      break;
  }

  error = false;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select the viewport start point's Y coordinate (default "
                      "value is 0).\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&vsy);
    if (output == CLI_INVALID)
      error = true;
    else
      break;
  }

  error = false;
  while (true) {
    cli_clear_screen();
    cli_print_content(
        "Select the viewport end point's X coordinate (default value is 0).\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&vex);
    if (output == CLI_INVALID)
      error = true;
    else
      break;
  }

  error = false;
  while (true) {
    cli_clear_screen();
    cli_print_content(
        "Select the viewport end point's Y coordinate (default value is 0).\n");
    if (error)
      cli_print_error("Enter a valid integer.\n");
    output = cli_ask_for_int(&vey);
    if (output == CLI_INVALID)
      error = true;
    else
      break;
  }

  return new_svg(new_viewport(new_point(min(vsx, vex), min(vsy, vey)),
                              new_point(max(vsx, vex), max(vsy, vey))),
                 NULL);
}

svg_t *cli_open_svg() {
  char buffer[OPEN_FILE_PATH_BUFFER_SIZE];
  size_t size, max_length = 500;
  bool running = true, error = false;
  FILE *file = NULL;
  svg_t *svg = NULL;
  serdelizer_t *serdelizer = NULL;
  cli_output_t output;
  while (running) {
    cli_clear_screen();
    cli_print_content("Select the svg file's path to open.\n");
    if (error)
      cli_print_error("Enter a valid file path\n");

    output = cli_ask_for_string(buffer, &size, max_length);

    if (output == CLI_EMPTY)
      return NULL;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    file = fopen(buffer, "r");
    if (file == NULL) {
      error = true;
      continue;
    }

    serdelizer = new_serdelizer(file);
    svg = parse_svg(serdelizer);
    if (svg == NULL) {
      cli_press_any_key();
      continue;
    }

    running = false;
  }
  if (serdelizer != NULL)
    free_serdelizer(serdelizer);
  return svg;
}

void cli_edit_svg(svg_t *svg) {
  bool error = false;
  int d;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_svg(svg);
    cli_print_content("Select action to perform :\n");
    cli_print_content("- Edit viewport (1)\n");
    cli_print_content("- Add new shape (2)\n");
    cli_print_content("- Edit shape (3)\n");
    cli_print_content("- Remove shape (4)\n");
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
      cli_edit_viewport(svg->viewport);
      break;
    case 2:
      cli_add_shape(&svg->shapes, new_default_style());
      break;
    case 3:
      cli_edit_shapes(svg->shapes);
      break;
    case 4:
      cli_remove_shape(&svg->shapes);
      break;
    default:
      error = true;
      continue;
    }
  }
  return;
}

export_config_t *cli_new_export_config() {
  int tab_size, d;
  bool error = false;
  export_config_t *config = new_export_config(2, false);
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    fprintf(stdout, "Export configs { Tab size = %d, Line break = %s }\n\n",
            config->tab_size, (config->line_break) ? "true" : "false");
    cli_print_content("Select action to perform :\n");
    cli_print_content("- Change tab size (1)\n");
    cli_print_content("- Change line break (2)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");

    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return config;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    switch (d) {
    case 1:
      output = cli_ask_for_int(&tab_size);
      if (output == CLI_VALID)
        config->tab_size = tab_size;
      if (output == CLI_INVALID)
        error = true;
      break;
    case 2:
      config->line_break = !config->line_break;
      break;
    default:
      error = true;
      continue;
    }
  }
  if (config != NULL)
    free_export_config(config);
  return NULL;
}

void cli_export_svg(svg_t *svg) {
  bool running = true, error = false;
  size_t size, max_length = 500;
  char buffer[SAVE_FILE_PATH_BUFFER_SIZE];
  FILE *file = NULL;
  serdelizer_t *serdelizer = NULL;
  export_config_t *config = NULL;
  cli_output_t output;
  while (running) {
    cli_clear_screen();
    cli_print_content("Select file path.\n");
    if (error)
      cli_print_error("Enter a valid file path.\n");

    output = cli_ask_for_string(buffer, &size, max_length);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    file = fopen(buffer, "w");
    if (file == NULL) {
      error = true;
      continue;
    }
    serdelizer = new_serdelizer(file);
    config = cli_new_export_config();
    if (config == NULL) {
      free_serdelizer(serdelizer);
      return;
    }
    if (!export_svg(svg, serdelizer, config)) {
      cli_press_any_key();
      free_export_config(config);
      free_serdelizer(serdelizer);
      return;
    } else
      running = false;
  }
  if (serdelizer != NULL)
    free_serdelizer(serdelizer);
  if (config != NULL)
    free_export_config(config);
  return;
}

void cli_export_svg_to_html(svg_t *svg) {
  bool error = false;
  size_t size, max_length = 500;
  char buffer[EXPORT_HTML_FILE_PATH_BUFFER_SIZE];
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select file path.\n");
    if (error)
      cli_print_error("Enter a valid file path.\n");

    output = cli_ask_for_string(buffer, &size, max_length);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_VALID)
      break;
    error = true;
  }

  export_to_html(svg, buffer);
}

void cli_main_menu() {
  bool running = true, error = false;
  int d;
  svg_t *svg = NULL;
  cli_output_t output;

  while (running) {
    cli_clear_screen();
    if (svg != NULL)
      cli_print_svg(svg);
    fprintf(stdout, "Choose action to perform :\n");
    if (svg == NULL)
      fprintf(stdout, "- (1) Create\n");
    if (svg == NULL)
      fprintf(stdout, "- (2) Open\n");
    if (svg != NULL)
      fprintf(stdout, "- (3) Edit\n");
    if (svg != NULL)
      fprintf(stdout, "- (4) Save\n");
    if (svg != NULL)
      fprintf(stdout, "- (5) Export\n");
    if (svg != NULL)
      fprintf(stdout, "- (6) Close\n");
    if (error)
      cli_print_error("Enter a valid option.\n");
    error = false;
    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY) {
      running = false;
      cli_clear_screen();
      continue;
    }
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    if (svg == NULL && d == 1)
      svg = cli_create_new_svg();
    else if (svg == NULL && d == 2)
      svg = cli_open_svg();
    else if (d == 3 && svg != NULL)
      cli_edit_svg(svg);
    else if (d == 4 && svg != NULL)
      cli_export_svg(svg);
    else if (d == 5 && svg != NULL)
      cli_export_svg_to_html(svg);
    else if (d == 6 && svg != NULL) {
      free_svg(svg);
      svg = NULL;
    } else
      error = true;
  }
  if (svg != NULL)
    free_svg(svg);
}
