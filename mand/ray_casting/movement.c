/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:03:33 by moel-idr          #+#    #+#             */
/*   Updated: 2025/12/24 10:29:39 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

bool	can_move_to(t_game *g, double x, double y, double r)
{
	double	dx;
	double	dy;
	int		mx;
	int		my;

	mx = (int)floor(x - r);
	while (mx <= (int)floor(x + r))
	{
		my = (int)floor(y - r);
		while (my <= (int)floor(y + r))
		{
			if (get_map_value(g, mx, my) != 0)
			{
				dx = x - (fmax((double)mx, fmin(x, (double)mx + 1.0)));
				dy = y - (fmax((double)my, fmin(y, (double)my + 1.0)));
				if (dx * dx + dy * dy < r * r)
					return (false);
			}
			my++;
		}
		mx++;
	}
	return (true);
}

void	handel_mouves_keys(t_game *g, double x, double y, double radius)
{
	double	new_x;
	double	new_y;

	new_x = g->player.x + x * g->player.move_speed;
	new_y = g->player.y + y * g->player.move_speed;
	if (can_move_to(g, new_x, g->player.y, radius))
		g->player.x = new_x;
	if (can_move_to(g, g->player.x, new_y, radius))
		g->player.y = new_y;
}

void	handle_movement(t_game *g)
{
	double	radius;

	radius = 0.2;
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		handel_mouves_keys(g, g->player.dir_x, g->player.dir_y, radius);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		handel_mouves_keys(g, -g->player.dir_x, -g->player.dir_y, radius);
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		handel_mouves_keys(g, -g->player.plane_x, -g->player.plane_y, radius);
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		handel_mouves_keys(g, g->player.plane_x, g->player.plane_y, radius);
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		rotate_player(&g->player, -g->player.rot_speed);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		rotate_player(&g->player, g->player.rot_speed);
}
