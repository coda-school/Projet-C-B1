use serde::{Deserialize, Serialize};

use crate::shapes::Print;

///  Represents a point.
///
/// # Fields
///
/// - `x` (`i32`) - The x coordinate.
/// - `y` (`i32`) - The y coordinate.
///
/// # Examples
///
/// ```
/// let s = Point {
///     x: value,
///     y: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone, Copy)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

impl Default for Point {
    /// Default constructor for the point structure.
    ///
    /// # Returns
    ///
    /// - `Self` - the new point.
    ///
    /// # Examples
    ///
    /// ```
    /// let point = Point::default();
    /// ```
    fn default() -> Self {
        Self {
            x: Default::default(),
            y: Default::default(),
        }
    }
}

impl Print for Point {
    /// Prints out the given point.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Point`) - The point to print.
    /// - `_depth` (`u32`) - Ignored.
    ///
    /// # Examples
    ///
    /// ```
    /// let point = Point::new();
    /// point.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!("{} {}", self.x, self.y);
    }
}

impl Point {
    /// The point structure's constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new point.
    ///
    /// # Examples
    ///
    /// ```
    /// let _ = Point::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

/// Prints out tabs "amount" times.
///
/// # Arguments
///
/// - `amount` (`u32`) - The number of tabs to print.
///
/// # Examples
///
/// ```
/// print_tabs(2);
/// ```
pub fn print_tabs(amount: u32) {
    for _ in 0..amount {
        print!("  ");
    }
}

/// Checks if the given file name is valid.
///
/// # Arguments
///
/// - `filename` (`&str`) - The file name to check.
///
/// # Returns
///
/// - `Result<(), String>` - Returns Ok(()) if the file name is valid else return Err() with an error message.
///
/// # Errors
///
/// - Empty file name.
/// - Reserved file name.
/// - Invalid chars.
/// - Invalid start or end.
/// - Invalid length.
/// - Invalid encoding.
///
/// # Examples
///
/// ```
/// if let Err(error) = is_valid_filename("test.txt") {
///     // ...
/// }
/// ```
pub fn is_valid_filename(filename: &str) -> Result<(), String> {
    if filename.is_empty() {
        return Err("Filename cannot be empty".to_string());
    }

    // Check for reserved filenames on Windows
    let reserved_names = [
        "CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8",
        "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9",
    ];
    if reserved_names.contains(&filename.to_ascii_uppercase().as_str()) {
        return Err("Filename is reserved".to_string());
    }

    // Check for invalid characters
    let invalid_chars = ['\\', '/', ':', '*', '?', '"', '<', '>', '|'];
    if filename.chars().any(|c| invalid_chars.contains(&c)) {
        return Err("Filename contains invalid characters".to_string());
    }

    // Check for trailing spaces or dots
    if filename.ends_with(char::is_whitespace) || filename.ends_with('.') {
        return Err("Filename cannot end with a space or dot".to_string());
    }

    // Check for leading/trailing spaces or dots (optional, depending on requirements)
    if filename.starts_with('.') || filename.starts_with(char::is_whitespace) {
        return Err("Filename cannot start with a space or dot".to_string());
    }

    // Check length (max 255 bytes for most filesystems)
    if filename.len() > 255 {
        return Err("Filename is too long".to_string());
    }

    // Check for valid UTF-8 (optional, depending on requirements)
    if !filename.is_char_boundary(0) {
        return Err("Filename is not valid UTF-8".to_string());
    }

    Ok(())
}
