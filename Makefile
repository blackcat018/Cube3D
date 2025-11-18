# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

# Project name
NAME    = cube3d

# Directories
MLX_DIR = MLX42
SRC_DIR = ray_casting

# Files
SRC     = $(SRC_DIR)/casing.c
OBJ     = $(SRC:.c=.o)

# MLX42 includes and libs
MLX_INC = -I$(MLX_DIR)/include
MLX_LIB = -L$(MLX_DIR) -lmlx42 -lglfw -ldl -lm

# Include local headers
INC     = -I.

# Build rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(INC) $(MLX_INC) $(MLX_LIB) -o $(NAME)

%.o: %.c cube.h
	$(CC) $(CFLAGS) $(INC) $(MLX_INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
