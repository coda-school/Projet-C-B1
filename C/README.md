# Correction projet C

## Installation

Pour ce projet il faut le compilateur `GCC` https://gcc.gnu.org/ et `make` https://www.gnu.org/software/make/. Ce projet a été développé sous Ubuntu WSL. 

Pour complier le projet il faut lancer la commande `make build`. Si la commande échoue, il faut créer manuellement le dossier `bin/` et réessayer.

## Création du projet

### Représentation des éléments

J'ai d'abord commencé par représenter les différentes formes et les différents styles dans le dossier `models/`. J'ai utilisé les structures, les alias de types, les énumérations et les unions. 

J'ai remarqué qu'un cercle est une ellipse particulière et que le carré est un rectangle particulier. Je n'ai donc pas besoin de m'occuper du cercle et du carré.

Mes formes et styles sont définis par:

- L'ellipse : un point et deux rayons
- Le rectangle : un point et deux tailles.
- La ligne : deux points.
- La polyline : une liste de points.
- Le polygon : une liste de points.
- Le chemin : une liste de commandes.
- Le groupe : une liste de formes.

Mes styles sont définis par :

- Les couleurs : 4 entiers non signés sur 8 bits.
- Les déplacements : un point.
- Les rotations : choix parmi  
    - Rotation circulaire : un entier
    - Inversion en X
    - Inversion en Y

Mon Svg est défini par :
- Un viewport : deux points
- Des formes : une liste de forme.

On remarque que l'on peut factoriser :

- La polyline et le polygon
- Le groupe et le SVG 

Le code C correspond à : 

```c
// ==================================================
// Points et liste chainée de points
// ==================================================

typedef struct point_s {
    int x;
    int y;
} point_t;

typedef struct point_node_s point_node_t;

struct point_node_s {
    point_node_t *next;
    point_t *point;
};

typedef struct point_list_s {
    unsigned int length;
    point_node_t *start;
} point_list_t;

// ==================================================
// Styles
// ==================================================

typedef struct color_s {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char transparency;
} color_t;

typedef struct flip_x_s { } flip_x_t;

typedef struct flip_y_s { } flip_y_t;

typedef union rotate_type_s {
    int circular;
    flip_x_t flip_x;
    flip_y_t flip_y;
} rotate_type_t;

typedef enum rotate_variant_e {
    CIRCULAR,
    FLIP_X,
    FLIP_Y
} rotate_variant_t;

typedef struct rotate_s {
    rotate_variant_t variant;
    rotate_type_t type;
} rotate_t;

typedef struct styles_s {
    color_t *fill;
    color_t *outline;
    rotate_t *rotate;
    point_t *translate;
} styles_t;

// ==================================================
// Chemins
// ==================================================

typedef point_t move_to_t;

typedef point_t line_to_t;

typedef int horizontal_line_to_t;

typedef int vertical_line_to_t;

typedef struct cubic_curve_to_s {
    point_t *point1;
    point_t *point2;
    point_t *point3;
} cubic_curve_to_t;

typedef struct cubic_curve_to_shorthand_s {
    point_t *point1;
    point_t *point2;
} cubic_curve_to_shorthand_t;

typedef struct quardratic_curve_to_s {
    point_t *point1;
    point_t *point2;
} quardratic_curve_to_t;

typedef point_t quadratic_curve_to_shorthand_t;

typedef struct end_of_path_s { } end_of_path_t;

typedef union path_element_type_s {
    move_to_t *move_to;
    line_to_t *line_to;
    horizontal_line_to_t horizontal_line_to;
    vertical_line_to_t vertical_line_to;
    cubic_curve_to_t *cubic_curve_to;
    cubic_curve_to_shorthand_t *cubic_curve_to_shorthand;
    quardratic_curve_to_t *quardratic_curve_to;
    quadratic_curve_to_shorthand_t *quadratic_curve_to_shorthand;
    end_of_path_t *end_of_path;
} path_element_type_t;

typedef enum path_element_variant_e {
    MOVE_TO,
    LINE_TO,
    VERTICAL_LINE_TO,
    HORIZONTAL_LINE_TO,
    CUBIC_CURVE_TO,
    CUBIC_CURVE_TO_SHORTHAND,
    QUADRATIC_CURVE_TO,
    QUADRATIC_CURVE_TO_SHORTHAND,
    END_OF_PATH
} path_element_variant_t;

typedef struct path_element_s {
    path_element_type_t *type;
    path_element_variant_t *variant;
} path_element_node_t;

typedef struct path_element_node_s path_element_node_t; 

struct path_element_node_s {
    path_element_node_t *next;
    path_element_t *path_element;
};

typedef struct path_element_list_s {
    unsigned int length;
    path_element_node_t *start;
} path_element_list_t;

// ==================================================
// Formes et liste chaînée de formes
// ==================================================

typedef struct shape_node_s shape_node_t;

typedef struct shape_list_s {
    unsigned int length;
    shape_node_t *start;
} shape_list_t;

typedef struct ellipse_s {
    point_t *origin;
    unsigned int radius_x;
    unsigned int radius_y;
} ellipse_t;

typedef struct rectangle_s {
    point_t *origin;
    unsigned int width;
    unsigned int length;
} rectangle_t;

typedef struct line_s {
    point_t *from;
    point_t *to;
} line_t;

typedef point_list_t polyline_t;

typedef point_list_t polygon_t;

typedef path_element_list_t path_t;

typedef shape_list_t group;

typedef union shape_type_u {
    ellipse_t *ellipse;
    rectangle_t *rectangle;
    line_t *line;
    polyline_t *polyline;
    polygon_t *polygon;
    path_t *path;
    groupt_t *group;
} shape_type_t;

typedef enum shape_variant_e {
    ELLIPSE,
    RECTANGLE,
    LINE,
    POLYLINE,
    POLYGON,
    PATH,
    GROUP
} shape_variant_t;

typedef struct shape_s {
    shape_variant_t *shape_variant;
    shape_type_t *shape_type;
    styles_t *styles;
} shape_t;

// ==================================================
// Viewport et SVG
// ==================================================

typedef struct viewport_s {
    point_t *from;
    point_t *to;
} viewport_t;

typedef struct svg_s {
    viewport_t *viewport;
    shape_list_t *shapes;
} svg_t;
```

### Manipulation des structures, enums et unions

Pour simplifier l'utilisation des structures, des enums et des unions je vous invite à écrire les fonctions suivantes:

- create
- free
- to_string
- clone
- print
- get
- set

Voici un exemple pour manipuler la structure `style_s` :

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STYLES_TO_STRING_SIZE 1024

styles_t *create_styles(color_t *fill, color_t *outline, point_t *translate, rotate_t *rotate) {
    styles_t *styles = (styles_t *) malloc(sizeof(styles_t));

    if (styles == NULL) {
        fprintf(stderr, "Could not malloc new styles.\n");
        exit(1);
    }

    styles->fill = fill;
    styles->outline = outline;
    styles->outline = outline;
    styles->translate = translate;
    styles->translate = translate;
    styles->rotate = rotate;
    return styles;
}

void free_styles(styles_t *styles) {
    if (styles == NULL) return;
    free_color(styles->fill);
    free_color(styles->outline);
    free_translate(styles->translate);
    free_rotate(styles->rotate);
    free(styles);
}

char *styles_to_string(styles_t *styles) {
    if (styles == NULL) return NULL;

    char *str = (char *) malloc(sizeof(char) * STYLES_TO_STRING_SIZE);
    
    if (str == NULL) {
        fprintf(stderr, "Could not malloc styles string.\n");
        exit(1);
    }

    sprintf(
        str, 
        "styles=\"fill: %s; outline: %s; transform: translate(%s) %s;\"",
        color_to_string(styles->fill),
        color_to_string(styles->outline),
        point_to_string(styles->translate),
        rotate_to_string(styles->rotate)
    );

    return str;
}

styles_t *clone_styles(styles_t *styles) {
    if (styles == NULL) return NULL;
    return create_styles(
        clone_color(styles->fill),
        clone_color(styles->outline),
        clone_point(styles->translate),
        clone_rotate(styles->rotate)
    );
}

void print_styles(styles_t *styles) {
    if (styles == NULL) return;
    printf("STYLES { FILL=");
    print_color(styles->fill);
    printf("; OUTLINE="); 
    print_color(styles->outline);
    printf("; TRANSLATE="); 
    print_point(styles->translate);
    printf("; ROTATE="); 
    print_rotate(styles->rotate);
    printf(" }\n"); 
}

color_t *get_fill(styles_t *styles) {
    if (styles == NULL) return NULL;
    return styles->fill;
}

color_t *get_outline(styles_t *styles) {
    if (styles == NULL) return NULL;
    return styles->outline;
}

point_t *get_translate(styles_t *styles) {
    if (styles == NULL) return NULL;
    return styles->translate;
}

rotate_t *get_rotate(styles_t *styles) {
    if (styles == NULL) return NULL;
    return styles->rotate;
}

void set_fill(styles_t *styles, color_t *color) {
    if (styles == NULL) return;
    styles->fill = color;
}

void set_outline(styles_t *styles, color_t *color) {
    if (styles == NULL) return;
    styles->outline = color;
}

void set_rotate(styles_t *styles, rotate_t *rotate) {
    if (styles == NULL) return;
    styles->rotate = rotate;
}

void set_translate(styles_t *styles, point_t *translate) {
    if (styles == NULL) return;
    styles->translate = translate;
}
```

### L'interface utilisateur

Une interface utilisateur se décompose en deux éléments : l'affichage et les interactions utilisateurs. Un bon dialogue utilisateur est essentiel pour construire une interface ergonomique et produire un code propre et cohérent. J'ai donc commencé par écrire des fonctions pour demander des valeurs à l'utilisateur.

Lorsque l'on demande une valeur à l'utilisateur il faut la valider ! Par exemple, si l'on demande un entier à un utilisateur, il faut :

- S'assurer que l'utilisateur écrit un entier (il peut y avoir une faute de frappe par exemple).
- S'assurer que l'entier corresponde au contexte :
    - Si l'on demande un age, il faut un entier positif.
    - Si l'on demande un index d'un tableau, il faut borner l'entier.
    - ...
- Permettre à l'utilisateur d'annuler l'opération. 


Pour simplifier et factoriser le code, j'ai créé des fonctions pour demander des valeurs à l'utilisateur. Voici un exemple :

```c
typedef enum cli_output_e { 
    CLI_VALID, 
    CLI_INVALID, 
    CLI_EMPTY 
} cli_output_t;

cli_output_t cli_ask_for_int(int *value) {
  char input[100];
  char *endptr;
  cli_print_content("Enter an integer value (or nothing to exit) : ");
  if (fgets(input, sizeof(input), stdin) == NULL)
    return CLI_INVALID;
  if (input[0] == '\n')
    return CLI_EMPTY;

  input[strcspn(input, "\n")] = '\0';

  long num = strtol(input, &endptr, 10);

  if (*endptr != '\0' || num < INT_MIN || num > INT_MAX)
    return CLI_INVALID;

  *value = (int)num;
  return CLI_VALID;
}
```

Ensuite, on utilise ces fonctions pour créer des menus et permettre à l'utilisateur d'utiliser l'application.

### Sauvegarde au format SVG

Comme pour la partie modélisation, j'ai créé une fonction pour exporter les formes, une fonction pour exporter les styles, etc...  

### Import et export

Avant de faire l'export j'ai décidé de travailler sur l'import. Pour importer des données depuis un fichier, on construit un `parser`. Un parser est un outil qui lit caractère par caractère un fichier et traduit le texte en données structurées. 

Généralement, il faut construire une grammaire pour définir les règles de "traduction". Voici la grammaire simplifiée associée à mon projet :

```
SVG := <svg viewport="POINT POINT POINT POINT"> SHAPE_LIST </svg> ;;

GROUP := <group GROUP_PARAMETER> SHAPE_LIST </group> ;;

GROUP_PARAMETER := 
    | GROUP_PARAMETER GROUP_PARAMETER
    | STYLES
;;

SHAPE_LIST :=
    | SHAPE_LIST SHAPE_LIST
    | SHAPE
;;

SHAPE := 
    | ELLIPSE
    | RECTANGLE
    | LINE 
    | POLYLINE
    | POLYGON
    | PATH
    | GROUP
;;


PATH := <draw PATH_PARAMETER /> ;;

PATH_PARAMETER := 
    | PATH_PARAMETER PATH_PARAMETER
    | points="PATH_ELEMENT_LIST"
    | STYLES
;;

PATH_ELEMENT_LIST :=
    | PATH_ELEMENT_LIST PATH_ELEMENT_LIST
    | PATH_ELEMENT
;;

PATH_ELEMENT := 
    | M POINT
    | L POINT
    | H NUMBER
    | V NUMBER
    | C POINT POINT POINT
    | S POINT POINT
    | Q POINT POINT
    | T POINT
    | Z
;;


POLYGON := <polygon POINT_LIST_PARAMETER /> ;;

MULTILINE := <multiline POINT_LIST_PARAMETER /> ;;

POINT_LIST_PARAMETER :=
    | POINT_LIST_PARAMETER POINT_LIST_PARAMETER
    | points="POINT_LIST"
    | STYLES
;;

POINT_LIST := 
    | POINT_LIST POINT_LIST
    | POINT
;;

LINE := <line LINE_PARAMETER /> ;;

LINE_PARAMETER :=
    | LINE_PARAMETER LINE_PARAMETER
    | x1="NUMBER"
    | y1="NUMBER"
    | x2="NUMBER"
    | y2="NUMBER"
    | STYLES
;;


RECTANGLE := <rectangle RECTANGLE_PARAMETER /> ;;

RECTANGLE_PARAMETER :=
    | RECTANGLE_PARAMETER RECTANGLE_PARAMETER
    | x="NUMBER"
    | y="NUMBER"
    | width="UNSIGNED_NUMBER"
    | height="UNSIGNED_NUMBER"
    | STYLES
;;


ELLIPSE := <ellipse ELLIPSE_PARAMETER /> ;;

ELLIPSE_PARAMETER :=
    | ELLIPSE_PARAMETER ELLIPSE_PARAMETER
    | x="NUMBER"
    | y="NUMBER"
    | width="UNSIGNED_NUMBER"
    | height="UNSIGNED_NUMBER"
    | STYLES
;;


STYLES := 
    | fill="COLOR"
    | outline="COLOR"
    | rotate="ROTATE"
    | translate="POINT"
;;

ROTATE := X | Y | NUMBER ;;

COLOR := #[0-F][0-F][0-F][0-F][0-F][0-F][0-F][0-F] ;;

POINT := NUMBER NUMBER ;;

NUMBER := -[0-9]* | UNSIGNED_NUMBER ;;

UNSIGNED_NUMBER := [0-9]* ;;
```

Avant de traduire la grammaire en code, il faut accéder au fichier. En cas d'échec de la traduction, il est intéressant d'indiquer où est-ce que l'erreur est apparue. Je vous invite donc à créer la structure suivante pour conserver en mémoire le numéro de ligne et la position du curseur :

```c
typedef struct serdelizer_s {
  int line;
  int position;
  FILE *file;
  char last_consumed;
} serdelizer_t;
```

Pour factoriser et simplifier le code, j'ai créé les fonctions suivantes:

- `get_next_char` qui retourne le prochain caractère lu (et met à jour la structure).
- `get_next_non_whitespace_char` qui retourne le prochain caractère lu qui n'est pas un caractère d'espacement (et met à jour la structure).

```c
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
```

Pour convertir la grammaire en code, il faut créer une fonction pour chaque règle de la grammaire.

Pour sauver le SVG, il suffit de procéder comme pour l'export en prenant soin de respecter le format de la grammaire.
