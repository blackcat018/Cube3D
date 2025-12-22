/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 22:07:42 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/22 10:17:26 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	move_forward(t_game *g, double move_speed)
{
	double	new_x;
	double	new_y;
	double	off_x;
	double	off_y;

	new_x = g->player.x + g->player.dir_x * move_speed;
	new_y = g->player.y + g->player.dir_y * move_speed;
	off_x = g->player.dir_x * g->player.radius;
	off_y = g->player.dir_y * g->player.radius;
	if (get_map_value(g, (int)(new_x + off_x), (int)(g->player.y)) == 0)
		g->player.x = new_x;
	if (get_map_value(g, (int)(g->player.x), (int)(new_y + off_y)) == 0)
		g->player.y = new_y;
}

void	move_backward(t_game *g, double move_speed)
{
	double	new_x;
	double	new_y;
	double	off_x;
	double	off_y;

	new_x = g->player.x - g->player.dir_x * move_speed;
	new_y = g->player.y - g->player.dir_y * move_speed;
	off_x = -g->player.dir_x * g->player.radius;
	off_y = -g->player.dir_y * g->player.radius;
	if (get_map_value(g, (int)(new_x + off_x), (int)g->player.y) == 0)
		g->player.x = new_x;
	if (get_map_value(g, (int)g->player.x, (int)(new_y + off_y)) == 0)
		g->player.y = new_y;
}

void	move_left(t_game *g, double move_speed)
{
	double	new_x;
	double	new_y;
	double	off_x;
	double	off_y;

	new_x = g->player.x - g->player.plane_x * move_speed;
	new_y = g->player.y - g->player.plane_y * move_speed;
	off_x = -g->player.plane_x * g->player.radius;
	off_y = -g->player.plane_y * g->player.radius;
	if (get_map_value(g, (int)(new_x + off_x), (int)(g->player.y)) == 0)
		g->player.x = new_x;
	if (get_map_value(g, (int)(g->player.x), (int)(new_y + off_y)) == 0)
		g->player.y = new_y;
}

void	move_right(t_game *g, double move_speed)
{
	double	new_x;
	double	new_y;
	double	off_x;
	double	off_y;

	new_x = g->player.x + g->player.plane_x * move_speed;
	new_y = g->player.y + g->player.plane_y * move_speed;
	off_x = g->player.plane_x * g->player.radius;
	off_y = g->player.plane_y * g->player.radius;
	if (get_map_value(g, (int)(new_x + off_x), (int)(g->player.y)) == 0)
		g->player.x = new_x;
	if (get_map_value(g, (int)(g->player.x), (int)(new_y + off_y)) == 0)
		g->player.y = new_y;
}

void	handle_movement(t_game *g)
{
	double	move_speed;

	if (!mlx_is_key_down(g->mlx, MLX_KEY_LEFT_CONTROL))
		handle_mouse_rotation(g);
	apply_sprint(g, &move_speed);
	handle_wasd(g, move_speed);
	handle_rotation(g);
}
