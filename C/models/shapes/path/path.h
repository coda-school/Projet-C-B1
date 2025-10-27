#ifndef CODA_PATH
#define CODA_PATH

#include "../../styles/style.h"
#include "../shape.h"
#include "curve_to.h"
#include "end_path.h"
#include "line_to.h"
#include "move_to.h"
#include "path_element.h"

/**
 * Duplicates the given path element.
 * Note that this function allocates memory.
 * @param element the path element to be duplicated.
 * @return the duplicated path element's pointer.
 * @see path_element_t.
 */
path_element_t *clone_path_element(path_element_t *element);

/**
 * Destroys the given path element.
 * Note that this function frees memory.
 * @param path_element the path element to be destroyed.
 * @see path_element_t.
 */
void free_path_element(path_element_t *path_element);

/**
 * Prints out the given path element.
 * Note that this function is for debug purposes only.
 * @param path_element the path element to be printed out.
 * @see path_element_t.
 */
void print_path_element(path_element_t *path_element);

/**
 * Represents a path element linked list node.
 * @param previous the previous path element node.
 * @param element  the node's path element.
 * @param next     the next path element node.
 * @see path_element_t.
 */
struct path_element_node_s {
  path_element_node_t *previous;
  path_element_t *element;
  path_element_node_t *next;
};

/**
 * Duplicates the given path element linked list.
 * Note that this function allocates memory.
 * Note that if the list parameter is NULL the function returns NULL.
 * @param list the linked list to be duplicated.
 * @return the duplicated list's pointer.
 * @see path_element_node_t.
 */
path_element_node_t *clone_path_element_list(path_element_node_t *list);

/**
 * Appends the given path element to the given linked list.
 * Note that this function allocates memory.
 * Note that if the given linked list is NULL (i.e. the linked is empty), the
 * linked list pointer will changed hence the return type.
 * @param elements the linked list.
 * @param element  the path element to append.
 * @return the updated linked list's first node pointer.
 * @see path_element_t.
 * @see path_element_node_t.
 */
path_element_node_t *push_path_element_node(path_element_node_t *elements,
                                            path_element_t *element);

/**
 * Inserts the given given path element at the given index in the given linked
 * list.
 * Note that this function allocates memory.
 * Note that if the given index is invalid (index < 0 or index >
 * length(elements)) the function returns NULL.
 * Note that if the given linked list is NULL (i.e. the linked is empty) or the
 * given index = 0, the linked list pointer will changed hence the return type.
 * @param elements the linked list.
 * @param index the insertion index.
 * @param element the path element to insert.
 * @return the updated linked list's first node pointer.
 * @see path_element_t.
 * @see path_element_node_t.
 */
path_element_node_t *insert_path_element_node_at(path_element_node_t *elements,
                                                 int index,
                                                 path_element_t *element);

/**
 * Removes the path element from the given list at the given index.
 * Note that this function frees memory.
 * Note that if the given index is invalid (index < 0 or index >
 * length(elements)) the function returns the linked list pointer.
 * Note that if the given linked list is NULL (i.e. the linked is empty) or the
 * given index = 0, the linked list pointer will changed hence the return type.
 * @param elements the linked list.
 * @param index the element to remove's index.
 * @return the updated linked list's first node pointer.
 * @see path_element_node_t.
 */
path_element_node_t *remove_path_element_node_at(path_element_node_t *elements,
                                                 int index);

/**
 * Computes the given linked list length.
 * @param elements the linked list.
 * @return the linked list length.
 * @see path_element_node_t.
 */
int get_path_element_node_length(path_element_node_t *elements);

/**
 * Destroys the given linked list.
 * Note that this function frees memory.
 * @param elements the linked list to be destroyed.
 * @see path_element_node_t.
 */
void free_path_element_nodes(path_element_node_t *elements);

/**
 * Overrides the path element linked list to define the path type.
 */
typedef path_element_node_t path_t;

/**
 * Creates a new path.
 * Note that this function allocates memory.
 * Note that this function wraps the new path in the shape_t structure.
 * @param path_elements the path's content.
 * @param styles the path's styles.
 * @return the new path's pointer.
 * @see path_element_node_t.
 * @see style_t.
 * @see path_t.
 * @see shape_t.
 */
shape_t *new_path(path_element_node_t *path_elements, style_t *styles);

/**
 * Destroys the given path.
 * Note that this function frees memory.
 * @param path the path to be destroyed.
 * @see path_t.
 */
void free_path(path_t *path);

/**
 * Prints out the given path.
 * Note that this function is for debug purposes only.
 * @param path the path to be printed out.
 * @see path_t.
 */
void print_path(path_t *path);

#endif
