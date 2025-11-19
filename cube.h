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


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

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


#endif