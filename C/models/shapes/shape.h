#ifndef CODA_SHAPE_BASE
#define CODA_SHAPE_BASE

#include "../styles/style.h"
#include "../utils/point.h"

/**
 * Predefines the path element linked list node type.
 */
typedef struct path_element_node_s path_element_node_t;

/**
 * Predefines the shape type.
 */
typedef struct shape_s shape_t;

/**
 * Predefines the shape linked list node type.
 */
typedef struct shape_node_s shape_node_t;

/**
 * Defines the shape linked list node type.
 * @param previous the linked list's previous node.
 * @param shape    the node's shape.
 * @param next     the linked list's next node.
 */
struct shape_node_s {
  shape_node_t *previous;
  shape_t *shape;
  shape_node_t *next;
};

/**
 * Defines the ellipse type.
 * @param center_x the ellipse center's X coordinate.
 * @param center_y the ellipse center's Y coordinate.
 * @param radius_x the ellipse's width.
 * @param radius_y the ellipse's height.
 */
typedef struct ellipse_s {
  int center_x;
  int center_y;
  int radius_x;
  int radius_y;
} ellipse_t;

/**
 * Defines the rectangle type.
 * @param x      the rectangle's top left corner X coordinate.
 * @param y      the rectangle's top left corner Y coordinate.
 * @param width  the rectangle's width.
 * @param height the rectangle's height.
 */
typedef struct rectangle_s {
  int x;
  int y;
  int width;
  int height;
} rectangle_t;

/**
 * Defines the line type.
 * @param start the line's start position.
 * @param end   the line's end position.
 */
typedef struct line_s {
  point_t *start;
  point_t *end;
} line_t;

/**
 * Overrides the point linked list node type to define the multiline type.
 */
typedef point_node_t multiline_t;

/**
 * Overrides the point linked list node type to define the polygon type.
 */
typedef point_node_t polygon_t;

/**
 * Overrides the path linked list node type to define the path type.
 */
typedef path_element_node_t path_t;

/**
 * Overrides the shape linked list node type to define the group type.
 */
typedef shape_node_t group_t;

/**
 * Lists all the shape variants.
 */
typedef enum shape_variants_e {
  ELLIPSE,
  RECTANGLE,
  LINE,
  MULTILINE,
  POLYGON,
  PATH,
  GROUP,
} shape_variants_t;

/**
 * Groups all the shape variants.
 */
typedef union shape_union_u {
  ellipse_t *ellipse;
  rectangle_t *rectangle;
  line_t *line;
  multiline_t *multiline;
  polygon_t *polygon;
  path_t *path;
  group_t *group;
} shape_union_t;

/**
 * Defines the shape type.
 * @param shape_variant indicates the active shape variant.
 * @param shape         holds the active shape variant.
 * @param styles        the shape's styles.
 */
struct shape_s {
  shape_variants_t shape_variant;
  shape_union_t *shape;
  style_t *styles;
};

/**
 * Duplicates the given shape.
 * Note that this function allocates memory.
 * @param shape the shape to be duplicated.
 * @return the duplicated shape's pointer.
 * @see shape_t.
 */
shape_t *clone_shape(shape_t *shape);

/**
 * Destroys the given shape.
 * Note that this function frees memory.
 * @param shape the shape to be destroyed.
 * @see shape_t.
 */
void free_shape(shape_t *shape);

/**
 * Prints out the given shape.
 * Note that this function is for debug purposes only.
 * @param shape the shape to be printed out.
 * @see shape_t.
 */
void print_shape(shape_t *shape);

/**
 * Duplicates the given shape linked list.
 * Note that this function allocates memory.
 * @param shapes the linked list.
 * @return the new linked list's pointer.
 * @see shape_node_t.
 */
shape_node_t *clone_shape_list(shape_node_t *shapes);

/**
 * Appends the given shape to the given shape linked list.
 * Note that this function allocates memory.
 * Note that if the linked list is NULL (i.e. the linked list is empty) then the
 * linked list pointer will change hence the result type.
 * @param shapes the linked list.
 * @param shape  the shape to append.
 * @return the linked list updated first node's pointer.
 * @see shape_t.
 * @see shape_node_t.
 */
shape_node_t *push_shape_node(shape_node_t *shapes, shape_t *shape);

/**
 * Inserts the given shape at the given index in the given linked list.
 * Note that this function allocates memory.
 * Note that if the index is invalid (index < 0 || index > length(shapes)) the
 * function returns the linked list's pointer.
 * Note that if the linked list is NULL (i.e. the linked list is empty) or the
 * index is 0 the linked list pointer will changed hence the return type.
 * @param shapes the linked list.
 * @param index the  insertion index. Must be >= 0 and <= length(shapes).
 * @param shape the  shape to insert.
 * @return the updated linked list first node's pointer.
 * @see shape_t.
 * @see shape_node_t.
 */
shape_node_t *insert_shape_node_at(shape_node_t *shapes, int index,
                                   shape_t *shape);

/**
 * Removes the shape from the given linked list at the given index.
 * Note that this function frees memory.
 * Note that if the given index is invalid (index < 0 || index >=
 * length(shapes)) the function returns NULL.
 * Note that if the given index is 0 the shape linked list pointer will changed
 * hence the return type.
 * @param shapes the linked list.
 * @param index the shape's index to remove.
 * @return the updated linked list's pointer.
 * @see shape_node_t.
 */
shape_node_t *remove_shape_node_at(shape_node_t *shapes, int index);

/**
 * Computes the given shape linked list length.
 * @param shapes the linked list.
 * @return the linked list length.
 * @see shape_node_t.
 */
int get_shape_node_length(shape_node_t *shapes);

/**
 * Destroys the given shape linked list.
 * Note that this function frees memory.
 * @param shapes the shape linked list to be destroyed.
 * @see shape_node_t.
 */
void free_shape_node(shape_node_t *shapes);

#endif
