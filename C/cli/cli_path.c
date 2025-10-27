#include "cli_path.h"
#include "cli.h"
#include <stdio.h>

void cli_print_move_to(move_to_t *move_to) {
  fprintf(stdout, "M %d %d", move_to->x, move_to->y);
}

void cli_print_line_to(line_to_t *line_to) {
  fprintf(stdout, "L %d %d", line_to->x, line_to->y);
}

void cli_print_vertical_line_to(vertical_line_to_t vertical_line_to) {
  fprintf(stdout, "V %d", vertical_line_to);
}

void cli_print_horizontal_line_to(horizontal_line_to_t horizontal_line_to) {
  fprintf(stdout, "H %d", horizontal_line_to);
}

void cli_print_cubic_curve_to(cubic_curve_to_t *cubic_curve_to) {
  fprintf(stdout, "C %d %d %d %d %d %d", cubic_curve_to->control_point_1->x,
          cubic_curve_to->control_point_1->y,
          cubic_curve_to->control_point_2->x,
          cubic_curve_to->control_point_2->y, cubic_curve_to->end->x,
          cubic_curve_to->end->y);
}

void cli_print_cubic_curve_to_shorthand(
    shorthand_cubic_curve_to_t *cubic_curve_to_shorthand) {
  fprintf(stdout, "S %d %d %d %d", cubic_curve_to_shorthand->control_point->x,
          cubic_curve_to_shorthand->control_point->y,
          cubic_curve_to_shorthand->end->x, cubic_curve_to_shorthand->end->y);
}

void cli_print_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to) {
  fprintf(stdout, "Q %d %d %d %d", quadratic_curve_to->control_point->x,
          quadratic_curve_to->control_point->y, quadratic_curve_to->end->x,
          quadratic_curve_to->end->y);
}

void cli_print_quadratic_curve_to_shorthand(
    shorthand_quadratic_curve_to_t *quadratic_curve_to_shorthand) {
  fprintf(stdout, "T %d %d", quadratic_curve_to_shorthand->x,
          quadratic_curve_to_shorthand->y);
}

void cli_print_end_of_path() { fprintf(stdout, "Z"); }

void cli_print_path_element(path_element_t *path_element) {
  switch (path_element->path_element_variant) {
  case MOVE_TO:
    cli_print_move_to(path_element->path_element->move_to);
    break;
  case LINE_TO:
    cli_print_line_to(path_element->path_element->line_to);
    break;
  case VERTICAL_LINE_TO:
    cli_print_vertical_line_to(path_element->path_element->vertical_line_to);
    break;
  case HORIZONTAL_LINE_TO:
    cli_print_horizontal_line_to(
        path_element->path_element->horizontal_line_to);
    break;
  case END_PATH:
    cli_print_end_of_path();
    break;
  case CUBIC_CURVE_TO:
    cli_print_cubic_curve_to(path_element->path_element->cubic_curve_to);
    break;
  case CUBIC_CURVE_TO_SHORTHAND:
    cli_print_cubic_curve_to_shorthand(
        path_element->path_element->shorthand_cubic_curve_to);
    break;
  case QUADRATIC_CURVE_TO:
    cli_print_quadratic_curve_to(
        path_element->path_element->quadratic_curve_to);
    break;
  case QUADRATIC_CURVE_TO_SHORTHAND:
    cli_print_quadratic_curve_to_shorthand(
        path_element->path_element->shorthand_quadratic_curve_to);
    break;
  }
}

void cli_edit_move_to(move_to_t *move_to) {
  int n;
  char *text = move_to_to_string(move_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the move to's X coordinate.\n",
                                "Enter a valid integer.\n", NULL, true, &n))
    move_to->x = n;
  free(text);

  text = move_to_to_string(move_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the move to's Y coordinate.\n",
                                "Enter a valid integer.\n", NULL, true, &n))
    move_to->y = n;
  free(text);
}

void cli_edit_line_to(line_to_t *line_to) {
  int n;
  char *text = line_to_to_string(line_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the line to's X coordinate.\n",
                                "Enter a valid integer.\n", NULL, true, &n))
    line_to->x = n;
  free(text);

  text = line_to_to_string(line_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(text, "Select the line to's Y coordinate.\n",
                                "Enter a valid integer.\n", NULL, true, &n))
    line_to->y = n;
  free(text);
}

void cli_edit_horizontal_line_to(horizontal_line_to_t *horizontal_line_to) {
  int n;
  char *text = horizontal_line_to_to_string(*horizontal_line_to);
  if (CLI_VALID == cli_ask_for_int_parameter(
                       text, "Select the horizontal line to's X coordinate.\n",
                       "Enter a valid integer.\n", NULL, true, &n))
    *horizontal_line_to = n;
  free(text);
}

void cli_edit_vertical_line_to(vertical_line_to_t *vertical_line_to) {
  int n;
  char *text = vertical_line_to_to_string(*vertical_line_to);
  if (CLI_VALID == cli_ask_for_int_parameter(
                       text, "Select the vertical line to's Y coordinate.\n",
                       "Enter a valid integer.\n", NULL, true, &n))
    *vertical_line_to = n;
  free(text);
}

void cli_edit_cubic_curve_to(cubic_curve_to_t *cubic_curve_to) {
  int n;
  char *text = cubic_curve_to_string(cubic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the cubic curve to control point 1's X coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to->control_point_1->x = n;
  free(text);

  text = cubic_curve_to_string(cubic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the cubic curve to control point 1's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to->control_point_1->y = n;
  free(text);

  text = cubic_curve_to_string(cubic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the cubic curve to control point 2's X coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to->control_point_2->x = n;
  free(text);

  text = cubic_curve_to_string(cubic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the cubic curve to control point 2's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to->control_point_2->y = n;
  free(text);

  text = cubic_curve_to_string(cubic_curve_to);
  if (CLI_VALID == cli_ask_for_int_parameter(
                       text,
                       "Select the cubic curve to end point's X coordinate.\n",
                       "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to->end->x = n;
  free(text);

  text = cubic_curve_to_string(cubic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the cubic curve to end point 1's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to->end->y = n;
  free(text);
}

void cli_edit_cubic_curve_to_shorthand(
    shorthand_cubic_curve_to_t *cubic_curve_to_shorthand) {
  int n;
  char *text = cubic_curve_to_shorthand_to_sting(cubic_curve_to_shorthand);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text,
          "Select the cubic curve to shorthand control point's X coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to_shorthand->control_point->x = n;
  free(text);

  text = cubic_curve_to_shorthand_to_sting(cubic_curve_to_shorthand);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text,
          "Select the cubic curve to shorthand control point's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to_shorthand->control_point->y = n;
  free(text);

  text = cubic_curve_to_shorthand_to_sting(cubic_curve_to_shorthand);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text,
          "Select the cubic curve to shorthand end point's X coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to_shorthand->end->x = n;
  free(text);

  text = cubic_curve_to_shorthand_to_sting(cubic_curve_to_shorthand);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text,
          "Select the cubic curve to shorthand end point's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    cubic_curve_to_shorthand->end->y = n;
  free(text);
}

void cli_edit_quadratic_curve_to(quadratic_curve_to_t *quadratic_curve_to) {
  int n;
  char *text = quadratic_curve_to_to_string(quadratic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the quadratic curve to control point's X coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    quadratic_curve_to->control_point->x = n;
  free(text);

  text = quadratic_curve_to_to_string(quadratic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the quadratic curve to control point's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    quadratic_curve_to->control_point->y = n;
  free(text);

  text = quadratic_curve_to_to_string(quadratic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the quadratic curve to end point's X coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    quadratic_curve_to->end->x = n;
  free(text);

  text = quadratic_curve_to_to_string(quadratic_curve_to);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the quadratic curve to end point's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    quadratic_curve_to->end->y = n;
  free(text);
}

void cli_edit_quadratic_curve_to_shorthand(
    shorthand_quadratic_curve_to_t *quadratic_curve_to_shorthand) {
  int n;
  char *text =
      quadratic_curve_to_shorthand_to_string(quadratic_curve_to_shorthand);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the quadratoic curve to shorthand's X coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    quadratic_curve_to_shorthand->x = n;
  free(text);

  text = quadratic_curve_to_shorthand_to_string(quadratic_curve_to_shorthand);
  if (CLI_VALID ==
      cli_ask_for_int_parameter(
          text, "Select the quadratic curve to shorthand's Y coordinate.\n",
          "Enter a valid integer.\n", NULL, true, &n))
    quadratic_curve_to_shorthand->y = n;
  free(text);
}

void cli_edit_path_element(path_element_t *path_element) {
  cli_clear_screen();
  switch (path_element->path_element_variant) {
  case MOVE_TO:
    cli_edit_move_to(path_element->path_element->move_to);
    break;
  case LINE_TO:
    cli_edit_line_to(path_element->path_element->line_to);
    break;
  case VERTICAL_LINE_TO:
    cli_edit_vertical_line_to(&path_element->path_element->vertical_line_to);
    break;
  case HORIZONTAL_LINE_TO:
    cli_edit_horizontal_line_to(
        &path_element->path_element->horizontal_line_to);
    break;
  case CUBIC_CURVE_TO:
    cli_edit_cubic_curve_to(path_element->path_element->cubic_curve_to);
    break;
  case CUBIC_CURVE_TO_SHORTHAND:
    cli_edit_cubic_curve_to_shorthand(
        path_element->path_element->shorthand_cubic_curve_to);
    break;
  case QUADRATIC_CURVE_TO:
    cli_edit_quadratic_curve_to(path_element->path_element->quadratic_curve_to);
    break;
  case QUADRATIC_CURVE_TO_SHORTHAND:
    cli_edit_quadratic_curve_to_shorthand(
        path_element->path_element->shorthand_quadratic_curve_to);
    break;
  default:
    break;
  }
}

path_element_t *cli_create_new_move_to() {
  cli_clear_screen();
  path_element_t *move_to = new_move_to(new_point(0, 0));
  return move_to;
}

path_element_t *cli_create_new_line_to() {
  cli_clear_screen();
  path_element_t *line_to = new_line_to(new_point(0, 0));
  return line_to;
}

path_element_t *cli_create_new_vertical_line_to() {
  cli_clear_screen();
  path_element_t *vertical_line_to = new_vertical_line_to(0);
  return vertical_line_to;
}

path_element_t *cli_create_new_horizontal_line_to() {
  cli_clear_screen();
  path_element_t *horizontal_line_to = new_horizontal_line_to(0);
  return horizontal_line_to;
}

path_element_t *cli_create_new_cubic_curve_to() {
  cli_clear_screen();
  path_element_t *cubic_curve_to =
      new_cubic_curve_to(new_point(0, 0), new_point(0, 0), new_point(0, 0));
  return cubic_curve_to;
}

path_element_t *cli_create_new_cubic_curve_to_shorthand() {
  cli_clear_screen();
  path_element_t *cubic_curve_to_shorthand =
      new_cubic_curve_to_shorthand(new_point(0, 0), new_point(0, 0));
  return cubic_curve_to_shorthand;
}

path_element_t *cli_create_new_quadratic_curve_to() {
  cli_clear_screen();
  path_element_t *quadratic_curve_to =
      new_quadratic_curve_to(new_point(0, 0), new_point(0, 0));
  return quadratic_curve_to;
}

path_element_t *cli_create_new_quadratic_curve_to_shorthand() {
  cli_clear_screen();
  path_element_t *quadratic_curve_to_shorthand =
      new_quadratic_curve_to_shorthand(new_point(0, 0));
  return quadratic_curve_to_shorthand;
}

path_element_t *cli_new_path_element() {
  bool error = false;
  int d;
  cli_output_t output;
  while (true) {
    cli_clear_screen();
    cli_print_content("Select element to create :\n");
    cli_print_content("- New move to (1)\n");
    cli_print_content("- New line to (2)\n");
    cli_print_content("- New horizontal line to (3)\n");
    cli_print_content("- New vertical line to (4)\n");
    cli_print_content("- New cubic curve to (5)\n");
    cli_print_content("- New cubic curve to shorthand (6)\n");
    cli_print_content("- New quadratic curve to (7)\n");
    cli_print_content("- New quadratic curve to shorthand (8)\n");
    cli_print_content("- New end of path (9)\n");
    if (error)
      cli_print_error("Enter a valid option.\n");
    cli_print_content("Enter the action to perform.\n");

    output = cli_ask_for_int(&d);
    if (output == CLI_EMPTY)
      return NULL;
    if (output == CLI_INVALID) {
      error = true;
      continue;
    }

    switch (d) {
    case 1:
      return cli_create_new_move_to();
      break;
    case 2:
      return cli_create_new_line_to();
      break;
    case 3:
      return cli_create_new_horizontal_line_to();
      break;
    case 4:
      return cli_create_new_vertical_line_to();
      break;
    case 5:
      return cli_create_new_cubic_curve_to();
      break;
    case 6:
      return cli_create_new_cubic_curve_to_shorthand();
      break;
    case 7:
      return cli_create_new_quadratic_curve_to();
      break;
    case 8:
      return cli_create_new_quadratic_curve_to_shorthand();
      break;
    case 9:
      return new_end_path();
      break;
    default:
      error = true;
      continue;
    }
  }
}
