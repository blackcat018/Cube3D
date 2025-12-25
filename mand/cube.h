/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:23:07 by czghoumi          #+#    #+#             */
/*   Updated: 2025/12/25 15:48:53 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# define WIN_W 800
# define WIN_H 600
# define MAP_W 12
# define MAP_H 12
# define TILE 50
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
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

typedef struct s_wall
{
	int				line_h;
	int				start;
	int				end;
	uint32_t		color;
}					t_wall;
//
typedef struct s_calc
{
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_calc;

typedef struct s_direction
{
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_direction;

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
	t_player		player;
	t_pars			*my_map;
	int				map_width;
	int				map_height;
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

int					check_player(char **map);
int					check_map(char **map);
char				*firs_word(char *line);
t_rgb				*colors_parce(char *word);
void				free_mymap(t_pars *my_map);
int					chack_empty_line(char *line);
bool				chck_cub(char *arg);
int					cub_atoi(const char *str);
int					ft_count(char const *s);
char				*trim_line(char *line);
char				*last_word(char *line);
int					fill_mapst(char *line, t_pars *my_map);
void				draw_wall(t_game *g, int x, t_ray *ray);
void				fill_map(t_pars *my_map);
bool				check_zero_pos(char **map);
bool				check_content(char *line);
void				draw_textured_wall(t_game *g, int x, t_ray *ray);
bool				check_line(char *line);
char				*get_next_line(int fd);
int					ft_found(const char *str, char c);
char				*ft_char_front(char *s);
char				*ft_read(char *str, char *buffer, int fd);
char				*ft_char_back(char *s);
void				ft_copy(char *dest, const char *src, size_t src_len);
// added casting
int					fill_tex(t_pars *my_map, t_game *g);
void				inicial_g(t_game *g);
int					fill_textur(t_pars *my_map, t_game *g);
void				free_texturs(t_game *g);
void				cast_rays(t_game *g);
void				calculate_step(t_ray *ray, t_game *g);
void				perform_dda(t_ray *ray, t_game *g);
void				draw_vertical_line(t_vline *l);
void				calculate_wall_distance(t_ray *ray, t_game *g);
uint32_t			get_rgba(int r, int g, int b);
void				draw_ceiling_and_floor(t_game *G);
int					chack_arg(int argc, char **argv);
int					chack_line(char *line, t_pars *my_map, int s);
void				applay_info(t_player *player, t_direction dir);
void				init_mouves(t_player *player, t_game *g, int i, int j);
void				init_player(t_player *player, t_game *g);
void				init_ray(t_ray *ray, t_game *g, int x);
t_wall				get_wall(t_ray *ray);
void				loop_hook(void *param);
void				get_map_dimensions(t_game *g);
int					get_map_value(t_game *g, int x, int y);
void				set_map(t_pars *my_map);
int					valid_map(t_pars *my_map);
t_pars				*map_fill(int argc, char **argv);
void				handle_movement(t_game *g);
void				handel_mouves_keys(t_game *g, double x, double y,
						double radius);
bool				can_move_to(t_game *g, double x, double y, double r);
void				rotate_player(t_player *p, double angle);
// added textures
char				*trim_line(char *line);
bool				check_content(char *line);
bool				check_line(char *line);
bool				check_cell(char **map, int i, int j);
bool				check_zero_pos(char **map);
int					for_cardinal(char *line, char *word, char **cord,
						t_pars *my_map);
char				*remove_prefix_dup(const char *str, const char *prefix);
int					for_color(char *line, char *word, t_rgb **coll,
						t_pars *my_map);
int					continu_map(char *line, t_pars *my_map);
int					for_map(char *line, char *word, t_pars *my_map);
int					fill_mapst(char *line, t_pars *my_map);
int					ft_count(char const *s);
int					chack_empty_line(char *line);
void				free_mymap(t_pars *my_map);
char				*firs_word(char *line);
char				*last_word(char *line);
void				free_split(char **tab);
int					dispatch_line(char *line, char *word, t_pars *m);
int					check_player(char **map);
int					check_size(char **map);
int					check_map(char **map);
void				fix_shit(t_pars *my_map, int k);
void				fill_map(t_pars *my_map);
bool				chck_cub(char *arg);
int					cub_atoi(const char *str);
int					check_rgb(char **rgb);
int					check_comma(char *word);
t_rgb				*colors_parce(char *word);
uint32_t			color_pixwls_img(t_scalc *calc, t_ray *ray);
t_scalc				calculatin(double wall_x, mlx_texture_t *tex, t_calc value);
t_calc				refill(double perp);
mlx_texture_t		*wall_text(t_ray *ray, t_game *g);
double				wal_xx(t_ray *ray, t_game *g);
size_t				ft_strlenn(const char *str);
char				*ft_strdupp(const char *s1);
void				ft_copy(char *dest, const char *src, size_t src_len);
char				*ft_strjoinn(char *s1, char *s2);
int					ft_found(const char *str, char c);
int					check_wit_space(char *arg);
#endif
