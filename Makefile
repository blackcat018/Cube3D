CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
NAME = cub3D
NAME_B = cub3D_bonus

SRC = mand/main.c mand/get_next_line.c mand/texturing/wall_help.c mand/texturing/wall_textur.c\
	  mand/parsing/check.c mand/parsing/fill_map.c mand/parsing/helpers.c\
	  mand/parsing/misc.c mand/parsing/parsing.c mand/parsing/tst.c mand/lib_ft.c\
	  mand/ray_casting/apply_textures.c mand/ray_casting/casting.c\
	  mand/ray_casting/drawing.c mand/ray_casting/init.c mand/ray_casting/mapping.c\
	  mand/ray_casting/movement.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

HEADER = mand/cube.h
HEADER_B = bonus/cub3D_bonus.h

SRCS_B = bonus/main_bonus.c bonus/lib_bonus.c\
	  bonus/parsing_bonus/check_parse_bonus.c\
	  bonus/parsing_bonus/misc_bonus.c\
	  bonus/parsing_bonus/norm_sucks_bonus.c\
	  bonus/parsing_bonus/parsing_bonus.c\
	  bonus/parsing_bonus/parsing_helper_bonus.c\
	  bonus/texturing_bonus/apply_textures_bonus.c\
	  bonus/get_next_line_bonus.c bonus/texturing_bonus/fill_map_bonus.c\
	  bonus/texturing_bonus/wall_textur_bonus.c\
	  bonus/texturing_bonus/map_prep_bonus.c\
	  bonus/texturing_bonus/light_n_color_bonus.c\
	  bonus/texturing_bonus/set_load_fill_bonus.c\
	  bonus/texturing_bonus/cleanup_texture_bonus.c\
	  bonus/hand_torch_bonus/hand_bonus.c\
	  bonus/hand_torch_bonus/hand_support_bonus.c\
	  bonus/ray_casting_bonus/movement_bonus.c\
	  bonus/ray_casting_bonus/mapping_bonus.c\
	  bonus/ray_casting_bonus/casting_bonus.c\
	  bonus/ray_casting_bonus/player_bonus.c\
	  bonus/ray_casting_bonus/plane_bonus.c\
	  bonus/ray_casting_bonus/directions_bonus.c\
	  bonus/ray_casting_bonus/init_bonus.c\
	  bonus/ray_casting_bonus/movement_alt_bonus.c\
	  bonus/minimap_bonus/minimap_bonus.c\
	  bonus/minimap_bonus/mini_map_sup_bonus.c
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