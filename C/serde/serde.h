#ifndef CODA_SERDE
#define CODA_SERDE

#include <stdbool.h>
#include <stdio.h>

/**
 * Defines the serdelizer type.
 * The serdelizer is designed to keep track of the cursor in it's associated
 * file.
 * @param line          the cursor's line.
 * @param position      the cursor's position on the line.
 * @param file          the serdelizer's file.
 * @param last_consumed the last consumed character.
 */
typedef struct serdelizer_s {
  int line;
  int position;
  FILE *file;
  char last_consumed;
} serdelizer_t;

/**
 * Creates a new serdelizer.
 * Note that this function allocates memory.
 * @param file the serdelizer's file.
 * @return the new serdelizer's pointer.
 * @see serdelizer_t.
 */
serdelizer_t *new_serdelizer(FILE *file);

/**
 * Checks if the given character is a whitespace.
 * The function checks for ' ', '\t', '\n' or '\r'.
 * @param c the character to check.
 * @return true if the character is a whitespace.
 */
bool is_whitespace(char c);

/**
 * Reads the next char from the file.
 * @param serdelizer the file accessor.
 * @return the read char.
 * @see serdelizer_t.
 */
char get_next_char(serdelizer_t *serdelizer);

/**
 * Reads the next char from the file until reaching a non whitespace char.
 * @param serdelizer the file accessor.
 * @return the read char.
 * @see serdelizer_t.
 */
char get_next_non_whitespace_char(serdelizer_t *serdelizer);

/**
 * Writes "amount" times tabs to the file.
 * @param serdelizer the file accessor.
 * @param amount     the number of tabs to write.
 * @return returns true if the operation was successful.
 * @see serdelizer_t.
 */
bool write_spaces(serdelizer_t *serdelizer, int amount);

/**
 * Writes the given string to the file.
 * @param serdelizer the file accessor.
 * @param string     the file's string.
 * @return returns true if the operation was successful.
 * @see serdelizer_t.
 */
bool write_to_file(serdelizer_t *serdelizer, char *string);

/**
 * Destroys the given serdelizer.
 * Note that this function frees memory.
 * @param serdelizer the serdelizer to destroy.
 * @see serdelizer_t.
 */
void free_serdelizer(serdelizer_t *serdelizer);

/**
 * Displays a formatted version of the given error message.
 * This function displays the line and position of the cursor and the error
 * source.
 * @param error      the error source. It is attended to be the function's name.
 * @param message    the error message.
 * @param serdelizer the file accessor.
 */
void print_serdelizer_error(char *source, char *message,
                            serdelizer_t *serdelizer);

#endif
