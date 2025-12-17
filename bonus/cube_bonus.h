#ifndef CUBE_BONUS_H
#define CUBE_BONUS_H


#define KEY_W <keycode for W>
#define KEY_A <keycode for A>
#define KEY_S <keycode for S>
#define KEY_D <keycode for D>

#define WIN_W 800
#define WIN_H 600

#define MAP_W 12
#define MAP_H 12
#define TILE 50
#ifndef DOOR_OPEN_DIST
# define DOOR_OPEN_DIST 0.80
#endif

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif


#include <stdio.h>
#include <unistd.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include "../libft/libft.h"


typedef struct s_calc
{
    int line_height;
    int draw_start;
    int draw_end;
}   t_calc;

typedef struct s_scalc
{
    uint8_t *pixels;
    int tex_w;
    int tex_h;
    int tex_x;
    double tex_pos;
    double step;
}  t_scalc;

typedef struct rgb
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}   t_rgb;

typedef struct s_pars
{
	char    **map;
	t_rgb   *floor;
	t_rgb  *ceil;
	char    *no;
    char    *so;
    char    *ea;
    char    *we;
    bool    stop;
}	t_pars;

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double move_speed;
    double rot_speed;
}   t_player;

typedef struct s_game
{
    mlx_t       *mlx;
    mlx_image_t *img;
    mlx_texture_t* texture_east;
    mlx_image_t* img_wall_east;
    mlx_texture_t* texture_north;
    mlx_image_t* img_wall_north;
    mlx_texture_t* texture_south; 
    mlx_image_t* img_wall_south; 
    mlx_texture_t* texture_west;
    mlx_image_t* img_wall_west; 

    mlx_texture_t* texture_door;
    mlx_image_t*   img_wall_door;

    t_player    player;
    t_pars      *my_map;
    int         map_width;
    int         map_height;
}   t_game;

typedef struct s_ray
{
    double camera_x;
    double dir_x;
    double dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
}   t_ray;


int     check_player(char **map);
int check_map(char **map);
char *firs_word(char *line);
t_rgb  *colors_parce(char *word);
void    free_mymap(t_pars *my_map);
int   chack_empty_line(char *line);
bool chck_cub(char *arg);
int	cub_atoi(const char *str);
int	ft_count(char const *s);
char *trim_line(char *line);
char *last_word(char *line);
int    fill_mapst(char *line,t_pars *my_map);
void draw_wall(t_game *g, int x, t_ray *ray);
void	fill_map(t_pars *my_map);
bool check_zero_pos(char **map);
bool    check_content(char *line);
void draw_textured_wall(t_game *g, int x, t_ray *ray);
bool check_line(char *line);
char	*get_next_line(int fd);
int		ft_found(const char *str, char c);
char	*ft_char_front(char *s);
char	*ft_read(char *str, char *buffer, int fd);
char	*ft_char_back(char *s);
void	ft_copy(char *dest, const char *src, size_t src_len);
void cast_rays(t_game *g);
void draw_ceiling_and_floor(t_game *G);
void perform_dda(t_ray *ray, t_game *g);
void init_ray(t_ray *ray, t_game *g, int x);
void calculate_step(t_ray *ray, t_game *g);
void calculate_wall_distance(t_ray *ray, t_game *g);
void init_ray(t_ray *ray, t_game *g, int x);
void calculate_step(t_ray *ray, t_game *g);
void perform_dda(t_ray *ray, t_game *g);
int get_map_value(t_game *g, int x, int y);
t_calc	refill(double perp);
double	wal_xx(t_ray *ray, t_game *g);
mlx_texture_t	*wall_text(t_ray *ray, t_game *g);
t_scalc	calculatin(double wall_x, mlx_texture_t *tex, t_calc value);
uint32_t	color_pixwls_img(t_scalc *calc, t_ray *ray);
int door_in_front(t_game *g, int *mx, int *my);

# endif