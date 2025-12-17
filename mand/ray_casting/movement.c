/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:07:42 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/17 18:55:57 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void apply_sprint(t_game *g, double *move_speed)
{
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT_SHIFT) || 
        mlx_is_key_down(g->mlx, MLX_KEY_RIGHT_SHIFT))
        *move_speed = g->player.move_speed * 2.0;
    else
        *move_speed = g->player.move_speed;
}

void move_forward(t_game *g, double move_speed)
{
    double new_x;
    double new_y;
    
    new_x = g->player.x + g->player.dir_x * move_speed;
    new_y = g->player.y + g->player.dir_y * move_speed;
    
    if (get_map_value(g, (int)new_x, (int)g->player.y) == 0)
        g->player.x = new_x;
    if (get_map_value(g, (int)g->player.x, (int)new_y) == 0)
        g->player.y = new_y;
}

void move_backward(t_game *g, double move_speed)
{
    double new_x;
    double new_y;
    
    new_x = g->player.x - g->player.dir_x * move_speed;
    new_y = g->player.y - g->player.dir_y * move_speed;
    
    if (get_map_value(g, (int)new_x, (int)g->player.y) == 0)
        g->player.x = new_x;
    if (get_map_value(g, (int)g->player.x, (int)new_y) == 0)
        g->player.y = new_y;
}

void move_left(t_game *g, double move_speed)
{
    double new_x;
    double new_y;
    
    new_x = g->player.x - g->player.plane_x * move_speed;
    new_y = g->player.y - g->player.plane_y * move_speed;
    
    if (get_map_value(g, (int)new_x, (int)g->player.y) == 0)
        g->player.x = new_x;
    if (get_map_value(g, (int)g->player.x, (int)new_y) == 0)
        g->player.y = new_y;
}

void move_right(t_game *g, double move_speed)
{
    double new_x;
    double new_y;
    
    new_x = g->player.x + g->player.plane_x * move_speed;
    new_y = g->player.y + g->player.plane_y * move_speed;
    
    if (get_map_value(g, (int)new_x, (int)g->player.y) == 0)
        g->player.x = new_x;
    if (get_map_value(g, (int)g->player.x, (int)new_y) == 0)
        g->player.y = new_y;
}

void handle_rotation(t_game *g)
{
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
        rotate_player(&g->player, -g->player.rot_speed);
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
        rotate_player(&g->player, g->player.rot_speed);
}

void handle_wasd(t_game *g, double move_speed)
{
    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
        move_forward(g, move_speed);
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
        move_backward(g, move_speed);
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
        move_left(g, move_speed);
    
    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
        move_right(g, move_speed);
}

void handle_movement(t_game *g)
{
    double move_speed;
    
    handle_mouse_rotation(g);
    apply_sprint(g, &move_speed);
    handle_wasd(g, move_speed);
    handle_rotation(g);
}