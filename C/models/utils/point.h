#ifndef CODA_POINT
#define CODA_POINT

/**
 * Represents a point in a 2D space. Only accepts integer coordinates.
 * @param x the X coordinate.
 * @param y the Y coordinate.
 */
typedef struct point_s {
  int x;
  int y;
} point_t;

/**
 * Creates a new point with the given coordinates.
 * Note that this function allocates memory.
 * @param x the X coordinate.
 * @param x the Y coordinate.
 * @return the new point's pointer.
 * @see point_t
 */
point_t *new_point(int x, int y);

/**
 * Duplicates the given point.
 * Note that this function allocates memory.
 * @param the point to be duplicated.
 * @return the duplicated point's pointer.
 */
point_t *clone_point(point_t *point);

/**
 * Destroys the given point.
 * Note that this function frees the memory occupied by the given point.
 * @param point the point to be destroyed.
 * @see point_t.
 */
void free_point(point_t *point);

/**
 * Prints out the given point.
 * Note that this function is for debug purposes only.
 * @param point the point to be printed out.
 * @see point_t.
 */
void print_point(point_t *point);

/**
 * Defines the point_node_t type.
 * Represents a point linked list node.
 */
typedef struct point_node_s point_node_t;

/**
 * Represents a point linked list node.
 * @param point    the linked list node's point.
 * @param previous the linked list previous node. The value is NULL if the node
 * is the first element.
 * @param next     the linked list next node. The value is NULL if the node is
 * the last element.
 * @see point_t.
 */
struct point_node_s {
  point_t *point;
  point_node_t *previous;
  point_node_t *next;
};

/**
 * Clones the given point linked list.
 * Note that this function allocates memory.
 * @param points the linked list to be duplicated's first node.
 * @returns the pointer to the duplicated linked list's first node.
 * @see point_node_t.
 */
point_node_t *clone_point_list(point_node_t *points);

/**
 * Appends the given point at the end of the given linked list.
 * Note that this function allocates memory.
 * Note that if the given linked list is NULL (i.e. the linked list is empty)
 * the linked list pointer will no longer be NULL hence the return type.
 * @param points the linked list.
 * @param point  the point to be added.
 * @return the linked list first node's pointer.
 * @see point_node_t.
 * @see point_t.
 */
point_node_t *push_point_node(point_node_t *points, point_t *point);

/**
 * Inserts the given point at the given index in the given linked list.
 * Note that this function allocates memory.
 * Note that if the index is invalid (i.e. < 0 || >= length(points)) the
 * function will return NULL.
 * Note that if the linked list is NULL (i.e. the linked list is empty) or if
 * the index is 0 the linked list pointer (i.e. the first node pointer) will
 * change hence the return type.
 * @param points the linked list.
 * @param index  the insertion index. Must be >= 0 and < length(points).
 * @param point  the point to be inserted.
 * @return the linked list first node's pointer.
 * @see point_node_t.
 * @see point_t.
 */
point_node_t *insert_point_node_at(point_node_t *points, int index,
                                   point_t *point);

/**
 * Removes the point at the given index from the given linked list.
 * Note that this function frees memory.
 * Note that if the given index is invalid (i.e. < 0 or >= length(points)) the
 * function will return the linked list pointer.
 * Note that if the linked list is NULL (i.e. the linked list is empty) or if
 * the index is 0 the linked list pointer (i.e. the first node pointer) will
 * change hence the return type.
 * @param points the linked list.
 * @param index  the point to be removed's index. Must be >= 0 and <
 * length(points).
 * @return the linked list first node's pointer.
 * @see point_node_t.
 */
point_node_t *remove_point_node_at(point_node_t *points, int index);

/**
 * Computes the given linked list's length.
 * @param points the linked list.
 * @return the linked list's length.
 * @see point_node_t.
 */
int get_point_node_length(point_node_t *points);

/**
 * Destroys the given linked list.
 * Note that this function frees memory.
 * Note that this function frees all the nodes and all their associated points.
 * @param points the linked list.
 * @see point_node_t.
 */
void free_point_nodes(point_node_t *points);

#endif
