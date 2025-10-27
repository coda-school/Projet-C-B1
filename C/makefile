CC = gcc
CFLAGS = -Wall -Werror -std=c99 -fstack-protector
TARGET = bin/main
OBJ_DIR = bin

# List source files in the desired compilation order
SRC = utils/utils.c \
      models/utils/point.c \
      models/styles/color.c \
      models/styles/rotate.c \
      models/styles/style.c \
      models/shapes/path/move_to.c \
      models/shapes/path/line_to.c \
      models/shapes/path/end_path.c \
      models/shapes/path/curve_to.c \
      models/shapes/path/path.c \
      models/shapes/ellipse.c \
      models/shapes/rectangle.c \
      models/shapes/line.c \
      models/shapes/multiline.c \
      models/shapes/polygon.c \
      models/shapes/group.c \
      models/shapes/shape.c \
      models/shapes/svg.c \
      serde/serde.c \
      serde/deserialize/parser.c \
      serde/deserialize/parse_style.c \
      serde/deserialize/parse_path.c \
      serde/deserialize/parse_shape.c \
      serde/serialize/export.c \
      serde/serialize/export_style.c \
      serde/serialize/export_path.c \
      serde/serialize/export_shape.c \
      html/html.c \
      cli/cli_style.c \
      cli/cli_path.c \
      cli/cli_shape.c \
      cli/cli.c \
      main.c

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
