# Projet C : Editeur de SVG : Version Rust

## Installation

Pour tester ce code il faut installer le langage Rust : https://rust-lang.org/tools/install/. La commande `cargo --version` permet de vérifier si le langage est correctement installé. Pour exécuter le code, il faut entrer la commande `cargo run`.

## Quelques notions de Rust pour comprendre le code

Rust détermine automatiquement le type des variables. Il n'est donc pas nécessaire de déclarer le type des variables.

```rust
let number = 10;
let text = "A string";
```

Par défaut les variables sont immutables, c’est-à-dire que l’on ne peut pas changer la valeur d’une variable. Pour rendre une variable mutable, on utilise le mot clé `mut`. 

```rust
let mut number = 10;
number = 20;
```

Il y a deux éléments importants dans le langage Rust : Le « ownership » et le « borrowing ». Pour faire simple :
-	Le « ownership » signifie qu’une valeur est associée à un unique propriétaire (une variable, une fonction, …). Ce propriétaire est le seul à avoir les droits de modification sur la variable.
-	Le « borrowing » permet d’emprunter une valeur à un propriétaire. Un emprunt permet de lire la valeur mais pas de la modifier. Le symbole `&` représente un emprunt.

```rust
// La fonction devient propriétaire de la valeur.
fn fonction1(a: i32) {
    println!("{a}");
}

// La fonction emprunte la valeur.
fn fonction2(a: &i32) {
    println!("{a}");
}
```

Comme en C, on utilise des structures pour créer de nouveaux types. En revanche, en Rust, les enums et les unions ne font qu'un ! Le mot clé `match` (équivalent de `switch` en C) permet de déterminer de quelle variante il s'agit :

```rust 
struct Point {
    x: i32,
    y: i32
}

enum Shape {
    Ellipse(Ellipse),
    Rectangle(Rectangle),
    Line(Line),
    Polyline(Polyline),
    Polygon(Polygon),
    Path(Path),
    Group(Group)
}

fn test(shape: Shape) {
    match shape {
        Shape::Ellipse(ellipse) => {},
        Shape::Rectangle(rectangle) => {},
        Shape::Line(line) => {},
        Shape::Polyline(polyline) => {},
        Shape::Polygon(polygon) => {},
        Shape::Path(path) => {},
        Shape::Group(group) => {}
    }
}
```

Il est possible de créer des fonctions génériques, à savoir des fonctions qui peuvent accepter différents types. On utilise la syntaxe `<T>` pour l'indiquer :

```rust
fn do_something<T>(value: T) {
    // ...
}

do_something<&str>("text");
do_something<bool>(true);
do_something<i32>(-100);
```

Il est possible de filtrer les types avec la syntaxe `where` :

```rust
fn print<T>(value: T) 
where
    T: Display
{
    print!("{value}");
}
```

Les erreurs et la valeur NULL n'existent pas en Rust. Pour les représenter, on utilise les énumérations `Option<T>` et `Result<T>`.

```rust
fn process_int<T>(value: i32) -> Option<T> {
    if value < 0 {
        return None;
    }
    return Some(...);
}

fn process_age<T, U>(value: i32) -> Result<T, U> {
    if value < 0 {
        return Err(...);
    }
    return Ok(...);
}
```

En Rust, on utilise le block `impl` pour lier des fonctions à des structures et des énumérations.

```rust
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    pub fn new(x: i32, y: i32) -> Self {
        Self { x, y }
    }

    pub fn print(&self) {
        println!("{}{}", self.x, self.y);
    }
}

let p = Point::new();
p.print();
```

## Création du projet

Pour la majorité du projet en Rust, j'ai suivi le déroulé du projet en C. Je vais vous présenter les grandes différences entre les deux versions.

### Représentation des éléments

La représentation des éléments est simplifiée en Rust car les unions et les énumérations sont liées et car la liste chaînée est déjà prédéfinie par le langage : 

```rust
pub struct Point {
    pub x: i32,
    pub y: i32,
}

pub enum Rotate {
    Circular(u16),
    Flipx,
    Flipy,
}

pub struct Color {
    pub red: u8,
    pub green: u8,
    pub blue: u8,
    pub transparency: u8,
}

pub struct Styles {
    pub translate: Point,
    pub rotate: Rotate,
    pub fill: Color,
    pub outline: Color,
}

pub struct Ellipse {
    pub origin: Point,
    pub radius_x: u32,
    pub radius_y: u32,
}

pub struct Rectangle {
    pub origin: Point,
    pub width: u32,
    pub height: u32,
}

pub struct Line {
    pub from: Point,
    pub to: Point,
}

pub struct Polyline(pub Vec<Point>);

pub struct Polygon(pub Vec<Point>);

pub enum PathCommand {
    MoveTo(Point),
    LineTo(Point),
    HorizontalLineTo(i32),
    VerticalLineTo(i32),
    CubicCurveTo(Point, Point, Point),
    CubicCurveToShorthand(Point, Point),
    QuadraticCurveTo(Point, Point),
    QuadraticCurveToShorthand(Point),
    EndOfPath,
}

pub struct Path(pub Vec<PathCommand>);

pub struct Group(pub Vec<Box<Shape>>);

pub enum ShapeType {
    Ellipse(Ellipse),
    Rectangle(Rectangle),
    Line(Line),
    Polyline(Polyline),
    Polygon(Polygon),
    Group(Group),
    Path(Path),
}

pub struct Shape {
    pub shape: ShapeType,
    pub styles: Styles,
}

pub struct Viewport {
    pub from: Point,
    pub to: Point,
}

pub struct Svg {
    pub viewport: Viewport,
    pub shapes: Vec<Box<Shape>>,
}
```

### Manipulation des structures, enums 

Comme pour le C, j'ai développé des fonctions pour manipuler mes structures et mes enums. Rust gère automatiquement la mémoire donc il n'y a pas de fonctions free. Voici quelques exemples :

```rust
impl Default for Ellipse {
    fn default() -> Self {
        Self {
            origin: Default::default(),
            radius_x: Default::default(),
            radius_y: Default::default(),
        }
    }
}

impl Ellipse {
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Ellipse {
    fn print(&self, _depth: u32) {
        print!("<ellipse origin=\"");
        self.origin.print(_depth);
        print!(
            "\" radius_x=\"{}\" radius_y=\"{}\" ",
            self.radius_x, self.radius_y
        );
    }
}
```

### L'interface utilisateur

Même principe que pour le code C.

### Sauvegarde au format SVG

Même principe que pour le code C.

### Import et export

Contrairement au langage C, Rust et le module `serde` permettent de rapidement exporter et importer des données. Il suffit d'ajouter un entête à chaque structure et fonction pour y arriver.

```rust
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
pub struct Ellipse {
    pub origin: Point,
    pub radius_x: u32,
    pub radius_y: u32,
}
```