#ifndef CODA_ROTATE
#define CODA_ROTATE

/**
 * Represents the flip X rotate variant.
 */
typedef struct flipx_s {
} flipx_t;

/**
 * Represents the flip Y rotate variant.
 */
typedef struct flipy_s {
} flipy_t;

/**
 * Represents the circular rotation variant.
 * This is an overload of the integer type.
 */
typedef int circular_t;

/**
 * Lists all the rotation variants.
 */
typedef enum rotation_variants_e {
  FLIP_X,
  FLIP_Y,
  CIRCULAR
} rotation_variants_t;

/**
 * Groups all rotation variants.
 * @param flip_x the flip X rotate variant's pointer.
 * @param flip_y the flip Y rotate variant's pointer.
 * @param circular the circular rotation variant's value.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
typedef union rotate_union_u {
  flipx_t *flip_x;
  flipx_t *flip_y;
  circular_t circular;
} rotate_union_t;

/**
 * Represents a rotation.
 * @param variant  defines which rotation variant is active.
 * @param rotation holds the active rotation variant.
 * @see rotation_variants_t.
 * @see rotate_union_t.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
typedef struct rotate_s {
  rotation_variants_t variant;
  rotate_union_t rotation;
} rotate_t;

/**
 * Creates a new rotation with the flip X variant.
 * Note that this function allocates memory.
 * @return the new rotation's pointer.
 * @see rotation_variants_t.
 * @see rotate_union_t.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
rotate_t *new_flipx();

/**
 * Creates a new rotation with the flip Y variant.
 * Note that this function allocates memory.
 * @return the new rotation's pointer.
 * @see rotation_variants_t.
 * @see rotate_union_t.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
rotate_t *new_flipy();

/**
 * Creates a new rotation with the circular variant.
 * Note that this function allocates memory.
 * Note that the given circular rotation value will be modulated by 360 bringing
 * it in the [-359, 359] range.
 * @param degree the circular rotation's value.
 * @return the new rotation's pointer.
 * @see rotation_variants_t.
 * @see rotate_union_t.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
rotate_t *new_circular(int degree);

/**
 * Duplicates the given rotation.
 * Note that this function allocates memory.
 * @param rotate the rotation to be duplicated.
 * @return the duplicated rotation's pointer.
 * @see rotation_variants_t.
 * @see rotate_union_t.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
rotate_t *clone_rotate(rotate_t *rotate);

/**
 * Destroys the given rotation.
 * Note that the function frees memory.
 * @param rotate the rotation to be destroyed.
 * @see rotation_variants_t.
 * @see rotate_union_t.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
void free_rotate(rotate_t *rotate);

/**
 * Prints out the given rotation.
 * Note that this function is for debug purposes only.
 * @param rotate the rotation to be printed out.
 * @see rotation_variants_t.
 * @see rotate_union_t.
 * @see flipx_t.
 * @see flipy_t.
 * @see circular_t.
 */
void print_rotate(rotate_t *rotate);

#endif
