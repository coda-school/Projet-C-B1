use std::{
    fs::File,
    io::{BufWriter, Write},
};

use crate::{
    shapes::{
        Ellipse, Group, Line, Path, PathCommand, Polygon, Polyline, Rectangle, Shape, ShapeType,
        Svg,
    },
    styles::{Color, Rotate, Styles},
    utils::Point,
};

/// Writes the given color int the given file in rgba format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `color` (`&Color`) - The color to write.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = write_color(BufWriter::new(File::create("test.svg").unwrap()), Color::new());
/// ```
pub fn write_color(mut writer: BufWriter<File>, color: &Color) -> std::io::Result<BufWriter<File>> {
    writer.write(
        format!(
            "rgba({}, {}, {}, {})",
            color.red, color.blue, color.green, color.transparency
        )
        .as_bytes(),
    )?;
    Ok(writer)
}

/// Writes the given point in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `point` (`&Point`) - The point to write.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = write_color(BufWriter::new(File::create("test.svg").unwrap()), Point::new());
/// ```
pub fn write_point(mut writer: BufWriter<File>, point: &Point) -> std::io::Result<BufWriter<File>> {
    writer.write(format!("{} {}", point.x, point.y).as_bytes())?;
    Ok(writer)
}

/// Writes the given rotate in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `rotate` (`&Rotate`) - The rotate to write.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = write_rotate(BufWriter::new(File::create("test.svg").unwrap()), Rotate::new_flip_x());
/// ```
pub fn write_rotate(
    mut writer: BufWriter<File>,
    rotate: &Rotate,
) -> std::io::Result<BufWriter<File>> {
    writer.write(
        match rotate {
            Rotate::Circular(degree) => format!("rotate({} deg)", degree),
            Rotate::Flipx => "rotateX(180)".to_string(),
            Rotate::Flipy => "rotateY(180)".to_string(),
        }
        .as_bytes(),
    )?;
    Ok(writer)
}

/// Writes the given styles in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `styles` (`&Styles`) - The styles to write.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_styles(BufWriter::new(File::create("test.svg").unwrap()), Styles::new());
/// ```
pub fn export_styles(
    mut writer: BufWriter<File>,
    styles: &Styles,
) -> std::io::Result<BufWriter<File>> {
    writer.write("fill=\"".as_bytes())?;
    writer = write_color(writer, &styles.fill)?;
    writer.write("\" outline=\"".as_bytes())?;
    writer = write_color(writer, &styles.outline)?;
    writer.write("\" transform=\"translate(".as_bytes())?;
    writer = write_point(writer, &styles.translate)?;
    writer.write(") ".as_bytes())?;
    writer = write_rotate(writer, &styles.rotate)?;
    writer.write("\"".as_bytes())?;
    Ok(writer)
}

/// Writes in the given file the given number of tabs.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `tabs` (`u8`) - The number of tabs to write.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = write_tabs(BufWriter::new(File::create("test.svg").unwrap()), 2);
/// ```
fn write_tabs(mut writer: BufWriter<File>, tabs: u8) -> std::io::Result<BufWriter<File>> {
    for _ in 0..tabs {
        writer.write("  ".as_bytes())?;
    }
    Ok(writer)
}

/// Writes the given ellipse in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `ellipse` (`&Ellipse`) - The ellipse to write .
/// - `styles` (`&Styles`) - The ellipse's styles to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_ellipse(
///     BufWriter::new(File::create("test.svg").unwrap()),
///     Ellipse::new(),
///     Styles::new(),
///     1
/// );
/// ```
pub fn export_ellipse(
    mut writer: BufWriter<File>,
    ellipse: &Ellipse,
    styles: &Styles,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    writer = write_tabs(writer, tabs)?;
    writer.write(
        format!(
            "<ellipse cx=\"{}\" cy=\"{}\" rx=\"{}\" ry=\"{}\" ",
            ellipse.origin.x, ellipse.origin.y, ellipse.radius_x, ellipse.radius_y
        )
        .as_bytes(),
    )?;
    writer = export_styles(writer, styles)?;
    writer.write(" />\n".as_bytes())?;
    Ok(writer)
}

/// Writes the given rectangle in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `rectangle` (`&Rectangle`) - The rectangle to write.
/// - `styles` (`&Styles`) - The rectangle's styles to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_rectangle(
///     BufWriter::new(File::create("test.svg").unwrap()),
///     Rectangle::new(),
///     Styles::new(),
///     1
/// );
/// ```
pub fn export_rectangle(
    mut writer: BufWriter<File>,
    rectangle: &Rectangle,
    styles: &Styles,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    writer = write_tabs(writer, tabs)?;
    writer.write(
        format!(
            "<rect x=\"{}\" y=\"{}\" width=\"{}\" height=\"{}\" ",
            rectangle.origin.x, rectangle.origin.y, rectangle.width, rectangle.height
        )
        .as_bytes(),
    )?;
    writer = export_styles(writer, styles)?;
    writer.write(" />\n".as_bytes())?;
    Ok(writer)
}

/// Writes the given line in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `line` (`&Line`) - The line to write.
/// - `styles` (`&Styles`) - The line's styles to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_line(
///     BufWriter::new(File::create("test.svg").unwrap()),
///     Line::new(),
///     Styles::new(),
///     1
/// );
/// ```
pub fn export_line(
    mut writer: BufWriter<File>,
    line: &Line,
    styles: &Styles,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    writer = write_tabs(writer, tabs)?;
    writer.write(
        format!(
            "<line x1=\"{}\" y1=\"{}\" x2=\"{}\" y2=\"{}\" ",
            line.from.x, line.from.y, line.to.x, line.to.y
        )
        .as_bytes(),
    )?;
    writer = export_styles(writer, styles)?;
    writer.write(" />\n".as_bytes())?;
    Ok(writer)
}

/// Writes the given point collection in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `points` (`&Vec<Point>`) - The point collection.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_point_vector(
///     BufWriter::new(File::create("test.svg").unwrap()),
///     vec![]
/// );
/// ```
pub fn export_point_vector(
    mut writer: BufWriter<File>,
    points: &Vec<Point>,
) -> std::io::Result<BufWriter<File>> {
    for i in 0..points.len() {
        writer = write_point(writer, &points[0])?;
        if i != points.len() - 1 {
            writer.write(" ".as_bytes())?;
        }
    }
    Ok(writer)
}

/// Writes the given polyline in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `polyline` (`&Polyline`) - The polyline to write.
/// - `styles` (`&Styles`) - The polyline's styles to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_polyline(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     Polyline::new(),
///     Styles::new(),
///     2
/// );
/// ```
pub fn export_polyline(
    mut writer: BufWriter<File>,
    polyline: &Polyline,
    styles: &Styles,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    writer = write_tabs(writer, tabs)?;
    writer.write("<polyline points=\"".as_bytes())?;
    writer = export_point_vector(writer, &polyline.0)?;
    writer.write("\" ".as_bytes())?;
    writer = export_styles(writer, styles)?;
    writer.write(" />\n".as_bytes())?;
    Ok(writer)
}

/// Writes the given polygon in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `polygon` (`&Polygon`) - The polyline to write.
/// - `styles` (`&Styles`) - The polyline's styles to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_polygon(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     Polygon::new(),
///     Styles::new(),
///     2
/// );
/// ```
pub fn export_polygon(
    mut writer: BufWriter<File>,
    polygon: &Polygon,
    styles: &Styles,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    writer = write_tabs(writer, tabs)?;
    writer.write("<polygon points=\"".as_bytes())?;
    writer = export_point_vector(writer, &polygon.0)?;
    writer.write("\" ".as_bytes())?;
    writer = export_styles(writer, styles)?;
    writer.write(" />\n".as_bytes())?;
    Ok(writer)
}

/// Writes the given path element to the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `element` (`&PathCommand`) - The path element to write.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_path_element(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     PathCommand::new_end_of_path()
/// );
/// ```
pub fn export_path_element(
    mut writer: BufWriter<File>,
    element: &PathCommand,
) -> std::io::Result<BufWriter<File>> {
    match element {
        PathCommand::MoveTo(point) => {
            writer.write("M ".as_bytes())?;
            write_point(writer, point)
        }
        PathCommand::LineTo(point) => {
            writer.write("L ".as_bytes())?;
            write_point(writer, point)
        }
        PathCommand::HorizontalLineTo(pos) => {
            writer.write(format!("H {}", pos).as_bytes())?;
            Ok(writer)
        }
        PathCommand::VerticalLineTo(pos) => {
            writer.write(format!("V {}", pos).as_bytes())?;
            Ok(writer)
        }
        PathCommand::CubicCurveTo(point, point1, point2) => {
            writer.write("C ".as_bytes())?;
            writer = write_point(writer, point)?;
            writer.write(" ".as_bytes())?;
            writer = write_point(writer, point1)?;
            writer.write(" ".as_bytes())?;
            write_point(writer, point2)
        }
        PathCommand::CubicCurveToShorthand(point, point1) => {
            writer.write("S ".as_bytes())?;
            writer = write_point(writer, point)?;
            writer.write(" ".as_bytes())?;
            write_point(writer, point1)
        }
        PathCommand::QuadraticCurveTo(point, point1) => {
            writer.write("Q ".as_bytes())?;
            writer = write_point(writer, point)?;
            writer.write(" ".as_bytes())?;
            write_point(writer, point1)
        }
        PathCommand::QuadraticCurveToShorthand(point) => {
            writer.write("T ".as_bytes())?;
            write_point(writer, point)
        }
        PathCommand::EndOfPath => {
            writer.write("Z".as_bytes())?;
            Ok(writer)
        }
    }
}

/// Writes the given path in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `path` (`&Path`) - The path to write.
/// - `styles` (`&Styles`) - The path's styles to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_path(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     Path::new(),
///     Styles::new(),
///     2
/// );
/// ```
pub fn export_path(
    mut writer: BufWriter<File>,
    path: &Path,
    styles: &Styles,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    writer = write_tabs(writer, tabs)?;
    writer.write("<path d=\"".as_bytes())?;
    for i in 0..path.0.len() {
        writer = export_path_element(writer, &path.0[i])?;
        if i != path.0.len() - 1 {
            writer.write(" ".as_bytes())?;
        }
    }
    writer = export_styles(writer, styles)?;
    writer.write(" />".as_bytes())?;
    Ok(writer)
}

/// Writes the given shape collection in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `shapes` (`&Vec<Box<Shape>>`) - The shape collection to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_shape_list(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     vec![],
///     2
/// );
/// ```
pub fn export_shape_list(
    mut writer: BufWriter<File>,
    shapes: &Vec<Box<Shape>>,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    for shape in shapes.iter() {
        writer = export_shape(writer, shape, tabs)?;
        writer.write("\n".as_bytes())?;
    }
    Ok(writer)
}

/// Writes the given group in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `group` (`&Group`) - The group to write.
/// - `styles` (`&Styles`) - The group's styles to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_group(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     Group::new(),
///     Styles::new(),
///     2
/// );
/// ```
pub fn export_group(
    mut writer: BufWriter<File>,
    group: &Group,
    styles: &Styles,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    writer = write_tabs(writer, tabs)?;
    writer.write("<g ".as_bytes())?;
    writer = export_styles(writer, styles)?;
    writer.write(">\n".as_bytes())?;
    writer = export_shape_list(writer, &group.0, tabs + 1)?;
    writer = write_tabs(writer, tabs)?;
    writer.write("</g>\n".as_bytes())?;
    Ok(writer)
}

/// Writes the given shape in the given file in SVG format.
///
/// # Arguments
///
/// - `writer` (`BufWriter<File>`) - The file.
/// - `shape` (`&Shape`) - The shape to write.
/// - `tabs` (`u8`) - The number of tabs to write before the content.
///
/// # Returns
///
/// - `std::io::Result<BufWriter<File>>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_shape(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     Shape::new_ellipse(Ellipse::new()),
///     2
/// );
/// ```
pub fn export_shape(
    writer: BufWriter<File>,
    shape: &Shape,
    tabs: u8,
) -> std::io::Result<BufWriter<File>> {
    match &shape.shape {
        ShapeType::Ellipse(ellipse) => export_ellipse(writer, ellipse, &shape.styles, tabs),
        ShapeType::Rectangle(rectangle) => export_rectangle(writer, rectangle, &shape.styles, tabs),
        ShapeType::Line(line) => export_line(writer, line, &shape.styles, tabs),
        ShapeType::Polyline(polyline) => export_polyline(writer, polyline, &shape.styles, tabs),
        ShapeType::Polygon(polygon) => export_polygon(writer, polygon, &shape.styles, tabs),
        ShapeType::Group(group) => export_group(writer, group, &shape.styles, tabs),
        ShapeType::Path(path) => export_path(writer, path, &shape.styles, tabs),
    }
}

/// Writes the given SVG in the given file in SVG format.
///
/// # Arguments
///
/// - `mut writer` (`BufWriter<File>`) - The file.
/// - `svg` (`&Svg`) - The SVG to write.
///
/// # Returns
///
/// - `std::io::Result<()>` - Returns the file when done or an error.
///
/// # Errors
///
/// writer.write() errors.
///
/// # Examples
///
/// ```
/// let writer = export_svg(
///     BufWriter::new(File::new("test.svg").unwrap()),
///     Svg::new()
/// );
/// ```
pub fn export_svg(mut writer: BufWriter<File>, svg: &Svg) -> std::io::Result<()> {
    writer.write("<svg  xmlns=\"http://www.w3.org/2000/svg\" viewport=\"".as_bytes())?;
    writer = write_point(writer, &svg.viewport.from)?;
    writer.write(" ".as_bytes())?;
    writer = write_point(writer, &svg.viewport.to)?;
    writer.write("\">\n".as_bytes())?;
    writer = export_shape_list(writer, &svg.shapes, 1)?;
    writer.write("</svg>\n".as_bytes())?;
    Ok(())
}
