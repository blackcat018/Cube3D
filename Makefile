CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
NAME = Cube3d
NAME_B = Cube3d_bonus

SRC_DIR = ray_casting
MLX_DIR = MLX42
SRC = mand/main.c mand/texturing/tst.c\
	  mand/texturing/apply_textures.c\
	  mand/get_next_line.c mand/texturing/fill_map.c\
	  mand/texturing/wall_textur.c\
	  mand/hand_torch/hand.c\
	  mand/ray_casting/movement.c\
	  mand/ray_casting/mapping.c\
	  mand/ray_casting/casting.c\
	  mand/ray_casting/player.c\
	  mand/ray_casting/plane.c\
	  mand/ray_casting/directions.c\
	  mand/minimap/minimap.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADER = mand/cube.h
HEADER_B = bonus/cube_bonus.h

SRCS_B = bonus/parcing_bonus.c bonus/door_textur_bonus.c bonus/wall_textur_bonus.c bonus/casing_bonus.c
OBJS_B = $(SRCS_B:.c=.o)

MLX = MLX42/build/libmlx42.a
GLFW = -L$(shell brew --prefix glfw)/lib -lglfw
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
INCLUDES = -I include


all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(GLFW) $(MLXFLAGS) $(LIBFT) $(INCLUDES) -o $(NAME)

$(NAME_B): $(OBJS_B) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_B) $(MLX) $(GLFW) $(MLXFLAGS) $(LIBFT) $(INCLUDES) -o $(NAME_B)

bonus: $(LIBFT) $(NAME_B)

%_bonus.o: %_bonus.c $(HEADER_B)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJS_B)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_B)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re