/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:54:59 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/24 09:37:36 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define MAP_W 12
# define MAP_H 12
# define TILE 50
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define LIGHT 3

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_torch
{
	int				sprite_x;
	int				sprite_y;
	int				sprite_width;
	int				sprite_height;
	float			scale;
	double			last_x;
	double			last_y;
	double			bob;
	int				bob_direction;
	int				x;
	int				y;
	int				orig_x;
	int				orig_y;
	int				idx;
	int				screen_x;
	int				screen_y;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			alpha;
	int				is_attacking;
	int				attack_frame;
	int				is_opening;
	int				open_frame;
}					t_torch;

typedef struct s_wall
{
	int				line_h;
	int				start;
	int				end;
	uint32_t		color;
}					t_wall;

typedef struct s_lighting
{
	double			ambient_strength;
	double			torch_intensity;
	double			torch_radius;
	double			torch_flicker;
	double			flicker_time;
}					t_lighting;

typedef struct s_minimap
{
	int				size;
	int				offset_x;
	int				offset_y;
	int				radius;
	float			scale;
	int				x;
	int				y;
	int				dx;
	int				dy;
	int				center_x;
	int				center_y;
	int				screen_x;
	int				screen_y;
	float			map_x;
	float			map_y;
	int				x1;
	int				y1;
	uint32_t		color;
}					t_minimap;

typedef struct s_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_line;

typedef struct s_calc
{
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_calc;

typedef struct s_scalc
{
	uint8_t			*pixels;
	int				tex_w;
	int				tex_h;
	int				tex_x;
	double			tex_pos;
	double			step;
}					t_scalc;

typedef struct rgb
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_rgb;

typedef struct s_pars
{
	char			**map;
	t_rgb			*floor;
	t_rgb			*ceil;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	bool			stop;
}					t_pars;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
	double			radius;
}					t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;

	mlx_texture_t	*texture_east;
	mlx_image_t		*img_wall_east;
	mlx_texture_t	*texture_north;
	mlx_image_t		*img_wall_north;
	mlx_texture_t	*texture_south;
	mlx_image_t		*img_wall_south;
	mlx_texture_t	*texture_west;
	mlx_image_t		*img_wall_west;
	mlx_texture_t	*texture_door;
	mlx_image_t		*img_wall_door;

	t_player		player;
	t_pars			*my_map;
	int				map_width;
	int				map_height;
	t_lighting		lighting;

	mlx_texture_t	*texture_torch;
	mlx_image_t		*img_torch;
	t_torch			torch;

	mlx_texture_t	*texture_attack1;
	mlx_texture_t	*texture_attack2;
	mlx_image_t		*img_attack1;
	mlx_image_t		*img_attack2;

	int				screen_width;
	int				screen_height;

	mlx_texture_t	*texture_open1;
	mlx_texture_t	*texture_open2;
	mlx_image_t		*img_open1;
	mlx_image_t		*img_open2;
	double			light;
}					t_game;

typedef struct s_vline
{
	t_game			*g;
	int				x;
	int				start;
	int				end;
	uint32_t		color;
}					t_vline;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
}					t_ray;

typedef struct s_column
{
	t_game			*game;
	int				x;
}					t_column;
t_pars				*map_fill(int argc, char **argv);
int					chack_arg(int argc, char **argv);
int					valid_map(t_pars *my_map);
bool				chck_cub(char *arg);
int					dispatch_line(char *line, char *word, t_pars *m);
int					fill_mapst(char *line, t_pars *my_map);
void				fill_map(t_pars *my_map);
bool				check_content(char *line);
bool				check_line(char *line);
int					check_size(char **map);
int					chack_line(char *line, t_pars *my_map, int s);
int					check_map(char **map);
bool				check_zero_pos(char **map);
bool				check_cell(char **map, int i, int j);
int					check_player(char **map);
int					continu_map(char *line, t_pars *my_map);
int					for_map(char *line, char *word, t_pars *my_map);
int					for_color(char *line, char *word, t_rgb **coll,
						t_pars *my_map);
int					for_cardinal(char *line, char *word, char **cord,
						t_pars *my_map);
void				fix_shit(t_pars *my_map, int k);
int					chack_empty_line(char *line);
char				*get_next_line(int fd);
char				*firs_word(char *line);
char				*last_word(char *line);
char				*trim_line(char *line);
char				*remove_prefix_dup(const char *str, const char *prefix);
int					ft_found(const char *str, char c);
int					ft_count(char const *s);
int					cub_atoi(const char *str);
void				free_split(char **tab);
void				free_mymap(t_pars *my_map);
int					check_comma(char *word);
int					check_rgb(char **rgb);
t_rgb				*colors_parce(char *word);
void				init_player(t_player *player, t_game *g);
void				get_map_dimensions(t_game *g);
void				cast_rays(t_game *g);
void				init_ray(t_ray *ray, t_game *g, int x);
void				calculate_step(t_ray *ray, t_game *g);
void				perform_dda(t_ray *ray, t_game *g);
void				calculate_wall_distance(t_ray *ray, t_game *g);
void				draw_wall(t_game *g, int x, t_ray *ray);
void				draw_textured_wall(t_game *g, int x, t_ray *ray);
void				draw_textured_door(t_game *g, int x, t_ray *ray);
void				draw_vertical_line(t_game *g, t_vline *l);
void				draw_ceiling(t_game *g);
void				draw_floor(t_game *g);
void				draw_ceiling_and_floor(t_game *g);
int					load_game_assets(t_game *g);
int					load_wall_textures(t_pars *map, t_game *g);
int					load_tex_img(t_game *g, char *path, mlx_texture_t **tex,
						mlx_image_t **img);
void				free_texturs(t_game *g);
double				get_light_intensity(double dist);
double				clamp_light(double light);
uint32_t			apply_lighting(uint32_t color, double intensity);
void				handle_movement(t_game *g);
void				handle_wasd(t_game *g, double move_speed);
void				apply_sprint(t_game *g, double *move_speed);
void				handle_rotation(t_game *g);
void				handle_mouse_rotation(t_game *g);
int					init_mouse(t_game *g);
bool				can_move_to(t_game *g, double x, double y, double r);
void				rotate_player(t_player *p, double angle);
void				move_forward(t_game *g, double move_speed);
void				move_backward(t_game *g, double move_speed);
void				move_left(t_game *g, double move_speed);
void				move_right(t_game *g, double move_speed);
void				draw_torch_sprite(t_game *g);
void				update_torch_bob(t_torch *t, t_game *g);
void				update_torch_animation(t_torch *t, t_game *g);
void				continue_torch_anim(t_torch *t, t_game *g);
void				handle_attack(t_game *g, t_torch *t);
void				handle_door_open(t_game *g, t_torch *t);
void				draw_torch_pixel(t_game *g, t_torch *t, uint8_t *pixels,
						int img_width);
void				draw_minimap(t_game *g);
void				draw_minimap_pixel(t_game *g, t_minimap *m);
void				draw_filled_circle(t_game *g, t_minimap *f, int radius,
						uint32_t color);
void				draw_line(t_game *g, t_minimap *m, uint32_t color);
void				init_line(t_line *l, t_minimap *m);
void				step_line(t_line *l, t_minimap *m);
mlx_texture_t		*wall_text(t_ray *ray, t_game *g);
double				wal_xx(t_ray *ray, t_game *g);
t_calc				refill(double perp, t_game *g);
t_scalc				calculatin(double wall_x, mlx_texture_t *tex, t_calc value,
						t_game *g);
uint32_t			color_pixwls_img(t_scalc *calc, t_ray *ray);
int					init_texture_data(t_game *g, t_ray *ray, t_calc *v,
						t_scalc *c);
void				draw_texture_column(t_column *col, t_calc *v, t_scalc *c,
						t_ray *ray);
int					fill_textur(t_pars *map, t_game *g);
int					door_in_front(t_game *g, int *mx, int *my);
int					get_map_value(t_game *g, int x, int y);
size_t				ft_strlenn(const char *str);
char				*ft_strdupp(const char *s1);
void				ft_copy(char *dest, const char *src, size_t src_len);
char				*ft_strjoinn(char *s1, char *s2);
int					ft_found(const char *str, char c);
uint32_t			get_rgba(int r, int g, int b);

#endif
