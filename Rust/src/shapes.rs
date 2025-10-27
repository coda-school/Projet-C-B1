use serde::{Deserialize, Serialize};

use crate::styles::*;
use crate::utils::{print_tabs, Point};

/// Defines the common behavior to print a formatted versions of values.
///
/// # Arguments
///
/// - `&self` (`T`) - The value to print.
/// - `depth` (`u32`) - The number of tabs to print.
pub trait Print {
    fn print(&self, depth: u32);
}

/// Defines the ellipse shape.
///
/// # Fields
///
/// - `origin` (`Point`) - The ellipse's center.
/// - `radius_x` (`u32`) - The ellipse's x radius.
/// - `radius_y` (`u32`) - The ellipse's y radius.
///
/// # Examples
///
/// ```
/// let s = Ellipse {
///     origin: value,
///     radius_x: value,
///     radius_y: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Ellipse {
    pub origin: Point,
    pub radius_x: u32,
    pub radius_y: u32,
}

/// Defines the rectangle shape.
///
/// # Fields
///
/// - `origin` (`Point`) - The rectangle's center.
/// - `width` (`u32`) - The rectangle's width.
/// - `height` (`u32`) - The rectangle's height.
///
/// # Examples
///
/// ```
/// let s = Rectangle {
///     origin: value,
///     width: value,
///     height: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Rectangle {
    pub origin: Point,
    pub width: u32,
    pub height: u32,
}

/// Represents the line shape.
///
/// # Fields
///
/// - `from` (`Point`) - The line's origin.
/// - `to` (`Point`) - The line's destination.
///
/// # Examples
///
/// ```
/// let s = Line {
///     from: value,
///     to: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Line {
    pub from: Point,
    pub to: Point,
}

/// Represents the polyline shape.
///
/// # Fields
///
/// - `field_0` (`Vec<Point>`) - The polyline's points.
///
/// # Examples
///
/// ```
/// let polyline = Polyline(vec![]);
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Polyline(pub Vec<Point>);

/// Represents the polygon shape.
///
/// # Fields
///
/// - `field_0` (`Vec<Point>`) - The polygon's points.
///
/// # Examples
///
/// ```
/// let polygon = Polygon(vec![]);
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Polygon(pub Vec<Point>);

/// Represents all the available path commands.
///
/// # Variants
///
/// - `MoveTo(Point)` - Move to command.
/// - `LineTo(Point)` - Line to command.
/// - `HorizontalLineTo(i32)` - Horizontal line to command.
/// - `VerticalLineTo(i32)` - Vertical line to command.
/// - `CubicCurveTo(Point, Point, Point)` - Cubic curve to command.
/// - `CubicCurveToShorthand(Point, Point)` - Cubic curve to shorthand command.
/// - `QuadraticCurveTo(Point, Point)` - Quadratic curve to command.
/// - `QuadraticCurveToShorthand(Point)` - Quadratic curve to shorthand command.
/// - `EndOfPath` - End of path command.
///
/// # Examples
///
/// ```
/// let pathcommand = PathCommand::MoveTo;
/// match pathcommand {
///     PathCommand::MoveTo(v0) => {},
///     PathCommand::LineTo(v0) => {},
///     PathCommand::HorizontalLineTo(v0) => {},
///     PathCommand::VerticalLineTo(v0) => {},
///     PathCommand::CubicCurveTo(v0, v1, v2) => {},
///     PathCommand::CubicCurveToShorthand(v0, v1) => {},
///     PathCommand::QuadraticCurveTo(v0, v1) => {},
///     PathCommand::QuadraticCurveToShorthand(v0) => {},
///     PathCommand::EndOfPath => {},
/// }
/// ```
#[derive(Debug, Serialize, Deserialize, Clone, Copy)]
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

/// Represents the path shape.
///
/// # Fields
///
/// - `field_0` (`Vec<PathCommand>`) - The path's commands .
///
/// # Examples
///
/// ```
/// let path = Path(vec![]);
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Path(pub Vec<PathCommand>);

/// Represents the group shape.
///
/// # Fields
///
/// - `field_0` (`Vec<Box<Shape>>`) - The group's shapes.
///
/// # Examples
///
/// ```
/// let group = Group(vec![]);
/// ```    
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Group(pub Vec<Box<Shape>>);

/// Represents all available shapes.
///
/// # Variants
///
/// - `Ellipse(Ellipse)` - The ellipse.
/// - `Rectangle(Rectangle)` - The rectangle.
/// - `Line(Line)` - The line.
/// - `Polyline(Polyline)` - The polyline.
/// - `Polygon(Polygon)` - The polygon.
/// - `Group(Group)` - The group.
/// - `Path(Path)` - The path.
///
/// # Examples
///
/// ```
/// let shapetype = ShapeType::Ellipse;
/// match shapetype {
///     ShapeType::Ellipse(v0) => {},
///     ShapeType::Rectangle(v0) => {},
///     ShapeType::Line(v0) => {},
///     ShapeType::Polyline(v0) => {},
///     ShapeType::Polygon(v0) => {},
///     ShapeType::Group(v0) => {},
///     ShapeType::Path(v0) => {},
/// }
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub enum ShapeType {
    Ellipse(Ellipse),
    Rectangle(Rectangle),
    Line(Line),
    Polyline(Polyline),
    Polygon(Polygon),
    Group(Group),
    Path(Path),
}

/// Represents a shape.
///
/// # Fields
///
/// - `shape` (`ShapeType`) - The shape's data.
/// - `styles` (`Styles`) - The shape's styles.
///
/// # Examples
///
/// ```
/// let s = Shape {
///     shape: value,
///     styles: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Shape {
    pub shape: ShapeType,
    pub styles: Styles,
}

/// Represents the SVG's viewport.
///
/// # Fields
///
/// - `from` (`Point`) - The viewport's start point.
/// - `to` (`Point`) - The viewport's end point.
///
/// # Examples
///
/// ```
/// let s = Viewport {
///     from: value,
///     to: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Viewport {
    pub from: Point,
    pub to: Point,
}

/// Represents an SVG.
///
/// # Fields
///
/// - `viewport` (`Viewport`) - The SVG's viewport.
/// - `shapes` (`Vec<Box<Shape>>`) - The SVG's shapes.
///
/// # Examples
///
/// ```
/// let s = Svg {
///     viewport: value,
///     shapes: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize)]
pub struct Svg {
    pub viewport: Viewport,
    pub shapes: Vec<Box<Shape>>,
}

impl Default for Ellipse {
    /// The ellipse's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new ellipse.
    ///
    /// # Examples
    ///
    /// ```
    /// let ellipse = Ellipse::default();
    /// ```
    fn default() -> Self {
        Self {
            origin: Default::default(),
            radius_x: Default::default(),
            radius_y: Default::default(),
        }
    }
}

impl Default for Rectangle {
    /// The rectangle's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new rectangle.
    ///
    /// # Examples
    ///
    /// ```
    /// let rectangle = Rectangle::default();
    /// ```
    fn default() -> Self {
        Self {
            origin: Default::default(),
            width: Default::default(),
            height: Default::default(),
        }
    }
}

impl Default for Line {
    /// The line's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new line.
    ///
    /// # Examples
    ///
    /// ```
    /// let line = Line::default();
    /// ```
    fn default() -> Self {
        Self {
            from: Default::default(),
            to: Default::default(),
        }
    }
}

impl Default for Polyline {
    /// The polyline's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new polyline.
    ///
    /// # Examples
    ///
    /// ```
    /// let polyline = Polyline::default();
    /// ```
    fn default() -> Self {
        Self(Default::default())
    }
}

impl Default for Polygon {
    /// The polygon's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new polygon.
    ///
    /// # Examples
    ///
    /// ```
    /// let polygon = Polygon::default();
    /// ```
    fn default() -> Self {
        Self(Default::default())
    }
}

impl Default for Path {
    /// The path's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new path.
    ///
    /// # Examples
    ///
    /// ```
    /// let path = Path::default();
    /// ```
    fn default() -> Self {
        Self(Default::default())
    }
}

impl Default for Group {
    /// The group's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new group.
    ///
    /// # Examples
    ///
    /// ```
    /// let group = Group::default();
    /// ```
    fn default() -> Self {
        Self(Default::default())
    }
}

impl Default for Viewport {
    /// The viewport's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new viewport.
    ///
    /// # Examples
    ///
    /// ```
    /// let viewport = Viewport::default();
    /// ```
    fn default() -> Self {
        Self {
            from: Default::default(),
            to: Default::default(),
        }
    }
}

impl Default for Svg {
    /// The SVG's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new SVG.
    ///
    /// # Examples
    ///
    /// ```
    /// let svg = Svg::default();
    /// ```
    fn default() -> Self {
        Self {
            viewport: Default::default(),
            shapes: Default::default(),
        }
    }
}

impl Ellipse {
    /// The ellipse's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new ellipse.
    ///
    /// # Examples
    ///
    /// ```
    /// let ellipse = Ellipse::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Ellipse {
    /// Prints out the given ellipse.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Ellipse`) - The ellipse to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let ellipse = Ellipse::new();
    /// ellipse.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!("<ellipse origin=\"");
        self.origin.print(_depth);
        print!(
            "\" radius_x=\"{}\" radius_y=\"{}\" ",
            self.radius_x, self.radius_y
        );
    }
}

impl Rectangle {
    /// The rectangle's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new rectangle.
    ///
    /// # Examples
    ///
    /// ```
    /// let rectangle = Rectangle::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Rectangle {
    /// Prints out the given rectangle.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Rectangle`) - The rectangle to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let rectangle = Rectangle::new();
    /// rectangle.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!("<rectangle origin=\"");
        self.origin.print(_depth);
        print!("\" width=\"{}\" height=\"{}\" ", self.width, self.height);
    }
}

impl Line {
    /// The line's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new line.
    ///
    /// # Examples
    ///
    /// ```
    /// let line = Line::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Line {
    /// Prints out the given line.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Line`) - The line to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let line = Line::new();
    /// line.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!("<line from=\"");
        self.from.print(_depth);
        print!("\" to=\"");
        self.to.print(_depth);
        print!("\" ");
    }
}

impl Polyline {
    /// The polyline's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new polyline.
    ///
    /// # Examples
    ///
    /// ```
    /// let polyline = Polyline::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Polyline {
    /// Prints out the given polyline.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Polyline`) - The polyline to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let polyline = Polyline::new();
    /// polyline.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!("<polyline points=\"");
        for point in self.0.iter() {
            point.print(_depth);
            print!(", ");
        }
        print!("\" ");
    }
}

impl Polygon {
    /// The polygon's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new polygon.
    ///
    /// # Examples
    ///
    /// ```
    /// let polygon = Polygon::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Polygon {
    /// Prints out the given polygon.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Polygon`) - The polygon to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let polygon = Polygon::new();
    /// polygon.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!("<polygon points=\"");
        for point in self.0.iter() {
            point.print(_depth);
            print!(", ");
        }
        print!("\" ");
    }
}

impl PathCommand {
    /// The move to path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new move to path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let move_to = PathCommand::new_move_to();
    /// ```
    pub fn new_move_to() -> Self {
        Self::MoveTo(Point::default())
    }

    /// The line to path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new line to path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let line_to = PathCommand::new_line_to();
    /// ```
    pub fn new_line_to() -> Self {
        Self::LineTo(Point::default())
    }

    /// The horizontal line to path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new horizontal line to path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let horizontal_line_to = PathCommand::new_horizontal_line_to();
    /// ```
    pub fn new_horizontal_line_to() -> Self {
        Self::HorizontalLineTo(0)
    }

    /// The vertical line to path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new vertical line to path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let vertical_line_to = PathCommand::new_vertical_line_to();
    /// ```
    pub fn new_vertical_line_to() -> Self {
        Self::VerticalLineTo(0)
    }

    /// The cubic curve to path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new cubic curve to path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let cubic_curve_to = PathCommand::new_cubic_curve_to();
    /// ```
    pub fn new_cubic_curve_to() -> Self {
        Self::CubicCurveTo(Point::default(), Point::default(), Point::default())
    }

    /// The cubic curve to shorthand path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new cubic curve to shorthand path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let cubic_curve_to_shorthand = PathCommand::new_cubic_curve_to_shorthand();
    /// ```
    pub fn new_cubic_curve_to_shorthand() -> Self {
        Self::CubicCurveToShorthand(Point::default(), Point::default())
    }

    /// The quadratic curve to path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new quadratic curve to path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let quadratic_curve_to = PathCommand::new_quadratic_curve_to();
    /// ```
    pub fn new_quadratic_curve_to() -> Self {
        Self::QuadraticCurveTo(Point::default(), Point::default())
    }

    /// The quadratic curve to shorthand path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new quadratic curve to shorthand path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let quadratic_curve_to_shorthand = PathCommand::new_quadratic_curve_to_shorthand();
    /// ```
    pub fn new_quadratic_curve_to_shorthand() -> Self {
        Self::QuadraticCurveToShorthand(Point::default())
    }

    /// The end of path path command's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new end of path path command.
    ///
    /// # Examples
    ///
    /// ```
    /// let end_of_path = PathCommand::new_end_of_path();
    /// ```
    pub fn new_end_of_path() -> Self {
        Self::EndOfPath
    }
}

impl Print for PathCommand {
    /// Prints out the given path command.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&PathCommand`) - The path command to print.
    /// - `depth` (`u32`) - The number of tabs to print.
    ///
    /// # Examples
    ///
    /// ```
    /// let path_command = PathCommand::new_end_of_path();
    /// path_command.print(0);
    /// ```
    fn print(&self, depth: u32) {
        match self {
            PathCommand::MoveTo(point) => {
                print!("M ");
                point.print(depth);
            }
            PathCommand::LineTo(point) => {
                print!("L ");
                point.print(depth);
            }
            PathCommand::HorizontalLineTo(to) => print!("H {to}"),
            PathCommand::VerticalLineTo(to) => print!("V {to}"),
            PathCommand::CubicCurveTo(point, point1, point2) => {
                print!("C ");
                point.print(depth);
                print!(" ");
                point1.print(depth);
                print!(" ");
                point2.print(depth);
            }
            PathCommand::CubicCurveToShorthand(point, point1) => {
                print!("S ");
                point.print(depth);
                print!(" ");
                point1.print(depth);
            }
            PathCommand::QuadraticCurveTo(point, point1) => {
                print!("Q ");
                point.print(depth);
                print!(" ");
                point1.print(depth);
            }
            PathCommand::QuadraticCurveToShorthand(point) => {
                print!("T ");
                point.print(depth);
            }
            PathCommand::EndOfPath => print!("Z"),
        }
    }
}

impl Path {
    /// The path's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new path.
    ///
    /// # Examples
    ///
    /// ```
    /// let path = Path::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Path {
    /// Prints out the given path.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Path`) - The path to print.
    /// - `depth` (`u32`) - The number of tabs to print.
    ///
    /// # Examples
    ///
    /// ```
    /// let path = Path::new();
    /// path.print(0);
    /// ```
    fn print(&self, depth: u32) {
        print_tabs(depth);
        print!("<path d=\"");
        for command in self.0.iter() {
            command.print(depth);
            print!(" ");
        }
        print!("\" ");
    }
}

impl Group {
    /// The group's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new group.
    ///
    /// # Examples
    ///
    /// ```
    /// let group = Group::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Group {
    /// Prints out the given group.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Group`) - The group to print.
    /// - `depth` (`u32`) - The number of tabs to print.
    ///
    /// # Examples
    ///
    /// ```
    /// let group = Group::new();
    /// group.print(0);
    /// ```
    fn print(&self, depth: u32) {
        for shape in self.0.iter() {
            shape.print(depth + 1);
        }
    }
}

impl Shape {
    /// Creates a new ellipse shape.
    ///
    /// # Arguments
    ///
    /// - `ellipse` (`Ellipse`) - The shape's ellipse data.
    ///
    /// # Returns
    ///
    /// - `Self` - The new shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_ellipse(Ellipse::new());
    /// ```
    pub fn new_ellipse(ellipse: Ellipse) -> Self {
        Self {
            shape: ShapeType::Ellipse(ellipse),
            styles: Styles::default(),
        }
    }

    /// Creates a new rectangle shape.
    ///
    /// # Arguments
    ///
    /// - `rectangle` (`Rectangle`) - The shape's rectangle data.
    ///
    /// # Returns
    ///
    /// - `Self` - The new shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_rectangle(Rectangle::new());
    /// ```
    pub fn new_rectangle(rectangle: Rectangle) -> Self {
        Self {
            shape: ShapeType::Rectangle(rectangle),
            styles: Styles::default(),
        }
    }

    /// Creates a new line shape.
    ///
    /// # Arguments
    ///
    /// - `line` (`Line`) - The shape's line data.
    ///
    /// # Returns
    ///
    /// - `Self` - The new shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_line(Line::new());
    /// ```
    pub fn new_line(line: Line) -> Self {
        Self {
            shape: ShapeType::Line(line),
            styles: Styles::default(),
        }
    }

    /// Creates a new polyline shape.
    ///
    /// # Arguments
    ///
    /// - `polyline` (`Polyline`) - The shape's polyline data.
    ///
    /// # Returns
    ///
    /// - `Self` - The new shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_polyline(Polyline::new());
    /// ```
    pub fn new_polyline(polyline: Polyline) -> Self {
        Self {
            shape: ShapeType::Polyline(polyline),
            styles: Styles::default(),
        }
    }

    /// Creates a new polygon shape.
    ///
    /// # Arguments
    ///
    /// - `polygon` (`Polygon`) - The shape's polygon data.
    ///
    /// # Returns
    ///
    /// - `Self` - The new shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_polygon(Polygon::new());
    /// ```
    pub fn new_polygon(polygon: Polygon) -> Self {
        Self {
            shape: ShapeType::Polygon(polygon),
            styles: Styles::default(),
        }
    }

    /// Creates a new group shape.
    ///
    /// # Arguments
    ///
    /// - `group` (`Group`) - The shape's group data.
    ///
    /// # Returns
    ///
    /// - `Self` - The new shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_group(Group::new());
    /// ```
    pub fn new_group(group: Group) -> Self {
        Self {
            shape: ShapeType::Group(group),
            styles: Styles::default(),
        }
    }

    /// Creates a new path shape.
    ///
    /// # Arguments
    ///
    /// - `path` (`Path`) - The shape's path data.
    ///
    /// # Returns
    ///
    /// - `Self` - The new shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_path(Path::new());
    /// ```
    pub fn new_path(path: Path) -> Self {
        Self {
            shape: ShapeType::Path(path),
            styles: Styles::default(),
        }
    }

    /// Binds the given styles to the given shape.
    ///
    /// # Arguments
    ///
    /// - `self` (`Shape`) - The shape.
    /// - `styles` (`Styles`) - The shape's new styles.
    ///
    /// # Returns
    ///
    /// - `Self` - The updated shape.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_ellispe(Ellipse::new())
    ///     .with_styles(Styles::new());
    /// ```
    pub fn with_styles(self, styles: Styles) -> Self {
        Self {
            styles: styles,
            ..self
        }
    }
}

impl Print for Shape {
    /// Prints out the given shape.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Shape`) - The shape to print.
    /// - `depth` (`u32`) - The number of tabs to print.
    ///
    /// # Examples
    ///
    /// ```
    /// let shape = Shape::new_ellipse(Ellipse::new());
    /// shape.print(0);
    /// ```
    fn print(&self, depth: u32) {
        print_tabs(depth);
        match &self.shape {
            ShapeType::Ellipse(ellipse) => ellipse.print(depth),
            ShapeType::Rectangle(rectangle) => rectangle.print(depth),
            ShapeType::Line(line) => line.print(depth),
            ShapeType::Polyline(polyline) => polyline.print(depth),
            ShapeType::Polygon(polygon) => polygon.print(depth),
            ShapeType::Path(path) => path.print(depth),
            ShapeType::Group(group) => {
                print!("<group ");
                self.styles.print(depth);
                println!(">");
                group.print(depth);
                print_tabs(depth);
                println!("<group />");
                return;
            }
        }

        self.styles.print(depth);
        println!(" />");
    }
}

impl Print for Viewport {
    /// Prints out the given viewport.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Viewport`) - The viewport to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let viewport = Viewport::default();
    /// viewport.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!("viewport=\"");
        self.from.print(_depth);
        print!(" ");
        self.to.print(_depth);
        print!("\"");
    }
}

impl Svg {
    /// The SVG's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new SVG.
    ///
    /// # Examples
    ///
    /// ```
    /// let svg = Svg::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Svg {
    /// Prints out the given SVG.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&SVG`) - The svg to print.
    /// - `depth` (`u32`) - The number of tabs to print.
    ///
    /// # Examples
    ///
    /// ```
    /// let svg = Svg::new();
    /// svg.print(0);
    /// ```
    fn print(&self, depth: u32) {
        print!("<svg ");
        self.viewport.print(depth);
        println!(" />");
        for shape in self.shapes.iter() {
            shape.print(1);
        }
        println!("</svg>");
    }
}
