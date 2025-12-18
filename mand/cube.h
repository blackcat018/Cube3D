#ifndef CUBE_H
#define CUBE_H

#define KEY_W <keycode for W>
#define KEY_A <keycode for A>
#define KEY_S <keycode for S>
#define KEY_D <keycode for D>

#define WIN_W 800
#define WIN_H 600

#define MAP_W 12
#define MAP_H 12
#define TILE 50


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define LIGHT 3
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


typedef struct s_torch
{
    int     sprite_x;
    int     sprite_y;
    int     sprite_width;
    int     sprite_height;
    float   scale;
    double  last_x;
    double  last_y;
    double  bob;
    int     bob_direction;
    int     x;
    int     y;
    int     orig_x;
    int     orig_y;
    int     idx;
    int     screen_x;
    int     screen_y;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t alpha;
	int     is_attacking;
    int     attack_frame;
} t_torch;


typedef struct s_lighting
{
    double ambient_strength;
    double torch_intensity;
    double torch_radius;
    double torch_flicker;
    double flicker_time;
}   t_lighting;


typedef struct s_minimap
{
    int size;
    int offset_x;
    int offset_y;
    int radius;
    float scale;
    int x;
    int y;
    int dx;
    int dy;
    int center_x;
    int center_y;
    int screen_x;
    int screen_y;
    float map_x;
    float map_y;
    uint32_t color;
}   t_minimap;

typedef struct s_line
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
}   t_line;


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
    t_player    player;
    t_pars      *my_map;
    int         map_width;
    int         map_height;
    t_lighting lighting;
    mlx_texture_t   *texture_torch;
    mlx_image_t     *img_torch;
    t_torch torch;
	mlx_texture_t   *texture_attack1;
    mlx_texture_t   *texture_attack2;
    mlx_image_t     *img_attack1;
    mlx_image_t     *img_attack2;
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
int check_collision_circle(t_game *g, double x, double y, double radius);
void handle_mouse_rotation(t_game *g);
void draw_torch_sprite(t_game *g);
int get_map_value(t_game *g, int x, int y);
void handle_movement(t_game *g);
uint32_t apply_lighting(uint32_t color, double intensity);
void rotate_player(t_player *p, double angle);
void draw_ceiling_and_floor(t_game *G);
void cast_rays(t_game *g);
void draw_vertical_line(t_game *g, int x, int draw_start, int draw_end, uint32_t color);
void calculate_wall_distance(t_ray *ray, t_game *g);
void perform_dda(t_ray *ray, t_game *g);
void calculate_step(t_ray *ray, t_game *g);
void init_ray(t_ray *ray, t_game *g, int x);
void init_player(t_player *player, t_game *g);
int get_map_value(t_game *g, int x, int y);
void get_map_dimensions(t_game *g);
void handle_mouse_rotation(t_game *g);
bool can_move_to(t_game *g, double x, double y, double r);
void rotate_player(t_player *p, double angle);
void    free_texturs(t_game *g);
int    fill_textur(t_pars	*my_map, t_game *g);
int fill_tex(t_pars	*my_map, t_game *g);
t_pars	*map_fill(int argc, char **argv);

















void draw_vertical_line(t_game *g, int x, int draw_start, int draw_end, uint32_t color);
#endif