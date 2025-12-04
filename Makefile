CC      = cc
CFLAGS  = -Wall -Wextra -Werror #-fsanitize=address

NAME    = Cube3d

SRC_DIR = ray_casting
MLX_DIR = MLX42
SRC     = casing.c tst.c get_next_line.c fill_map.c wall_textur.c
OBJ     = $(SRC:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX     = -I$(MLX_DIR)/include
#GLFW    = -L$(shell brew --prefix glfw)/lib -lglfw
MLXFLAGS = -L$(MLX_DIR) -lmlx42 -lglfw -ldl -lm

all: $(LIBFT) $(NAME)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(MLX) $(GLFW) $(MLXFLAGS) $(LIBFT) -Iinclude -o $(NAME)

%.o: %.c cube.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
