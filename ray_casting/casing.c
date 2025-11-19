#include "../cube.h"
void init_map(t_game *g)
{
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1},
    {1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1},  
    {1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,0,1},
    {1,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,0,1,0,0,1,1,1,0,0,0,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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
    player->x = 5.5;
    player->y = 5.5;
    player->dir_x = -1.0;
    player->dir_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.66;
    player->move_speed = 0.05;
    player->rot_speed = 0.03;
}
//TODO
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

// #define TILE_SIZE 20
// #define MINIMAP_OFFSET_X 10
// #define MINIMAP_OFFSET_Y 10

// void init_map(t_game *g)
// {
//     int map[24][24] = {
//         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//         {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,1,1,1,0,1,1,0,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1},
//         {1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1},
//         {1,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1},
//         {1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1},
//         {0,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
//         {0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
//         {0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
//         {1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
//         {1,0,1,1,1,1,0,1,1,1,1,0,0,1,0,1,0,1,1,1,0,1,0,1},
//         {1,0,1,0,0,1,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,0,1},
//         {1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,0,1},
//         {1,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,0,1},
//         {1,0,1,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1},
//         {1,0,1,0,0,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,0,1,0,1},
//         {1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,1,0,1,1,1,0,1,0,1},
//         {1,0,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
//         {1,0,1,1,1,1,1,0,1,0,0,1,1,1,0,1,0,1,1,1,0,1,0,1},
//         {1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
//         {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//     };

//     int i = 0;
//     int j;
//     while (i < MAP_HEIGHT)
//     {
//         j = 0;
//         while (j < MAP_WIDTH)
//         {
//             g->map[i][j] = map[i][j];
//             j++;
//         }
//         i++;
//     }
// }

// void init_player(t_player *player)
// {
//     player->x = 5.5;
//     player->y = 5.5;
//     player->dir_x = -1.0;
//     player->dir_y = 0.0;
//     player->plane_x = 0.0;
//     player->plane_y = 0.66;
//     player->move_speed = 0.05;
//     player->rot_speed = 0.03;
// }

// void draw_rect(t_game *g, int x, int y, int w, int h, uint32_t color)
// {
//     int i, j; 
    
//     i = 0;
//     while (i < h)
//     {
//         j = 0;
//         while (j < w)
//         {
//             if (x + j >= 0 && x + j < SCREEN_WIDTH && 
//                 y + i >= 0 && y + i < SCREEN_HEIGHT)
//                 mlx_put_pixel(g->img, x + j, y + i, color);
//             j++;
//         }
//         i++;
//     }
// }

// void draw_line(t_game *g, int x1, int y1, int x2, int y2, uint32_t color)
// {
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);
//     int sx = x1 < x2 ? 1 : -1;
//     int sy = y1 < y2 ? 1 : -1;
//     int err = dx - dy;
//     int e2;
    
//     while (1)
//     {
//         if (x1 >= 0 && x1 < SCREEN_WIDTH && y1 >= 0 && y1 < SCREEN_HEIGHT)
//             mlx_put_pixel(g->img, x1, y1, color);
        
//         if (x1 == x2 && y1 == y2)
//             break;
        
//         e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             x1 += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             y1 += sy;
//         }
//     }
// }

// void draw_map_2d(t_game *g)
// {
//     int i, j;
//     int screen_x, screen_y;
    
//     // Draw tiles
//     i = 0;
//     while (i < MAP_HEIGHT)
//     {
//         j = 0;
//         while (j < MAP_WIDTH)
//         {
//             screen_x = MINIMAP_OFFSET_X + j * TILE_SIZE;
//             screen_y = MINIMAP_OFFSET_Y + i * TILE_SIZE;
            
//             if (g->map[i][j] == 1)
//                 draw_rect(g, screen_x, screen_y, TILE_SIZE, TILE_SIZE, 0xFFFFFFFF);
//             else
//                 draw_rect(g, screen_x, screen_y, TILE_SIZE, TILE_SIZE, 0x333333FF);
            
//             j++;
//         }
//         i++;
//     }
// }

// void draw_player_2d(t_game *g)
// {
//     int player_screen_x = MINIMAP_OFFSET_X + (int)(g->player.x * TILE_SIZE);
//     int player_screen_y = MINIMAP_OFFSET_Y + (int)(g->player.y * TILE_SIZE);
    
//     // Draw player as a circle (approximated with a square)
//     draw_rect(g, player_screen_x - 3, player_screen_y - 3, 6, 6, 0x00FF00FF);
    
//     // Draw direction line
//     int dir_length = 30;
//     int end_x = player_screen_x + (int)(g->player.dir_x * dir_length);
//     int end_y = player_screen_y + (int)(g->player.dir_y * dir_length);
//     draw_line(g, player_screen_x, player_screen_y, end_x, end_y, 0xFF0000FF);
    
//     // Draw field of view lines
//     double fov_angle = atan(0.66);
    
//     // Left FOV line
//     double left_x = g->player.dir_x * cos(fov_angle) - g->player.dir_y * sin(fov_angle);
//     double left_y = g->player.dir_x * sin(fov_angle) + g->player.dir_y * cos(fov_angle);
//     end_x = player_screen_x + (int)(left_x * dir_length);
//     end_y = player_screen_y + (int)(left_y * dir_length);
//     draw_line(g, player_screen_x, player_screen_y, end_x, end_y, 0xFFFF00FF);
    
//     // Right FOV line
//     double right_x = g->player.dir_x * cos(-fov_angle) - g->player.dir_y * sin(-fov_angle);
//     double right_y = g->player.dir_x * sin(-fov_angle) + g->player.dir_y * cos(-fov_angle);
//     end_x = player_screen_x + (int)(right_x * dir_length);
//     end_y = player_screen_y + (int)(right_y * dir_length);
//     draw_line(g, player_screen_x, player_screen_y, end_x, end_y, 0xFFFF00FF);
// }

// void rotate_player(t_player *p, double angle)
// {
//     double old_dir_x = p->dir_x;
//     p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
//     p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
    
//     double old_plane_x = p->plane_x;
//     p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
//     p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
// }

// void handle_movement(t_game *g)
// {
//     double new_x;
//     double new_y;
    
//     if (mlx_is_key_down(g->mlx, MLX_KEY_W))
//     {
//         new_x = g->player.x + g->player.dir_x * g->player.move_speed;
//         new_y = g->player.y + g->player.dir_y * g->player.move_speed;
//         if (g->map[(int)new_y][(int)new_x] == 0)
//         {
//             g->player.x = new_x;
//             g->player.y = new_y;
//         }
//     }

//     if (mlx_is_key_down(g->mlx, MLX_KEY_S))
//     {
//         new_x = g->player.x - g->player.dir_x * g->player.move_speed;
//         new_y = g->player.y - g->player.dir_y * g->player.move_speed;
//         if (g->map[(int)new_y][(int)new_x] == 0)
//         {
//             g->player.x = new_x;
//             g->player.y = new_y;
//         }
//     }
    
//     if (mlx_is_key_down(g->mlx, MLX_KEY_A))
//     {
//         new_x = g->player.x - g->player.plane_x * g->player.move_speed;
//         new_y = g->player.y - g->player.plane_y * g->player.move_speed;
//         if (g->map[(int)new_y][(int)new_x] == 0)
//         {
//             g->player.x = new_x;
//             g->player.y = new_y;
//         }
//     }
    
//     if (mlx_is_key_down(g->mlx, MLX_KEY_D))
//     {
//         new_x = g->player.x + g->player.plane_x * g->player.move_speed;
//         new_y = g->player.y + g->player.plane_y * g->player.move_speed;
//         if (g->map[(int)new_y][(int)new_x] == 0)
//         {
//             g->player.x = new_x;
//             g->player.y = new_y;
//         }
//     }
    
//     if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
//         rotate_player(&g->player, g->player.rot_speed);
    
//     if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
//         rotate_player(&g->player, -g->player.rot_speed);
// }

// void loop_hook(void *param)
// {
//     t_game *g = param;

//     handle_movement(g);

//     // Clear screen with black background
//     memset(g->img->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);

//     // Draw 2D top-down view
//     draw_map_2d(g);
//     draw_player_2d(g);
// }

// int main(void)
// {
//     t_game g;
    
//     init_map(&g);
//     init_player(&g.player);
    
//     g.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d - 2D View", true);
//     if (!g.mlx)
//         return (1);
    
//     g.img = mlx_new_image(g.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
//     mlx_image_to_window(g.mlx, g.img, 0, 0);
    
//     mlx_loop_hook(g.mlx, loop_hook, &g);
//     mlx_loop(g.mlx);
//     mlx_terminate(g.mlx);
    
//     return (0);
// }