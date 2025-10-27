#include "serde.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

serdelizer_t *new_serdelizer(FILE *file) {
  serdelizer_t *serdelizer = malloc(sizeof(serdelizer_t));
  serdelizer->file = file;
  serdelizer->position = 0;
  serdelizer->last_consumed = '\0';
  serdelizer->line = 0;
  return serdelizer;
}

bool is_whitespace(char c) {
  switch (c) {
  case '\n':
  case '\r':
  case '\t':
  case ' ':
    return true;
  default:
    return false;
  }
}

char get_next_char(serdelizer_t *serdelizer) {
  char c = getc(serdelizer->file);
  switch (c) {
  case '\n':
    serdelizer->line++;
    serdelizer->position = 0;
    break;
  default:
    serdelizer->position++;
    break;
  }
  serdelizer->last_consumed = c;
  return c;
}

char get_next_non_whitespace_char(serdelizer_t *serdelizer) {
  char c = get_next_char(serdelizer);
  while (is_whitespace(c))
    c = get_next_char(serdelizer);
  return c;
}

bool write_spaces(serdelizer_t *serdelizer, int amount) {
  for (int i = 0; i < amount; i++) {
    if (fprintf(serdelizer->file, " ") <= 0) {
      print_serdelizer_error("write_spaces", "Could not write spaces in file",
                             serdelizer);
      return false;
    }
  }
  return true;
}

bool write_to_file(serdelizer_t *serdelizer, char *string) {
  int length = strlen(string);

  if (fprintf(serdelizer->file, "%s", string) <= 0)
    return false;

  for (int i = 0; i <= length; i++) {
    switch (string[i]) {
    case '\n':
      serdelizer->line++;
      serdelizer->position = 0;
      break;
    default:
      serdelizer->position++;
      break;
    }
  }
  serdelizer->position += length;
  return true;
}

void free_serdelizer(serdelizer_t *serdelizer) { fclose(serdelizer->file); }

void print_serdelizer_error(char *source, char *message,
                            serdelizer_t *serdelizer) {
  fprintf(stderr, "[ERROR] (%s) > %s\n| line: %d\n| position: %d\n", source,
          message, serdelizer->line + 1, serdelizer->position + 1);
}
