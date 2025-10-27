use crate::cli::main_menu;

mod cli;
mod export;
mod shapes;
mod styles;
mod utils;

/// The program's entry point.
fn main() {
    main_menu();
}
