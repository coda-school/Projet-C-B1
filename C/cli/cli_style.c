#include "cli_style.h"
#include "../serde/deserialize/parser.h"
#include "cli.h"
#include <stdio.h>
#include <string.h>

#define FILL_BUFFER_SIZE 50
#define OUTLINE_BUFFER_SIZE 50
#define ROTATE_BUFFER_SIZE 50

void cli_display_style(style_t *styles) {
  fprintf(stdout, "fill=\"");
  fprintf(stdout, "#%02x%02x%02x%02x\" ", styles->fill->blue,
          styles->fill->green, styles->fill->red, styles->fill->transparent);

  fprintf(stdout, "outline=\"");
  fprintf(stdout, "#%02x%02x%02x%02x\" ", styles->outline->blue,
          styles->outline->green, styles->outline->red,
          styles->outline->transparent);

  fprintf(stdout, "translate=\"%d %d\" ", styles->translate->x,
          styles->translate->y);

  fprintf(stdout, "rotate=\"");
  switch (styles->rotate->variant) {
  case FLIP_X:
    fprintf(stdout, "X\" ");
    break;
  case FLIP_Y:
    fprintf(stdout, "Y\" ");
    break;
  case CIRCULAR:
    fprintf(stdout, "%d\" ", styles->rotate->rotation.circular);
    break;
  }
}

void cli_select_fill(style_t *styles) {
  bool error = false;
  char buffer[FILL_BUFFER_SIZE];
  cli_output_t output;
  size_t length;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select a color for the 'fill' parameter.\n");
    if (error)
      cli_print_error("Enter a valid color format. (r-g-b-a parameters must be "
                      "hexa values).\n");
    cli_print_content("Enter color (format: #rrggbbaa) or 'transparent'.\n");

    output = cli_ask_for_string(buffer, &length, FILL_BUFFER_SIZE);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    if (buffer[0] == '#' && is_char_hexa(buffer[1]) &&
        is_char_hexa(buffer[2]) && is_char_hexa(buffer[3]) &&
        is_char_hexa(buffer[4]) && is_char_hexa(buffer[5]) &&
        is_char_hexa(buffer[6]) && is_char_hexa(buffer[7]) &&
        is_char_hexa(buffer[8])) {
      styles->fill->red = 16 * hexa_to_int(buffer[1]) + hexa_to_int(buffer[2]);
      styles->fill->green =
          16 * hexa_to_int(buffer[3]) + hexa_to_int(buffer[4]);
      styles->fill->blue = 16 * hexa_to_int(buffer[5]) + hexa_to_int(buffer[6]);
      styles->fill->transparent =
          16 * hexa_to_int(buffer[7]) + hexa_to_int(buffer[8]);
      return;
    }
    error = true;
  }
}

void cli_select_outline(style_t *styles) {
  bool error = false;
  char buffer[OUTLINE_BUFFER_SIZE];
  cli_output_t output;
  size_t length;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select a color for the 'outline' parameter.\n");
    if (error)
      cli_print_error("Enter a valid color format. (r-g-b-a parameters must be "
                      "hexa values).\n");
    cli_print_content("Enter color (format: #rrggbbaa) or 'transparent'.\n");

    output = cli_ask_for_string(buffer, &length, OUTLINE_BUFFER_SIZE);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    if (buffer[0] == '#' && is_char_hexa(buffer[1]) &&
        is_char_hexa(buffer[2]) && is_char_hexa(buffer[3]) &&
        is_char_hexa(buffer[4]) && is_char_hexa(buffer[5]) &&
        is_char_hexa(buffer[6]) && is_char_hexa(buffer[7]) &&
        is_char_hexa(buffer[8])) {
      styles->outline->red =
          16 * hexa_to_int(buffer[1]) + hexa_to_int(buffer[2]);
      styles->outline->green =
          16 * hexa_to_int(buffer[3]) + hexa_to_int(buffer[4]);
      styles->outline->blue =
          16 * hexa_to_int(buffer[5]) + hexa_to_int(buffer[6]);
      styles->outline->transparent =
          16 * hexa_to_int(buffer[7]) + hexa_to_int(buffer[8]);
      return;
    }
    error = true;
  }
}

void cli_select_rotate(style_t *styles) {
  bool error = false, valid = false, is_negative = false;
  char buffer[ROTATE_BUFFER_SIZE];
  size_t length;
  cli_output_t output;
  rotate_t *previous_rotate;
  int res;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select a rotate value.\n");
    if (error)
      cli_print_error("Enter a valid rotate value.\n");
    cli_print_content("Enter 'X', 'Y' or a rotate integer value '°'.\n");

    output = cli_ask_for_string(buffer, &length, ROTATE_BUFFER_SIZE);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    if (buffer[0] == 'X' || buffer[0] == 'x') {
      previous_rotate = styles->rotate;
      styles->rotate = new_flipx();
      free_rotate(previous_rotate);
      return;
    } else if (buffer[0] == 'Y' || buffer[0] == 'y') {
      previous_rotate = styles->rotate;
      styles->rotate = new_flipy();
      free_rotate(previous_rotate);
      return;
    }

    res = 0;
    valid = true;
    is_negative = false;
    for (int i = 0; i < length; i++) {
      if (i == 0 && buffer[i] == '-') {
        is_negative = true;
        continue;
      }
      if (!is_char_digit(buffer[i])) {
        valid = false;
        break;
      }
      res = res * 10 + char_to_int(buffer[i]);
    }

    if (!valid) {
      error = true;
      continue;
    }

    if (is_negative)
      res *= -1;

    previous_rotate = styles->rotate;
    styles->rotate = new_circular(res);
    free_rotate(previous_rotate);
    return;
  }
}

void cli_select_translate_x(point_t *point) {
  bool error = false;
  cli_output_t output;
  int d;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select a translate X value.\n");
    if (error)
      cli_print_error("Enter a valid translate value (integer).\n");
    cli_print_content("Enter a translate X value : ");
    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }
    point->x = d;
    return;
  }
}

void cli_select_translate_y(point_t *point) {
  bool error = false;
  cli_output_t output;
  int d;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select a translate Y value.\n");
    if (error)
      cli_print_error("Enter a valid translate value (integer).\n");
    cli_print_content("Enter a translate Y value : ");
    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }
    point->y = d;
    return;
  }
}

void cli_select_translate(style_t *styles) {
  cli_select_translate_x(styles->translate);
  cli_select_translate_y(styles->translate);
}

void cli_edit_style(style_t *styles) {
  bool error = false;
  int m;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_display_style(styles);
    cli_print_content("Edit style :\n");
    cli_print_content("- fill (1)\n");
    cli_print_content("- outline (2)\n");
    cli_print_content("- translate (3)\n");
    cli_print_content("- rotate (4)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");

    output = cli_ask_for_int(&m);
    if (output == CLI_EMPTY)
      return;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    switch (m) {
    case 1:
      cli_select_fill(styles);
      break;
    case 2:
      cli_select_outline(styles);
      break;
    case 3:
      cli_select_translate(styles);
      break;
    case 4:
      cli_select_rotate(styles);
      break;
    default:
      error = true;
      break;
    }
  }
}
