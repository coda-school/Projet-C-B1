#ifndef CODA_MOVE_TO
#define CODA_MOVE_TO

#include "../../utils/point.h"
#include "path_element.h"

/**
 * Represents the move to path element.
 * Represents the SVG path element code M <int> <int>.
 * @param point the move to's destination.
 * @see point_t.
 */
struct move_to_s {
  point_t *point;
};

/**
 * Destroys the given move to path element.
 * Note that this function frees memory.
 * @param move_to the move to path element to be destroyed.
 * @see move_to_t.
 */
void free_move_to(move_to_t *move_to);

/**
 * Prints out the given move to path element.
 * Note that this function is for debug purposes only.
 * @param move_to the move to path element to be printed out.
 * @see move_to_t.
 */
void print_move_to(move_to_t *move_to);

/**
 * Creates a new move to path element.
 * Note that this function allocates memory.
 * This function wraps the move to in the path element structure.
 * @param point the move_to's destination.
 * @return the new move to's destination.
 * @see point_t.
 * @see path_element_t.
 */
path_element_t *new_move_to(point_t *point);

/**
 * Converts the given move to path element to a string.
 * Note that this function allocates memory.
 * @param move_to the move to path element to be converted.
 * @return a string.
 * @see move_to_t.
 */
char *move_to_to_string(move_to_t *move_to);

#endif
