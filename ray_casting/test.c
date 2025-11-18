#include "../cube.h"

#include <string.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

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
    t_player    player;
    int         map[MAP_HEIGHT][MAP_WIDTH];
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

void init_map(t_game *g)
{
    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,1},
        {1,0,0,0,1,0,0,1},
        {1,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1}
    };
    
    int i = 0;
    int j;
    while (i < MAP_HEIGHT)
    {
        j = 0;
        while (j < MAP_WIDTH)
        {
            g->map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
}

void init_player(t_player *player)
{
    player->x = 3.5;
    player->y = 3.5;
    player->dir_x = -1.0;
    player->dir_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.66;
    player->move_speed = 0.05;
    player->rot_speed = 0.03;
}

void init_ray(t_ray *ray, t_game *g, int x)
{
    ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
    ray->dir_x = g->player.dir_x + g->player.plane_x * ray->camera_x;
    ray->dir_y = g->player.dir_y + g->player.plane_y * ray->camera_x;
    
    ray->map_x = (int)g->player.x;
    ray->map_y = (int)g->player.y;
    
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
}

void calculate_step(t_ray *ray, t_game *g)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (g->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - g->player.x) * ray->delta_dist_x;
    }
    
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (g->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - g->player.y) * ray->delta_dist_y;
    }
}

void perform_dda(t_ray *ray, t_game *g)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (g->map[ray->map_y][ray->map_x] > 0)
            ray->hit = 1;
    }
}

void calculate_wall_distance(t_ray *ray, t_game *g)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - g->player.x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - g->player.y + (1 - ray->step_y) / 2) / ray->dir_y;
}

void draw_vertical_line(t_game *g, int x, int draw_start, int draw_end, uint32_t color)
{
    int y = draw_start;
    
    while (y < draw_end)
    {
        if (y >= 0 && y < SCREEN_HEIGHT)
            mlx_put_pixel(g->img, x, y, color);
        y++;
    }
}

void draw_wall(t_game *g, int x, t_ray *ray)
{
    int line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
    int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;
    uint32_t color;
    if (ray->side == 0)
        color = 0xFF0000FF;
    else
        color = 0x880000FF;
    draw_vertical_line(g, x, 0, draw_start, 0x333333FF);
    draw_vertical_line(g, x, draw_start, draw_end, color);
    draw_vertical_line(g, x, draw_end, SCREEN_HEIGHT, 0x666666FF);
}

void cast_rays(t_game *g)
{
    int x = 0;
    t_ray ray;
    
    while (x < SCREEN_WIDTH)
    {
        init_ray(&ray, g, x);
        calculate_step(&ray, g);
        perform_dda(&ray, g);
        calculate_wall_distance(&ray, g);
        draw_wall(g, x, &ray);
        x++;
    }
}

void rotate_player(t_player *p, double angle)
{
    double old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
    p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
    
    double old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
    p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void handle_movement(t_game *g)
{
    double new_x;
    double new_y;
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
    {
        new_x = g->player.x + g->player.dir_x * g->player.move_speed;
        new_y = g->player.y + g->player.dir_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }

    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
    {
        new_x = g->player.x - g->player.dir_x * g->player.move_speed;
        new_y = g->player.y - g->player.dir_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }
    

    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
    {
        new_x = g->player.x - g->player.plane_x * g->player.move_speed;
        new_y = g->player.y - g->player.plane_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
    {
        new_x = g->player.x + g->player.plane_x * g->player.move_speed;
        new_y = g->player.y + g->player.plane_y * g->player.move_speed;
        if (g->map[(int)new_y][(int)new_x] == 0)
        {
            g->player.x = new_x;
            g->player.y = new_y;
        }
    }
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
        rotate_player(&g->player, g->player.rot_speed);
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
        rotate_player(&g->player, -g->player.rot_speed);
}

void loop_hook(void *param)
{
    t_game *g = param;

    handle_movement(g);

    memset(g->img->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

    cast_rays(g);
}


int main(void)
{
    t_game g;
    
    init_map(&g);
    init_player(&g.player);
    
    g.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
    if (!g.mlx)
        return (1);
    
    g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_image_to_window(g.mlx, g.img, 0, 0);
    
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);
    mlx_terminate(g.mlx);
    
    return (0);
}

//void init_map(t_game *g)
//{
//    int map[MAP_H][MAP_W] = {
//        {1,1,1,1,1,1,1,1},
//        {1,0,0,0,0,0,0,1},
//        {1,0,0,0,0,0,0,1},
//        {1,0,0,0,0,0,0,1},
//        {1,0,0,0,0,0,0,1},
//        {1,0,0,0,0,0,0,1},
//        {1,0,0,0,0,0,0,1},
//        {1,1,1,1,1,1,1,1}
//    };

//    int y = 0;
//    while (y < MAP_H)
//    {
//        int x = 0;
//        while (x < MAP_W)
//        {
//            g->map[y][x] = map[y][x];
//            x++;
//        }
//        y++;
//    }
//}


//void init_player(t_player *p)
//{
//    p->x = 3.5 * TILE;
//    p->y = 3.5 * TILE;
//    p->dir_x = -1;
//    p->dir_y = 0;
//    p->move_speed = 3;
//    p->rot_speed = 0.06;
//}

//void draw_square(mlx_image_t *img, int px, int py, int size, uint32_t col)
//{
//    int y = 0;
//    while (y < size)
//    {
//        int x = 0;
//        while (x < size)
//        {
//            mlx_put_pixel(img, px + x, py + y, col);
//            x++;
//        }
//        y++;
//    }
//}


//void draw_map(t_game *g)
//{
//    int y = 0;
//    while (y < MAP_H)
//    {
//        int x = 0;
//        while (x < MAP_W)
//        {
//            if (g->map[y][x] == 1)
//                draw_square(g->img, x * TILE, y * TILE, TILE, 0x666666FF);
//            else
//                draw_square(g->img, x * TILE, y * TILE, TILE, 0x222222FF);
//            x++;
//        }
//        y++;
//    }
//}


//void draw_player(t_game *g)
//{
//    draw_square(g->img, g->p.x - 5, g->p.y - 5, 10, 0xFF0000FF);
//}

//void move_player(t_game *g)
//{
//    double new_x, new_y;

//    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
//    {
//        new_x = g->p.x + g->p.dir_x * g->p.move_speed;
//        new_y = g->p.y + g->p.dir_y * g->p.move_speed;
//        if (g->map[(int)(new_y / TILE)][(int)(new_x / TILE)] == 0)
//        { g->p.x = new_x; g->p.y = new_y; }
//    }

//    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
//    {
//        new_x = g->p.x - g->p.dir_x * g->p.move_speed;
//        new_y = g->p.y - g->p.dir_y * g->p.move_speed;
//        if (g->map[(int)(new_y / TILE)][(int)(new_x / TILE)] == 0)
//        { g->p.x = new_x; g->p.y = new_y; }
//    }

//    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
//    {
//        new_x = g->p.x + g->p.dir_y * g->p.move_speed;
//        new_y = g->p.y - g->p.dir_x * g->p.move_speed;
//        if (g->map[(int)(new_y / TILE)][(int)(new_x / TILE)] == 0)
//        { g->p.x = new_x; g->p.y = new_y; }
//    }

//    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
//    {
//        new_x = g->p.x - g->p.dir_y * g->p.move_speed;
//        new_y = g->p.y + g->p.dir_x * g->p.move_speed;
//        if (g->map[(int)(new_y / TILE)][(int)(new_x / TILE)] == 0)
//        { g->p.x = new_x; g->p.y = new_y; }
//    }

//    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
//    {
//        double old_x = g->p.dir_x;
//        g->p.dir_x = g->p.dir_x * cos(g->p.rot_speed) - g->p.dir_y * sin(g->p.rot_speed);
//        g->p.dir_y = old_x * sin(g->p.rot_speed) + g->p.dir_y * cos(g->p.rot_speed);
//    }

//    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
//    {
//        double old_x = g->p.dir_x;
//        g->p.dir_x = g->p.dir_x * cos(-g->p.rot_speed) - g->p.dir_y * sin(-g->p.rot_speed);
//        g->p.dir_y = old_x * sin(-g->p.rot_speed) + g->p.dir_y * cos(-g->p.rot_speed);
//    }
//}

//void loop_hook(void *param)
//{
//    t_game *g = param;

//    move_player(g);

//    memset(g->img->pixels, 0, WIN_W * WIN_H * 4);

//    draw_map(g);
//    draw_player(g);
//}

//int main(void)
//{
//    t_game g;

//    init_map(&g);
//    init_player(&g.p);

//    g.mlx = mlx_init(WIN_W, WIN_H,"2D", true);
//    g.img = mlx_new_image(g.mlx, WIN_W, WIN_H);
//    mlx_image_to_window(g.mlx, g.img, 0, 0);

//    mlx_loop_hook(g.mlx, loop_hook, &g);
//    mlx_loop(g.mlx);
//}
