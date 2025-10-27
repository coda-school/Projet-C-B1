use std::{
    fs::{self, File},
    io::{self, BufWriter, Write},
    path::Path,
    process::Command,
    str::FromStr,
};

use crate::{
    export::export_svg,
    shapes::{
        Ellipse, Group, Line, PathCommand, Polygon, Polyline, Print, Rectangle, Shape, ShapeType,
        Svg, Viewport,
    },
    styles::{Color, Rotate, Styles},
    utils::{is_valid_filename, Point},
};

/// Clears the console.
///
/// # Examples
///
/// ```
/// clear_screen();
/// ```
fn clear_screen() {
    print!("{esc}c", esc = 27 as char);
}

/// Asks the user for a value in the terminal.
/// The user can skip the question by pressing enter.
/// If the given input is invalid the function will repeat.
///
/// # Arguments
///
/// - `message` (`&String`) - A prompt for the user.
/// - `error_message` (`&String`) - A custom error message when the user fails to provide a valid answer.
/// - `entity` (`Option<&U>`) - An optional structure / enum to print before the prompt.
///
/// # Returns
///
/// - `Option<T> where T: FromStr, U: Print,` - The parsed value or None if the user skiped the question.
///
/// # Examples
///
/// ```
/// let mut point = Point::new();
/// let new_x = ask_for_value::<i32, Point>(
///     &"Select the new x coordinate.".to_string(),
///     &"Enter a valid integer.".to_string(),
///     Some(&point)
/// );
/// if let Some(x) = new_x {
///     point.x = x;
/// }
/// ```
fn ask_for_value<T, U>(message: &String, error_message: &String, entity: Option<&U>) -> Option<T>
where
    T: FromStr,
    U: Print,
{
    let mut input_line: String = String::new();
    let mut error = false;
    loop {
        input_line.clear();
        clear_screen();

        if let Some(e) = &entity {
            e.print(0);
            println!("");
        }

        println!("{message}");

        if error {
            println!("{error_message}");
        }

        io::stdin().read_line(&mut input_line).ok()?;

        if input_line == "\r\n" {
            return None;
        }

        match input_line.trim().parse::<T>() {
            Ok(value) => return Some(value),
            Err(_) => error = true,
        }
    }
}

/// Asks the user for a value in a range.
/// The user can skip the question by pressing enter.
/// The program will repeat if the input is invalid.
///
/// # Arguments
///
/// - `message` (`&String`) - A prompt for the user.
/// - `error_message` (`&String`) - A custom error message when the user fails to provide a valid input.
/// - `entity` (`Option<&U>`) - An optional structure or enum to print before the prompt.
/// - `min` (`T`) - The minimum accepted value.
/// - `max` (`T`) - The maximum accepted value.
///
/// # Returns
///
/// - `Option<T> where T: FromStr + Ord, U: Print,` - The parsed value or None if the user skiped the question.
///
/// # Examples
///
/// ```
/// let mut color = Color::new();
/// let choice = ask_for_value_in_range::<u8, Color>(
///     &"Select a value from 0 to 255.".to_string(),
///     &"Select a valid integer in the [0, 255] range.".to_string(),
///     None,
///     0,
///     255
/// );
/// if let Some(red) = choice {
///     color.red = red;
/// }
/// ```
fn ask_for_value_in_range<T, U>(
    message: &String,
    error_message: &String,
    entity: Option<&U>,
    min: T,
    max: T,
) -> Option<T>
where
    T: FromStr + Ord,
    U: Print,
{
    let mut input_line: String = String::new();
    let mut error = false;
    loop {
        input_line.clear();
        clear_screen();

        if let Some(e) = &entity {
            e.print(0);
            println!("");
        }

        println!("{message}");

        if error {
            println!("{error_message}");
        }

        io::stdin().read_line(&mut input_line).ok()?;

        if input_line == "\r\n" {
            return None;
        }

        match input_line.trim().parse::<T>() {
            Ok(value) => {
                if value >= min && value <= max {
                    return Some(value);
                } else {
                    error = true;
                }
            }
            Err(_) => {
                error = true;
            }
        }
    }
}

/// Asks the user for an index in a vector.
/// The user can skip the question by pressing enter.
/// The program will repeat until the user submitted a valid input.
///
/// # Arguments
///
/// - `message` (`&String`) - A prompt to the user.
/// - `error_message` (`&String`) - A custom error message when the user failed to provide a valid input.
/// - `entities` (`&Vec<T>`) - The vector.
/// - `include_length` (`bool`) - Indicates if the length of the vector is considered as a valid index.
///
/// # Returns
///
/// - `Option<usize> where T: Print,` - The selected index or None if the user skiped the question.
///
/// # Examples
///
/// ```
/// let mut points = Vec<Point>::new();
/// let index = ask_for_index::<Point>(
///     &"Select an index to add a point.".to_string()
///     &"Select a valid index.".to_string(),
///     &points,
///     true
/// );
/// if let Some(i) = index {
///     points.insert(i, Point::new());
/// }
/// ```
fn ask_for_index<T>(
    message: &String,
    error_message: &String,
    entities: &Vec<T>,
    include_length: bool,
) -> Option<usize>
where
    T: Print,
{
    let mut input_line: String = String::new();
    let mut error = false;

    if entities.is_empty() {
        return None;
    }

    loop {
        input_line.clear();
        clear_screen();

        for (i, e) in entities.iter().enumerate() {
            print!("  - ({i}) ");
            e.print(0);
            println!("");
        }

        println!("{message}");

        if error {
            println!("{error_message}");
        }

        io::stdin().read_line(&mut input_line).ok()?;

        if input_line == "\r\n" {
            return None;
        }

        match input_line.trim().parse::<usize>() {
            Ok(value) => {
                if include_length && value <= entities.len() {
                    return Some(value);
                }
                if !include_length && value < entities.len() {
                    return Some(value);
                } else {
                    error = true;
                }
            }
            Err(_) => error = true,
        }
    }
}

/// Asks the user for an index in a vector.
/// The user can skip the question by pressing enter.
/// The program will repeat until the user submitted a valid input.
///
/// # Arguments
///
/// - `message` (`&String`) - A prompt to the user.
/// - `error_message` (`&String`) - A custom error message when the user failed to provide a valid input.
/// - `entities` (`&Vec<Box<T>>`) - The vector.
/// - `include_length` (`bool`) - Indicates if the length of the vector is considered as a valid index.
///
/// # Returns
///
/// - `Option<usize> where T: Print,` - The selected index or None if the user skiped the question.
///
/// # Examples
///
/// ```
/// let mut shapes = Vec<Box<Shape>>::new();
/// let index = ask_for_index::<Shape>(
///     &"Select an index to remove a shape.".to_string()
///     &"Select a valid index.".to_string(),
///     &shapes,
///     false
/// );
/// if let Some(i) = index {
///     shapes.remove(i);
/// }
/// ```
fn ask_for_index_box<T>(
    message: &String,
    error_message: &String,
    entities: &Vec<Box<T>>,
    include_length: bool,
) -> Option<usize>
where
    T: Print,
{
    let mut input_line: String = String::new();
    let mut error = false;

    if entities.is_empty() {
        return None;
    }

    loop {
        input_line.clear();
        clear_screen();

        for (i, e) in entities.iter().enumerate() {
            print!("  - {i} ");
            e.print(0);
        }

        println!("{message}");

        if error {
            println!("{error_message}");
        }

        io::stdin().read_line(&mut input_line).ok()?;

        if input_line == "\r\n" {
            return None;
        }

        match input_line.trim().parse::<usize>() {
            Ok(value) => {
                if include_length && value <= entities.len() {
                    return Some(value);
                }
                if !include_length && value < entities.len() {
                    return Some(value);
                } else {
                    error = true;
                }
            }
            Err(_) => error = true,
        }
    }
}

/// Asks the user for a file name.
/// The user can skip the question by pressing enter.
/// The program will repeat if the user submits a wrong input.
///
/// # Returns
///
/// - `Option<String>` - The file's name or None if the user skips the question.
///
/// # Examples
///
/// ```
/// match ask_for_file_name() {
///     Some(filename) => {},
///     None => {}
/// }
/// ```
fn ask_for_file_name() -> Option<String> {
    let message = "Enter a file name :".to_string();
    let mut error_message = "".to_string();
    let mut input_line = String::new();
    loop {
        input_line.clear();
        clear_screen();
        println!("{}", &message);
        if !error_message.is_empty() {
            println!("{}", error_message);
        }
        io::stdin().read_line(&mut input_line).ok()?;
        input_line = input_line.trim().to_string();
        if input_line == "\r\n" {
            return None;
        }

        if let Err(e) = is_valid_filename(&input_line) {
            error_message = e;
        } else {
            return Some(input_line);
        }
    }
}

/// Prompts the user to update the given color.
///
/// # Arguments
///
/// - `mut color` (`Color`) - The color to update.
///
/// # Returns
///
/// - `Color` - The updated color.
///
/// # Examples
///
/// ```
/// let color = edit_color(Color::new());
/// ```
fn edit_color(mut color: Color) -> Color {
    color.red = ask_for_value::<u8, Color>(
        &"Select the color's RED value".to_string(),
        &"Select a valid value".to_string(),
        Some(&color),
    )
    .unwrap_or(color.red);
    color.green = ask_for_value::<u8, Color>(
        &"Select the color's GREEN value".to_string(),
        &"Select a valid value".to_string(),
        Some(&color),
    )
    .unwrap_or(color.green);
    color.blue = ask_for_value::<u8, Color>(
        &"Select the color's BLUE value".to_string(),
        &"Select a valid value".to_string(),
        Some(&color),
    )
    .unwrap_or(color.blue);
    color.transparency = ask_for_value::<u8, Color>(
        &"Select the color's TRANSPARENCY value".to_string(),
        &"Select a valid value".to_string(),
        Some(&color),
    )
    .unwrap_or(color.transparency);
    color
}

/// Prompts the user to update the given rotate.
///
/// # Arguments
///
/// - `rotate` (`Rotate`) - The rotate to upgrade.
///
/// # Returns
///
/// - `Rotate` - The updated rotate.
///
/// # Examples
///
/// ```
/// let rotate = edit_rotate(Rotate::new_flipx());
/// ```
fn edit_rotate(rotate: Rotate) -> Rotate {
    let message = r"Select an option :
  - (1) Circular
  - (2) Flip X
  - (3) Flip Y
  - Press enter to exit"
        .to_string();
    let error_message = r"Select a valiid option (1 - 3)".to_string();

    loop {
        let choice = ask_for_value_in_range(&message, &error_message, Some(&rotate), 1, 3);

        if choice.is_none() {
            return rotate;
        }

        match choice.unwrap_or(-1) {
            1 => {
                return Rotate::new_circular(
                    ask_for_value::<u16, Rotate>(
                        &"Select the angle value.".to_string(),
                        &"Select a valid angle value.".to_string(),
                        None,
                    )
                    .unwrap_or(0),
                )
            }
            2 => return Rotate::new_flip_x(),
            3 => return Rotate::new_flip_y(),
            _ => continue,
        }
    }
}

/// Prompts the user to update the given styles.
///
/// # Arguments
///
/// - `mut styles` (`Styles`) - The styles to update.
///
/// # Returns
///
/// - `Styles` - The updated styles.
///
/// # Examples
///
/// ```
/// let styles = edit_styles(Styles::new());
/// ```
fn edit_styles(mut styles: Styles) -> Styles {
    let message = r"Select an option :
  - (1) Edit fill
  - (2) Edit outline
  - (3) Edit translate
  - (4) Edit rotate
  - Press enter to exit"
        .to_string();
    let error_message = "Select a valid option (1 - 4).".to_string();

    loop {
        let choice = ask_for_value_in_range(&message, &error_message, Some(&styles), 1, 4);

        if choice.is_none() {
            return styles;
        }

        match choice.unwrap_or(-1) {
            1 => styles.fill = edit_color(styles.fill),
            2 => styles.outline = edit_color(styles.outline),
            3 => styles.translate = edit_point(styles.translate),
            4 => styles.rotate = edit_rotate(styles.rotate),
            _ => continue,
        }
    }
}

/// Prompts the user to update the given ellipse.
///
/// # Arguments
///
/// - `mut ellipse` (`Ellipse`) - The ellipse to update.
/// - `mut styles` (`Styles`) - The ellipse's styles to update.
///
/// # Returns
///
/// - `Shape` - The updated shape.
///
/// # Examples
///
/// ```
/// let shape = edit_ellipse(Ellipse::new(), Styles::new());
/// ```
fn edit_ellipse(mut ellipse: Ellipse, mut styles: Styles) -> Shape {
    let msg = r"Select a valid option :
  - (1) Edit origin
  - (2) Edit radius X
  - (3) Edit radius Y
  - (4) Edit styles
  - Press enter to exit"
        .to_string();

    loop {
        let choice = ask_for_value_in_range(
            &msg,
            &"select a valid option (1 - 4).".to_string(),
            Some(&ellipse),
            1,
            4,
        );
        if choice.is_none() {
            return Shape::new_ellipse(ellipse).with_styles(styles);
        }

        match choice.unwrap_or(-1) {
            1 => {
                ellipse.origin.x = ask_for_value::<i32, Ellipse>(
                    &"Select the X origin value.".to_string(),
                    &"Select a valid X origin value.".to_string(),
                    None,
                )
                .unwrap_or(ellipse.origin.x);
                ellipse.origin.y = ask_for_value::<i32, Ellipse>(
                    &"Select the Y origin value.".to_string(),
                    &"Select a valid Y origin value.".to_string(),
                    None,
                )
                .unwrap_or(ellipse.origin.y);
            }
            2 => {
                ellipse.radius_x = ask_for_value::<u32, Ellipse>(
                    &"Select the X radius value.".to_string(),
                    &"Select a valid X radius value (>= 0).".to_string(),
                    None,
                )
                .unwrap_or(ellipse.radius_x)
            }
            3 => {
                ellipse.radius_y = ask_for_value::<u32, Ellipse>(
                    &"Select the Y radius value.".to_string(),
                    &"Select a valid Y radius value (>= 0).".to_string(),
                    None,
                )
                .unwrap_or(ellipse.radius_y)
            }
            4 => styles = edit_styles(styles),
            _ => continue,
        }
    }
}

/// Prompts the user to update the given rectangle.
///
/// # Arguments
///
/// - `mut rectangle` (`Rectangle`) - The rectangle to update.
/// - `mut styles` (`Styles`) - The rectangle's styles to update.
///
/// # Returns
///
/// - `Shape` - The updated shape.
///
/// # Examples
///
/// ```
/// let shape = edit_rectangle(Rectangle::new(), Styles::new());
/// ```
fn edit_rectangle(mut rectangle: Rectangle, mut styles: Styles) -> Shape {
    let msg = r"Select a valid option :
  - (1) Edit origin
  - (2) Edit width
  - (3) Edit height
  - (4) Edit styles
  - Press enter to exit"
        .to_string();

    loop {
        let choice = ask_for_value_in_range(
            &msg,
            &"select a valid option (1 - 4).".to_string(),
            Some(&rectangle),
            1,
            4,
        );
        if choice.is_none() {
            return Shape::new_rectangle(rectangle).with_styles(styles);
        }

        match choice.unwrap_or(-1) {
            1 => {
                rectangle.origin.x = ask_for_value::<i32, Rectangle>(
                    &"Select the X origin value.".to_string(),
                    &"Select a valid X origin value.".to_string(),
                    None,
                )
                .unwrap_or(rectangle.origin.x);
                rectangle.origin.y = ask_for_value::<i32, Rectangle>(
                    &"Select the Y origin value.".to_string(),
                    &"Select a valid Y origin value.".to_string(),
                    None,
                )
                .unwrap_or(rectangle.origin.y);
            }
            2 => {
                rectangle.width = ask_for_value::<u32, Rectangle>(
                    &"Select the width value.".to_string(),
                    &"Select a valid width value (>= 0).".to_string(),
                    None,
                )
                .unwrap_or(rectangle.width)
            }
            3 => {
                rectangle.height = ask_for_value::<u32, Rectangle>(
                    &"Select the height value.".to_string(),
                    &"Select a valid height value (>= 0).".to_string(),
                    None,
                )
                .unwrap_or(rectangle.height)
            }
            4 => styles = edit_styles(styles),
            _ => continue,
        }
    }
}

/// Prompts the user to update the given line.
///
/// # Arguments
///
/// - `mut line` (`Line`) - The line to update.
/// - `mut styles` (`Styles`) - The line's styles to update.
///
/// # Returns
///
/// - `Shape` - Describe the return value.
///
/// # Examples
///
/// ```
/// let shape = edit_line(Line::new(), Styles::new());
/// ```
fn edit_line(mut line: Line, mut styles: Styles) -> Shape {
    let msg = r"Select a valid option :
  - (1) Edit from
  - (2) Edit to
  - (3) Edit styles
  - Press enter to exit"
        .to_string();

    loop {
        let choice = ask_for_value_in_range(
            &msg,
            &"select a valid option (1 - 3).".to_string(),
            Some(&line),
            1,
            3,
        );
        if choice.is_none() {
            return Shape::new_line(line).with_styles(styles);
        }

        match choice.unwrap_or(-1) {
            1 => {
                line.from.x = ask_for_value::<i32, Rectangle>(
                    &"Select the X from value.".to_string(),
                    &"Select a X from value.".to_string(),
                    None,
                )
                .unwrap_or(line.from.x);
                line.from.y = ask_for_value::<i32, Rectangle>(
                    &"Select the Y from value.".to_string(),
                    &"Select a valid Y from value.".to_string(),
                    None,
                )
                .unwrap_or(line.from.y);
            }
            2 => {
                line.to.x = ask_for_value::<i32, Rectangle>(
                    &"Select the X to value.".to_string(),
                    &"Select a X to value.".to_string(),
                    None,
                )
                .unwrap_or(line.to.x);
                line.to.y = ask_for_value::<i32, Rectangle>(
                    &"Select the Y to value.".to_string(),
                    &"Select a valid Y to value.".to_string(),
                    None,
                )
                .unwrap_or(line.to.y);
            }
            3 => styles = edit_styles(styles),
            _ => continue,
        }
    }
}

/// Prompts the user to update a point.
///
/// # Arguments
///
/// - `mut point` (`Point`) - The point to update.
///
/// # Returns
///
/// - `Point` - The updated point.
///
/// # Examples
///
/// ```
/// let point = edit_point(Point::new());
/// ```
fn edit_point(mut point: Point) -> Point {
    point.x = ask_for_value::<i32, Point>(
        &"Select the point x value".to_string(),
        &"Select a valid x value".to_string(),
        Some(&point),
    )
    .unwrap_or(point.x);
    point.y = ask_for_value::<i32, Point>(
        &"Select the point y value".to_string(),
        &"Select a valid y value".to_string(),
        Some(&point),
    )
    .unwrap_or(point.y);
    point
}

/// Prompts the user to add a new point.
///
/// # Arguments
///
/// - `mut points` (`Vec<Point>`) - The point collection.
///
/// # Returns
///
/// - `Vec<Point>` - The updated point collection.
///
/// # Examples
///
/// ```
/// let points = add_point(vec![]);
/// ```
fn add_point(mut points: Vec<Point>) -> Vec<Point> {
    let index = if points.is_empty() {
        Some(0)
    } else {
        ask_for_index::<Point>(
            &"Select the point's index or press enter to exit".to_string(),
            &"Select a valid index".to_string(),
            &points,
            true,
        )
    };

    if index.is_none() {
        return points;
    }

    let point = edit_point(Point::new());
    points.insert(index.unwrap(), point);
    return points;
}

/// Prompts the user to update a point in a point collection.
///
/// # Arguments
///
/// - `mut points` (`Vec<Point>`) - The point collection.
///
/// # Returns
///
/// - `Vec<Point>` - The updated point collection.
///
/// # Examples
///
/// ```
/// let point = edit_points(vec![]);
/// ```
fn edit_points(mut points: Vec<Point>) -> Vec<Point> {
    let index = ask_for_index::<Point>(
        &"Select the point index or press enter to exit".to_string(),
        &"Select a valid index".to_string(),
        &points,
        false,
    );

    if index.is_none() {
        return points;
    }
    let point = edit_point(points[index.unwrap()]);
    points[index.unwrap()] = point;
    return points;
}

/// Prompts the user to remove the a point in a point collection.
///
/// # Arguments
///
/// - `mut points` (`Vec<Point>`) - The point collection.
///
/// # Returns
///
/// - `Vec<Point>` - The updated point collection.
///
/// # Examples
///
/// ```
/// let points = remove_point(vec![]);
/// ```
fn remove_point(mut points: Vec<Point>) -> Vec<Point> {
    let index = ask_for_index::<Point>(
        &"Select the point's index or press enter to exit".to_string(),
        &"Select a valid index".to_string(),
        &points,
        false,
    );

    if index.is_none() {
        return points;
    }

    points.remove(index.unwrap());
    return points;
}

/// Prompts the user to update the given polyline.
///
/// # Arguments
///
/// - `mut polyline` (`Polyline`) - The polyline to update.
/// - `mut styles` (`Styles`) - The polyline's styles to update.
///
/// # Returns
///
/// - `Shape` - The updated shape.
///
/// # Examples
///
/// ```
/// let shape = edit_polyline(Polyline::new(), Styles::new());
/// ```
fn edit_polyline(mut polyline: Polyline, mut styles: Styles) -> Shape {
    let message = r"Select an option :
  - (1) Add a point
  - (2) Edit a point
  - (3) Remove a point
  - (4) Edit the styles
  - Press enter to exit"
        .to_string();
    let error_message = "Select a valid option".to_string();

    loop {
        let choice = ask_for_value_in_range(&message, &error_message, Some(&polyline), 1, 4);
        if choice.is_none() {
            return Shape::new_polyline(polyline).with_styles(styles);
        }

        match choice.unwrap_or(-1) {
            1 => polyline.0 = add_point(polyline.0),
            2 => polyline.0 = edit_points(polyline.0),
            3 => polyline.0 = remove_point(polyline.0),
            4 => styles = edit_styles(styles),
            _ => continue,
        }
    }
}

/// Prompts the user to update the given polygon.
///
/// # Arguments
///
/// - `mut polygon` (`Polygon`) - The polygon to update.
/// - `mut styles` (`Styles`) - The polygon's styles to update.
///
/// # Returns
///
/// - `Shape` - The updated shape.
///
/// # Examples
///
/// ```
/// let polygon = edit_polygon(Polygon::new(), Styles::new());
/// ```
fn edit_polygon(mut polygon: Polygon, mut styles: Styles) -> Shape {
    let message = r"Select an option :
  - (1) Add a point
  - (2) Edit a point
  - (3) Remove a point
  - (4) Edit the styles
  - Press enter to exit"
        .to_string();
    let error_message = "Select a valid option".to_string();

    loop {
        let choice = ask_for_value_in_range(&message, &error_message, Some(&polygon), 1, 4);
        if choice.is_none() {
            return Shape::new_polygon(polygon).with_styles(styles);
        }

        match choice.unwrap_or(-1) {
            1 => polygon.0 = add_point(polygon.0),
            2 => polygon.0 = edit_points(polygon.0),
            3 => polygon.0 = remove_point(polygon.0),
            4 => styles = edit_styles(styles),
            _ => continue,
        }
    }
}

/// Prompts the user to create a new path element.
/// The user can skip the question by pressing
///
/// # Returns
///
/// - `Option<PathCommand>` - The new path element or None if the user skips the question.
///
/// # Examples
///
/// ```
/// match create_path_element() {
///     Some(element) => {},
///     None => {}
/// }
/// ```
fn create_path_element() -> Option<PathCommand> {
    let message = r"Select an option :
  - (1) Move to
  - (2) Line to
  - (3) Horizontal line to 
  - (4) Vertical line to
  - (5) Cubic curve to
  - (6) Cubic curve to shorthand
  - (7) Quadratic curve to
  - (8) Quadratic curve to shorthand
  - (9) End of path
  - Press enter to exit"
        .to_string();
    let error_message = "Select a valid option".to_string();

    Some(edit_path_element(
        match ask_for_value_in_range::<u8, PathCommand>(&message, &error_message, None, 1, 9)? {
            1 => Some(PathCommand::new_move_to()),
            2 => Some(PathCommand::new_line_to()),
            3 => Some(PathCommand::new_horizontal_line_to()),
            4 => Some(PathCommand::new_vertical_line_to()),
            5 => Some(PathCommand::new_cubic_curve_to()),
            6 => Some(PathCommand::new_cubic_curve_to_shorthand()),
            7 => Some(PathCommand::new_quadratic_curve_to()),
            8 => Some(PathCommand::new_quadratic_curve_to_shorthand()),
            9 => Some(PathCommand::new_end_of_path()),
            _ => None,
        }?,
    ))
}

/// Prompts the user to update the given path element.
///
/// # Arguments
///
/// - `element` (`PathCommand`) - The path element to update.
///
/// # Returns
///
/// - `PathCommand` - The updated path element.
///
/// # Examples
///
/// ```
/// let element = edit_path_element(PathElement::new_move_to());
/// ```
fn edit_path_element(element: PathCommand) -> PathCommand {
    match element {
        PathCommand::MoveTo(point) => PathCommand::MoveTo(edit_point(point)),
        PathCommand::LineTo(point) => PathCommand::LineTo(edit_point(point)),
        PathCommand::HorizontalLineTo(val) => PathCommand::HorizontalLineTo(
            ask_for_value::<i32, PathCommand>(
                &"Select the new position".to_string(),
                &"Select a valid position".to_string(),
                None,
            )
            .unwrap_or(val),
        ),
        PathCommand::VerticalLineTo(val) => PathCommand::VerticalLineTo(
            ask_for_value::<i32, PathCommand>(
                &"Select the new position".to_string(),
                &"Select a valid position".to_string(),
                None,
            )
            .unwrap_or(val),
        ),
        PathCommand::CubicCurveTo(point, point1, point2) => {
            PathCommand::CubicCurveTo(edit_point(point), edit_point(point1), edit_point(point2))
        }
        PathCommand::CubicCurveToShorthand(point, point1) => {
            PathCommand::CubicCurveToShorthand(edit_point(point), edit_point(point1))
        }
        PathCommand::QuadraticCurveTo(point, point1) => {
            PathCommand::QuadraticCurveTo(edit_point(point), edit_point(point1))
        }
        PathCommand::QuadraticCurveToShorthand(point) => {
            PathCommand::QuadraticCurveToShorthand(edit_point(point))
        }
        PathCommand::EndOfPath => PathCommand::EndOfPath,
    }
}

/// Prompts the user to add a path element in a path element collection.
///
/// # Arguments
///
/// - `mut elements` (`Vec<PathCommand>`) - The path element collection.
///
/// # Returns
///
/// - `Vec<PathCommand>` - The updated path element collection.
///
/// # Examples
///
/// ```
/// let elements = add_path_element(vec![]);
/// ```
fn add_path_element(mut elements: Vec<PathCommand>) -> Vec<PathCommand> {
    let index = ask_for_index(
        &"Select the index.".to_string(),
        &"Select a valid index.".to_string(),
        &elements,
        true,
    );

    let element = create_path_element();
    if element.is_none() {
        return elements;
    }

    if index.is_none() {
        elements.push(element.unwrap());
        return elements;
    }

    elements.insert(index.unwrap(), element.unwrap());
    elements
}

/// Promtps the user to edit a path element in the given path element collection.
///
/// # Arguments
///
/// - `mut elements` (`Vec<PathCommand>`) - A path element collection.
///
/// # Returns
///
/// - `Vec<PathCommand>` - The updated path element collection.
///
/// # Examples
///
/// ```
/// let elements = edit_path_elements(vec![]);
/// ```
fn edit_path_elements(mut elements: Vec<PathCommand>) -> Vec<PathCommand> {
    let index = ask_for_index::<PathCommand>(
        &"Select the path element index or press enter to exit".to_string(),
        &"Select a valid index".to_string(),
        &elements,
        false,
    );

    if index.is_none() {
        return elements;
    }
    let element = edit_path_element(elements[index.unwrap()]);
    elements[index.unwrap()] = element;
    return elements;
}

/// Prompts the user to remove a path element in the given path element collection.
///
/// # Arguments
///
/// - `mut elements` (`Vec<PathCommand>`) - A path element collection.
///
/// # Returns
///
/// - `Vec<PathCommand>` - The updated path element collection.
///
/// # Examples
///
/// ```
/// let elements = remove_path_element(vec![]);
/// ```
fn remove_path_element(mut elements: Vec<PathCommand>) -> Vec<PathCommand> {
    let index = ask_for_index::<PathCommand>(
        &"Select the path element index or press enter to exit".to_string(),
        &"Select a valid index".to_string(),
        &elements,
        false,
    );

    if index.is_none() {
        return elements;
    }

    elements.remove(index.unwrap());
    elements
}

/// Prompts the user to edit the given path.
///
/// # Arguments
///
/// - `mut path` (`Path`) - The path to update.
/// - `mut styles` (`Styles`) - The path's styles to update.
///
/// # Returns
///
/// - `Shape` - The updated shape.
///
/// # Examples
///
/// ```
/// let shape = edit_path(Path::new(), Styles::new());
/// ```
fn edit_path(mut path: crate::shapes::Path, mut styles: Styles) -> Shape {
    let message = r"Select an option :
  - (1) Add an element
  - (2) Edit an element
  - (3) Remove an element
  - (4) Edit styles
  - Press enter to exit"
        .to_string();
    let error_message = "Select a valid option".to_string();

    loop {
        let choice = ask_for_value_in_range::<u8, crate::shapes::Path>(
            &message,
            &error_message,
            Some(&path),
            1,
            4,
        );

        if choice.is_none() {
            return Shape::new_path(path).with_styles(styles);
        }

        match choice.unwrap() {
            1 => path.0 = add_path_element(path.0),
            2 => path.0 = edit_path_elements(path.0),
            3 => path.0 = remove_path_element(path.0),
            4 => styles = edit_styles(styles),
            _ => continue,
        }
    }
}

/// Prompts the user to edit the given viewport.
///
/// # Arguments
///
/// - `mut viewport` (`Viewport`) - The viewport to edit.
///
/// # Returns
///
/// - `Viewport` - The updated viewport.
///
/// # Examples
///
/// ```
/// let viewport = edit_viewport(Viewport::new());
/// ```
fn edit_viewport(mut viewport: Viewport) -> Viewport {
    let message = r"Select an option :
  - (1) Edit the viewport from point
  - (2) Edit the viewport to point
  - Press enter to exit"
        .to_string();
    let error_message = "Select a valid option".to_string();
    loop {
        let choice = ask_for_value_in_range::<i32, Viewport>(
            &message,
            &error_message,
            Some(&viewport),
            1,
            2,
        );

        if choice.is_none() {
            return viewport;
        }

        match choice.unwrap_or(-1) {
            1 => {
                viewport.from.x = ask_for_value(
                    &"Select the viewport from x value.".to_string(),
                    &"Select a valid viewport from x value".to_string(),
                    Some(&viewport),
                )
                .unwrap_or(viewport.from.x);
                viewport.from.y = ask_for_value(
                    &"Select the viewport from y value.".to_string(),
                    &"Select a valid viewport from y value".to_string(),
                    Some(&viewport),
                )
                .unwrap_or(viewport.from.y);
            }
            2 => {
                viewport.to.x = ask_for_value(
                    &"Select the viewport to x value.".to_string(),
                    &"Select a valid viewport to x value".to_string(),
                    Some(&viewport),
                )
                .unwrap_or(viewport.to.x);
                viewport.to.y = ask_for_value(
                    &"Select the viewport to y value.".to_string(),
                    &"Select a valid viewport to y value".to_string(),
                    Some(&viewport),
                )
                .unwrap_or(viewport.to.y);
            }
            _ => continue,
        }
    }
}

/// Prompts the user to update the given shape.
///
/// # Arguments
///
/// - `shape` (`Shape`) - The shape to update.
///
/// # Returns
///
/// - `Shape` - The updated shape.
///
/// # Examples
///
/// ```
/// let shape = edit_shape(Shape::new_ellipse(Ellipse::new()));
/// ```
fn edit_shape(shape: Shape) -> Shape {
    let styles = shape.styles.clone();
    match shape.shape {
        ShapeType::Ellipse(ellipse) => edit_ellipse(ellipse, styles),
        ShapeType::Rectangle(rectangle) => edit_rectangle(rectangle, styles),
        ShapeType::Line(line) => edit_line(line, styles),
        ShapeType::Polyline(polyline) => edit_polyline(polyline, styles),
        ShapeType::Polygon(polygon) => edit_polygon(polygon, styles),
        ShapeType::Group(group) => edit_group(group, styles),
        ShapeType::Path(path) => edit_path(path, styles),
    }
}

/// Prompts the user to create a new shape.
/// The user can skip the question by pressing enter.
///
/// # Returns
///
/// - `Option<Shape>` - The new shape or None if the user skips the question.
///
/// # Examples
///
/// ```
/// match create_shape() {
///     Some(shape) => {},
///     None => {}
/// }
/// ```
fn create_shape() -> Option<Shape> {
    let message = r"Select an option :
  - (1) Create ellipse
  - (2) Create rectangle
  - (3) Create line
  - (4) Create polyline
  - (5) Create polygon
  - (6) Create path
  - (7) Create group
  - Press enter to exit ..."
        .to_string();
    let error_message = "Select a valid option (1 - 7).".to_string();

    loop {
        let choice = ask_for_value_in_range::<i32, Shape>(&message, &error_message, None, 1, 7);
        if choice.is_none() {
            return None;
        }

        match choice.unwrap_or(-1) {
            1 => return Some(edit_ellipse(Ellipse::new(), Styles::new())),
            2 => return Some(edit_rectangle(Rectangle::new(), Styles::new())),
            3 => return Some(edit_line(Line::new(), Styles::new())),
            4 => return Some(edit_polyline(Polyline::new(), Styles::new())),
            5 => return Some(edit_polygon(Polygon::new(), Styles::new())),
            6 => return Some(edit_path(crate::shapes::Path::new(), Styles::new())),
            7 => return Some(edit_group(Group::new(), Styles::new())),
            _ => continue,
        }
    }
}

/// Prompts the user to add a shape in the given shape collection.
///
/// # Arguments
///
/// - `mut shapes` (`Vec<Box<Shape>>`) - The shape collection.
///
/// # Returns
///
/// - `Vec<Box<Shape>>` - The updated shape collection.
///
/// # Examples
///
/// ```
/// let shapes = add_shape(vec![]);
/// ```
fn add_shape(mut shapes: Vec<Box<Shape>>) -> Vec<Box<Shape>> {
    let index = if shapes.is_empty() {
        Some(0)
    } else {
        ask_for_index_box(
            &"Select the shape's index".to_string(),
            &"Select a valid index".to_string(),
            &shapes,
            true,
        )
    };

    if index.is_none() {
        return shapes;
    }

    let shape = create_shape();

    if shape.is_none() {
        return shapes;
    }

    shapes.insert(index.unwrap(), Box::new(shape.unwrap()));
    return shapes;
}

/// Prompts the user to edit a shape in the given shape collection.
///
/// # Arguments
///
/// - `mut shapes` (`Vec<Box<Shape>>`) - The shape collection.
///
/// # Returns
///
/// - `Vec<Box<Shape>>` - The updated shape collection.
///
/// # Examples
///
/// ```
/// let shapes = edit_shapes(vec![]);
/// ```
fn edit_shapes(mut shapes: Vec<Box<Shape>>) -> Vec<Box<Shape>> {
    let index = ask_for_index_box(
        &"Select the shape's index".to_string(),
        &"Select a valid index".to_string(),
        &shapes,
        false,
    );
    if index.is_none() {
        return shapes;
    }

    let shape = shapes.remove(index.unwrap());
    shapes.insert(index.unwrap(), Box::new(edit_shape(*shape)));
    return shapes;
}

/// Prompts the user to remove a shape in the given shape collection.
///
/// # Arguments
///
/// - `mut shapes` (`Vec<Box<Shape>>`) - The shape collection.
///
/// # Returns
///
/// - `Vec<Box<Shape>>` - The updated shape collection.
///
/// # Examples
///
/// ```
/// let shapes = remove_shape(vec![]);
/// ```
fn remove_shape(mut shapes: Vec<Box<Shape>>) -> Vec<Box<Shape>> {
    let index = ask_for_index_box(
        &"Select the shape's index".to_string(),
        &"Select a valid index".to_string(),
        &shapes,
        false,
    );

    if index.is_none() {
        return shapes;
    }

    shapes.remove(index.unwrap());
    return shapes;
}

/// Prompts the user to edit the given group.
///
/// # Arguments
///
/// - `mut group` (`Group`) - The group to update.
/// - `mut styles` (`Styles`) - The group's styles to update.
///
/// # Returns
///
/// - `Shape` - The updated shape.
///
/// # Examples
///
/// ```
/// let shape = edit_group(Group::new(), Styles::new());
/// ```
fn edit_group(mut group: Group, mut styles: Styles) -> Shape {
    let message = r"Select an option :
  - (1) Add a shape
  - (2) Edit a shape
  - (3) Remove a shape
  - (4) Edit the styles"
        .to_string();
    let error_message = "Select a valid option (1 - 4)".to_string();

    loop {
        let choice = ask_for_value_in_range(&message, &error_message, Some(&group), 1, 4);

        if choice.is_none() {
            return Shape::new_group(group).with_styles(styles);
        }

        match choice.unwrap_or(-1) {
            1 => group.0 = add_shape(group.0),
            2 => group.0 = edit_shapes(group.0),
            3 => group.0 = remove_shape(group.0),
            4 => styles = edit_styles(styles),
            _ => continue,
        }
    }
}

/// Prompts the user to edit the given SVG.
///
/// # Arguments
///
/// - `mut svg` (`Svg`) - The SVG to update.
///
/// # Returns
///
/// - `Svg` - The updated SVG.
///
/// # Examples
///
/// ```
/// let svg = edit_svg(Svg::new());
/// ```
fn edit_svg(mut svg: Svg) -> Svg {
    let message = r"Select an option :
  - (1) Add a shape
  - (2) Edit a shape
  - (3) Remove a shape
  - (4) Edit the viewport
  - Press enter to exit"
        .to_string();

    let error_message = "Select a valid option (1 - 4)".to_string();

    loop {
        let choice = ask_for_value_in_range(&message, &error_message, Some(&svg), 1, 4);

        dbg!(choice);
        let _ = Command::new("pause").status();

        if choice.is_none() {
            return svg;
        }

        match choice.unwrap_or(-1) {
            1 => svg.shapes = add_shape(svg.shapes),
            2 => svg.shapes = edit_shapes(svg.shapes),
            3 => svg.shapes = remove_shape(svg.shapes),
            4 => svg.viewport = edit_viewport(svg.viewport),
            _ => continue,
        }
    }
}

/// Prompts the user for a file name to serialize the given SVG.
///
/// # Arguments
///
/// - `svg` (`Svg`) - The SVG to update.
///
/// # Returns
///
/// - `Svg` - Returns the SVG for ownership.
///
/// # Examples
///
/// ```
/// let svg = save_svg(Svg::new());
/// ```
fn save_svg(svg: Svg) -> Svg {
    let file_name = ask_for_file_name();
    if file_name.is_none() {
        return svg;
    }
    let file_name = file_name.unwrap();

    let json = serde_json::to_string(&svg);
    if json.is_err() {
        return svg;
    }
    let json = json.unwrap();

    let file = File::create(file_name);
    if file.is_err() {
        return svg;
    }
    let mut file = file.unwrap();
    let _ = file.write_all(json.as_bytes());
    return svg;
}

/// Prompts the user for a filename to deserialize an svg.
/// The user can skip the question by pressing enter.
///
/// # Returns
///
/// - `Option<Svg>` - The loaded SVG or None if the user skips the question.
///
/// # Examples
///
/// ```
/// match load_svg() {
///     Some(svg) => {},
///     None => {}
/// }
/// ```
fn load_svg() -> Option<Svg> {
    let file_name = ask_for_file_name();
    if file_name.is_none() {
        return None;
    }
    let file_name = file_name.unwrap();

    if !Path::new(&file_name).exists() {
        return None;
    }

    let json = fs::read_to_string(file_name).ok()?;
    let data: Svg = serde_json::from_str(&json).ok()?;
    Some(data)
}

/// Prompts the user to create a new SVG.
///
/// # Returns
///
/// - `Svg` - The new SVG.
///
/// # Examples
///
/// ```
/// let svg = create_svg();
/// ```
fn create_svg() -> Svg {
    return edit_svg(Svg::new());
}

/// Prompts the user for a file name and export the given svg.
/// The user can skip the question by pressing enter.
///
/// # Arguments
///
/// - `svg` (`Svg`) - The SVG to export.
///
/// # Returns
///
/// - `Svg` - The SVG for ownership.
///
/// # Examples
///
/// ```
/// let svg = save_to_svg(Svg::new());
/// ```
fn save_to_svg(svg: Svg) -> Svg {
    let filepath = ask_for_file_name();
    if filepath.is_none() {
        return svg;
    }
    let file = File::create(filepath.unwrap());
    if file.is_err() {
        return svg;
    }
    let writer = BufWriter::new(file.unwrap());
    let _ = export_svg(writer, &svg);
    svg
}

/// The CLI main menu.
///
/// # Examples
///
/// ```
/// main_menu();
/// ```
pub fn main_menu() {
    let mut svg: Option<Svg> = None;
    let msg_with_svg = r"- (1) Edit SVG
- (2) Save SVG
- (3) Export SVG
- (4) Close SVG";
    let msg_without_svg = r"- (5) Load SVG
- (6) Create SVG";
    loop {
        clear_screen();
        let message = "Choose an option :\n".to_string()
            + if svg.is_some() {
                msg_with_svg
            } else {
                msg_without_svg
            }
            + "\n- (7) Quit";

        let choice = ask_for_value_in_range(
            &message,
            &"Select a valid option".to_string(),
            None::<&Svg>,
            1,
            6,
        )
        .unwrap_or(-1);
        match choice {
            1 => svg = Some(edit_svg(svg.unwrap())),
            2 => svg = Some(save_svg(svg.unwrap())),
            3 => svg = Some(save_to_svg(svg.unwrap())),
            4 => svg = None,
            5 => svg = load_svg(),
            6 => svg = Some(create_svg()),
            7 => return,
            _ => {}
        }
    }
}
