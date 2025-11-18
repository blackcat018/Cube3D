CC      = cc
CFLAGS  = -Wall -Wextra -Werror

NAME    = cube3d

MLX_DIR = MLX42
SRC_DIR = ray_casting

SRC     = $(SRC_DIR)/casing.c
OBJ     = $(SRC:.c=.o)

# Homebrew path (Apple Silicon = /opt/homebrew, Intel = /usr/local)
BREW_PREFIX := $(shell brew --prefix)

MLX_INC = -I$(MLX_DIR)/include
MLX_LIB = -L$(MLX_DIR)/build -lmlx42 \
          -L$(BREW_PREFIX)/lib -lglfw \
          -framework Cocoa -framework IOKit -framework CoreVideo -framework Carbon

INC     = -I.

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
