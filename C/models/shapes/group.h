#ifndef CODA_GROUP
#define CODA_GROUP

#include "../styles/style.h"
#include "shape.h"

/**
 * Creates a new group.
 * Note that this function allocates memory.
 * Note that this function wraps the new group in the shape_t structure.
 * @param shapes the group's shape linked list.
 * @param styles the group's styles.
 * @return the new group's pointer.
 * @see style_t.
 * @see shape_node_t.
 * @see group_t.
 * @see shape_t.
 */
shape_t *new_group(shape_node_t *shapes, style_t *styles);

/**
 * Destroys the given group.
 * Note that this function frees memory.
 * @param group the group to be destroyed.
 * @see group_t.
 */
void free_group(group_t *group);

/**
 * Prints out the given group.
 * Note that this function is for debug purposes only.
 * @param group the group to be printed out.
 * @see group_t.
 */
void print_group(group_t *group);

#endif
