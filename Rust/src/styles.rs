use serde::{Deserialize, Serialize};

use crate::{shapes::Print, utils::Point};

/// Represents the different rotate transformations.
///
/// # Variants
///
/// - `Circular(u16)` - Circular rotation.
/// - `Flipx` - Flip X transformation.
/// - `Flipy` - Flip Y transformation.
///
/// # Examples
///
/// ```
/// let rotate = Rotate::Circular;
/// match rotate {
///     Rotate::Circular(v0) => handle_tuple,
///     Rotate::Flipx => handle_unit,
///     Rotate::Flipy => handle_unit,
/// }
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub enum Rotate {
    Circular(u16),
    Flipx,
    Flipy,
}

/// Represents a RGBA color.
///
/// # Fields
///
/// - `red` (`u8`) - The RED parameter.
/// - `green` (`u8`) - The GREEN parameter.
/// - `blue` (`u8`) - The BLUE parameter.
/// - `transparency` (`u8`) - The TRANSPARENCY parameter.
///
/// # Examples
///
/// ```
/// let s = Color {
///     red: value,
///     green: value,
///     blue: value,
///     transparency: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Color {
    pub red: u8,
    pub green: u8,
    pub blue: u8,
    pub transparency: u8,
}

/// Represents the shape's styles.
///
/// # Fields
///
/// - `translate` (`Point`) - The translate transformation.
/// - `rotate` (`Rotate`) - The rotate transformation.
/// - `fill` (`Color`) - The fill color.
/// - `outline` (`Color`) - The outline color.
///
/// # Examples
///
/// ```
/// let s = Styles {
///     translate: value,
///     rotate: value,
///     fill: value,
///     outline: value,
/// };
/// ```
#[derive(Debug, Serialize, Deserialize, Clone)]
pub struct Styles {
    pub translate: Point,
    pub rotate: Rotate,
    pub fill: Color,
    pub outline: Color,
}

impl Default for Color {
    /// The color's default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new color.
    ///
    /// # Examples
    ///
    /// ```
    /// let color = Color::default();
    /// ```
    fn default() -> Self {
        Self {
            red: Default::default(),
            green: Default::default(),
            blue: Default::default(),
            transparency: Default::default(),
        }
    }
}

impl Print for Color {
    /// Prints out the given color.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Color`) - The color to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let color = Color::default();
    /// color.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        print!(
            "rgba({}, {}, {}, {})",
            self.red, self.green, self.blue, self.transparency
        );
    }
}

impl Default for Rotate {
    /// The rotate default constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new rotate.
    ///
    /// # Examples
    ///
    /// ```
    /// let rotate = Rotate::default();
    /// ```
    fn default() -> Self {
        Self::Circular(0)
    }
}

impl Rotate {
    /// Create a circular rotate transformation.
    ///
    /// # Arguments
    ///
    /// - `degree` (`u16`) - The angle.
    ///
    /// # Returns
    ///
    /// - `Self` - The new rotate.
    ///
    /// # Examples
    ///
    /// ```
    /// let rotate = Rotate::new_circular(180);
    /// ```
    pub fn new_circular(degree: u16) -> Self {
        Self::Circular(degree % 360)
    }

    /// Creates a new flip x transformation.
    ///
    /// # Returns
    ///
    /// - `Self` - The new rotate.
    ///
    /// # Examples
    ///
    /// ```
    /// let rotate = new_flip_x();
    /// ```
    pub fn new_flip_x() -> Self {
        Self::Flipx
    }

    /// Creates a new flip y transformation.
    ///
    /// # Returns
    ///
    /// - `Self` - The new rotate.
    ///
    /// # Examples
    ///
    /// ```
    /// let rotate = new_flip_y();
    /// ```
    pub fn new_flip_y() -> Self {
        Self::Flipy
    }
}

impl Print for Rotate {
    /// Prints out the given rotate.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Rotate`) - The rotate to print.
    /// - `_depth` (`u32`) - Unused.
    ///
    /// # Examples
    ///
    /// ```
    /// let rotate = Rotate::default();
    /// rotate.print(0);
    /// ```
    fn print(&self, _depth: u32) {
        match self {
            Rotate::Circular(deg) => print!("{deg}"),
            Rotate::Flipx => print!("x"),
            Rotate::Flipy => print!("y"),
        }
    }
}

impl Default for Styles {
    /// The default constructor for the styles.
    ///
    /// # Returns
    ///
    /// - `Self` - The new styles.
    ///
    /// # Examples
    ///
    /// ```
    /// let styles = Styles::default();
    /// ```
    fn default() -> Self {
        Self {
            translate: Default::default(),
            rotate: Default::default(),
            fill: Default::default(),
            outline: Default::default(),
        }
    }
}

impl Styles {
    /// The styles constructor.
    ///
    /// # Returns
    ///
    /// - `Self` - The new styles.
    ///
    /// # Examples
    ///
    /// ```
    /// let styles = Styles::new();
    /// ```
    pub fn new() -> Self {
        Self::default()
    }
}

impl Print for Styles {
    /// Prints out the given styles.
    ///
    /// # Arguments
    ///
    /// - `&self` (`&Styles`) - The styles to print.
    /// - `depth` (`u32`) - The number of tabs to print.
    ///
    /// # Examples
    ///
    /// ```
    /// let styles = Styles::default();
    /// styles.print(1);
    /// ```
    fn print(&self, depth: u32) {
        print!("fill=\"");
        self.fill.print(depth);
        print!("\" outline=\"");
        self.outline.print(depth);
        print!("\" translate=\"");
        self.translate.print(depth);
        print!("\" rotate=\"");
        self.rotate.print(depth);
        print!("\"");
    }
}
